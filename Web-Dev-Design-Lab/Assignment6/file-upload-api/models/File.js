const fs = require('fs');
const path = require('path');

const DATA_FILE = path.join(__dirname, '../data/files.json');
const INDEX_FILE = path.join(__dirname, '../data/indexes.json');

class File {
  static async readFiles() {
    try {
      const data = fs.readFileSync(DATA_FILE, 'utf8');
      return JSON.parse(data);
    } catch (error) {
      return [];
    }
  }

  static async writeFiles(files) {
    fs.writeFileSync(DATA_FILE, JSON.stringify(files, null, 2));
  }

  static async readIndexes() {
    try {
      const data = fs.readFileSync(INDEX_FILE, 'utf8');
      return JSON.parse(data);
    } catch (error) {
      return { users: 0, files: 0 };
    }
  }

  static async writeIndexes(indexes) {
    fs.writeFileSync(INDEX_FILE, JSON.stringify(indexes, null, 2));
  }

  static async findAll() {
    return this.readFiles();
  }

  static async findByFilename(filename) {
    const files = await this.readFiles();
    return files.find(file => file.filename === filename);
  }

  static async create(fileData) {
    const files = await this.readFiles();
    const indexes = await this.readIndexes();

    indexes.files += 1;

    const newFile = {
      id: indexes.files,
      filename: fileData.filename,
      originalName: fileData.originalname,
      mimetype: fileData.mimetype,
      size: fileData.size,
      path: fileData.path,
      uploadedBy: fileData.userId,
      uploadedAt: new Date().toISOString()
    };

    files.push(newFile);
    await this.writeFiles(files);
    await this.writeIndexes(indexes);

    return newFile;
  }

  static async deleteByFilename(filename) {
    const files = await this.readFiles();
    const index = files.findIndex(file => file.filename === filename);

    if (index === -1) {
      return null;
    }

    const deletedFile = files.splice(index, 1)[0];
    await this.writeFiles(files);

    return deletedFile;
  }
}

module.exports = File;
