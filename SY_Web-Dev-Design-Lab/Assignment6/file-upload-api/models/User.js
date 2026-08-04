const fs = require('fs');
const path = require('path');
const bcrypt = require('bcryptjs');

const DATA_FILE = path.join(__dirname, '../data/users.json');
const INDEX_FILE = path.join(__dirname, '../data/indexes.json');

class User {
  static async readUsers() {
    try {
      const data = fs.readFileSync(DATA_FILE, 'utf8');
      return JSON.parse(data);
    } catch (error) {
      return [];
    }
  }

  static async writeUsers(users) {
    fs.writeFileSync(DATA_FILE, JSON.stringify(users, null, 2));
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

  static async findByEmail(email) {
    const users = await this.readUsers();
    return users.find(user => user.email === email);
  }

  static async findById(id) {
    const users = await this.readUsers();
    return users.find(user => user.id === id);
  }

  static async create(userData) {
    const users = await this.readUsers();
    const indexes = await this.readIndexes();

    const existingUser = await this.findByEmail(userData.email);
    if (existingUser) {
      throw new Error('User with this email already exists');
    }

    indexes.users += 1;

    const newUser = {
      id: indexes.users,
      email: userData.email,
      password: await bcrypt.hash(userData.password, 10),
      name: userData.name || '',
      createdAt: new Date().toISOString()
    };

    users.push(newUser);
    await this.writeUsers(users);
    await this.writeIndexes(indexes);

    const { password, ...result } = newUser;
    return result;
  }

  static async validateCredentials(email, password) {
    const user = await this.findByEmail(email);
    if (!user) {
      return null;
    }

    const isValid = await bcrypt.compare(password, user.password);
    if (!isValid) {
      return null;
    }

    const { password: _, ...result } = user;
    return result;
  }
}

module.exports = User;
