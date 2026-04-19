const Book = require('../models/Book');

exports.getAllBooks = async (req, res) => {
  try {
    const { page = 1, limit = 10, author, genre } = req.query;
    const result = await Book.findAll({
      page: parseInt(page),
      limit: parseInt(limit),
      author,
      genre
    });

    res.status(200).json({
      success: true,
      data: result.data,
      pagination: result.pagination,
      filters: {
        author: req.query.author || '',
        genre: req.query.genre || ''
      }
    });
  } catch (error) {
    res.status(500).json({
      success: false,
      message: 'Failed to fetch books',
      error: error.message
    });
  }
};

exports.getBookById = async (req, res) => {
  try {
    const book = await Book.findById(req.params.id);

    if (!book) {
      return res.status(404).json({
        success: false,
        message: 'Book not found'
      });
    }

    res.status(200).json({
      success: true,
      data: book
    });
  } catch (error) {
    res.status(500).json({
      success: false,
      message: 'Failed to fetch book',
      error: error.message
    });
  }
};

exports.createBook = async (req, res) => {
  try {
    const { title, author, genre, year } = req.body;

    if (!title || !author || !genre || !year) {
      return res.status(400).json({
        success: false,
        message: 'Title, author, genre, and year are required'
      });
    }

    const book = await Book.create({ title, author, genre, year });

    res.status(201).json({
      success: true,
      message: 'Book created successfully',
      data: book
    });
  } catch (error) {
    res.status(400).json({
      success: false,
      message: error.message
    });
  }
};

exports.updateBook = async (req, res) => {
  try {
    const { title, author, genre, year } = req.body;

    if (!title && !author && !genre && !year) {
      return res.status(400).json({
        success: false,
        message: 'At least one field to update is required'
      });
    }

    const book = await Book.update(req.params.id, { title, author, genre, year });

    if (!book) {
      return res.status(404).json({
        success: false,
        message: 'Book not found'
      });
    }

    res.status(200).json({
      success: true,
      message: 'Book updated successfully',
      data: book
    });
  } catch (error) {
    res.status(400).json({
      success: false,
      message: error.message
    });
  }
};

exports.deleteBook = async (req, res) => {
  try {
    const success = await Book.delete(req.params.id);

    if (!success) {
      return res.status(404).json({
        success: false,
        message: 'Book not found'
      });
    }

    res.status(200).json({
      success: true,
      message: 'Book deleted successfully'
    });
  } catch (error) {
    res.status(500).json({
      success: false,
      message: 'Failed to delete book',
      error: error.message
    });
  }
};
