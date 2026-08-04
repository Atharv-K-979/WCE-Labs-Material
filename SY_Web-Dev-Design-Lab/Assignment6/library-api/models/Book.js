const fs = require('fs');
const path = require('path');

const DATA_FILE = path.join(__dirname, '../data/books.json');
const INDEX_FILE = path.join(__dirname, '../data/indexes.json');

class Book {
  static async readBooks() {
    try {
      const data = fs.readFileSync(DATA_FILE, 'utf8');
      return JSON.parse(data);
    } catch (error) {
      return [];
    }
  }

  static async writeBooks(books) {
    fs.writeFileSync(DATA_FILE, JSON.stringify(books, null, 2));
  }

  static async readIndexes() {
    try {
      const data = fs.readFileSync(INDEX_FILE, 'utf8');
      return JSON.parse(data);
    } catch (error) {
      return { users: 0, books: 0, files: 0 };
    }
  }

  static async writeIndexes(indexes) {
    fs.writeFileSync(INDEX_FILE, JSON.stringify(indexes, null, 2));
  }

  static async findAll(options = {}) {
    const books = await this.readBooks();
    let filtered = [...books];

    if (options.author) {
      filtered = filtered.filter(book =>
        book.author.toLowerCase().includes(options.author.toLowerCase())
      );
    }

    if (options.genre) {
      filtered = filtered.filter(book =>
        book.genre.toLowerCase() === options.genre.toLowerCase()
      );
    }

    const page = parseInt(options.page) || 1;
    const limit = parseInt(options.limit) || 10;
    const startIndex = (page - 1) * limit;
    const endIndex = page * limit;

    return {
      data: filtered.slice(startIndex, endIndex),
      pagination: {
        page,
        limit,
        total: filtered.length,
        totalPages: Math.ceil(filtered.length / limit)
      }
    };
  }

  static async findById(id) {
    const books = await this.readBooks();
    return books.find(book => book.id === id);
  }

  static async create(bookData) {
    const books = await this.readBooks();
    const indexes = await this.readIndexes();

    indexes.books += 1;

    const newBook = {
      id: indexes.books,
      title: bookData.title,
      author: bookData.author,
      genre: bookData.genre,
      year: parseInt(bookData.year),
      createdAt: new Date().toISOString(),
      updatedAt: new Date().toISOString()
    };

    books.push(newBook);
    await this.writeBooks(books);
    await this.writeIndexes(indexes);

    return newBook;
  }

  static async update(id, bookData) {
    const books = await this.readBooks();
    const index = books.findIndex(book => book.id === parseInt(id));

    if (index === -1) {
      return null;
    }

    books[index] = {
      ...books[index],
      title: bookData.title || books[index].title,
      author: bookData.author || books[index].author,
      genre: bookData.genre || books[index].genre,
      year: bookData.year ? parseInt(bookData.year) : books[index].year,
      updatedAt: new Date().toISOString()
    };

    await this.writeBooks(books);
    return books[index];
  }

  static async delete(id) {
    const books = await this.readBooks();
    const index = books.findIndex(book => book.id === parseInt(id));

    if (index === -1) {
      return false;
    }

    books.splice(index, 1);
    await this.writeBooks(books);
    return true;
  }
}

module.exports = Book;
