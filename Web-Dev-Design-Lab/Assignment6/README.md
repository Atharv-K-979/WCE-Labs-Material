# Assignment 6: Full-Stack RESTful API Development

Complete full-stack applications with React frontends and Node.js/Express backends.

## 🚀 Projects Overview

### 1. Library Management System

**Backend:** `./library-api` (Node.js + Express)  
**Frontend:** `./library-frontend` (React + Tailwind CSS)

**Full Stack Application:**
- User authentication with JWT
- Book CRUD operations (Create, Read, Update, Delete)
- Pagination and filtering (by author, genre)
- Responsive web interface

**Ports:** Backend: 3000 | Frontend: 5173

---

### 2. File Upload Management System

**Backend:** `./file-upload-api` (Node.js + Express + Multer)  
**Frontend:** `./file-upload-frontend` (React + Tailwind CSS)

**Full Stack Application:**
- User authentication with JWT
- File upload (images & documents)
- File listing with metadata
- Download and delete operations
- File type validation (jpg, png, gif, pdf, doc, docx)
- 10MB size limit

**Ports:** Backend: 3001 | Frontend: 5174

---

## 📋 Quick Start

### Option 1: Run Everything (4 Terminal Windows)

**Terminal 1 - Library Backend:**
```bash
cd library-api
npm install
npm start
```

**Terminal 2 - Library Frontend:**
```bash
cd library-frontend
npm install
npm run dev
```

**Terminal 3 - File Upload Backend:**
```bash
cd file-upload-api
npm install
npm start
```

**Terminal 4 - File Upload Frontend:**
```bash
cd file-upload-frontend
npm install
npm run dev
```

---

### Option 2: Use Script (Start All at Once)

```bash
# Make script executable
chmod +x start-all.sh

# Run all servers (uses tmux or background processes)
./start-all.sh
```

---

## 🌐 Access URLs

| Application | Frontend URL | Backend API |
|-------------|--------------|-------------|
| Library Management | http://localhost:5173 | http://localhost:3000 |
| File Upload | http://localhost:5174 | http://localhost:3001 |

---

## 🔐 Default Login Credentials

### Library API
- **Email:** `admin@library.com`
- **Password:** `admin123`

### File Upload API
- **Email:** `admin@files.com`
- **Password:** `admin123`

You can also register new accounts from the frontend login pages.

---

## 📁 Project Structure

```
Assignment6/
│
├── 📦 Backends
│   ├── library-api/          # Library Management Backend
│   │   ├── server.js
│   │   ├── package.json
│   │   ├── .env
│   │   ├── controllers/
│   │   ├── middleware/
│   │   ├── models/
│   │   ├── routes/
│   │   └── data/
│   │
│   └── file-upload-api/      # File Upload Backend
│       ├── server.js
│       ├── package.json
│       ├── .env
│       ├── controllers/
│       ├── middleware/
│       ├── models/
│       ├── routes/
│       ├── uploads/
│       └── data/
│
├── 💻 Frontends
│   ├── library-frontend/     # Library Management Frontend
│   │   ├── src/
│   │   │   ├── App.jsx
│   │   │   ├── context/AuthContext.jsx
│   │   │   ├── services/api.js
│   │   │   └── ...
│   │   ├── package.json
│   │   ├── tailwind.config.js
│   │   ├── index.html
│   │   └── README.md
│   │
│   └── file-upload-frontend/ # File Upload Frontend
│       ├── src/
│       │   ├── App.jsx
│       │   ├── context/AuthContext.jsx
│       │   ├── services/api.js
│       │   └── ...
│       ├── package.json
│       ├── tailwind.config.js
│       ├── index.html
│       └── README.md
│
├── 📄 Documentation
│   ├── README.md             # This file
│   ├── HOW-TO-RUN.md         # Detailed setup instructions
│   └── test-api.sh           # Backend API test script
│
└── ⚙️ Configuration
    └── .env files (in each backend)
```

---

## 🎯 Features

### Library Management System

**Backend Features:**
- JWT authentication (register/login)
- Book CRUD with auto-increment IDs
- Pagination: `?page=1&limit=10`
- Filtering: `?author=Name&genre=Genre`
- JSON file persistence

**Frontend Features:**
- Login/Register pages
- Book listing with table view
- Search and filter controls
- Add/Edit/Delete books
- Pagination controls
- Responsive design with Tailwind CSS

---

### File Upload Management System

**Backend Features:**
- JWT authentication
- Multer file upload with disk storage
- File type validation (jpg, png, gif, pdf, doc, docx)
- 10MB file size limit
- Metadata storage in JSON
- Download and delete operations

**Frontend Features:**
- Login/Register pages
- Drag & drop file upload
- File list with metadata (name, size, type, date)
- Download button
- Delete confirmation
- File type icons/indicators
- Responsive design with Tailwind CSS

---

## 🧪 Testing

### API Testing (Backend)

See individual backend READMEs for cURL examples or run:

```bash
./test-api.sh
```

### Frontend Testing

1. Start both frontend and backend servers
2. Open http://localhost:5173 (Library) or http://localhost:5174 (File Upload)
3. Login with default credentials or register new account
4. Test all features through the web interface

---

## 🛠️ Tech Stack

### Backends
- Node.js
- Express.js
- JWT (jsonwebtoken)
- bcryptjs (password hashing)
- Multer (file upload)
- CORS
- JSON file storage

### Frontends
- React 18
- React Router v6
- Tailwind CSS
- Fetch API
- Context API for state management

---

## 📝 Notes

- Both backends use JSON file-based storage for simplicity
- JWT tokens expire after 24 hours
- File uploads are stored in `uploads/` directory (file-upload-api)
- Default ports can be changed in `.env` files
- For production: use a real database, stronger JWT secret, add rate limiting

---

## 🐛 Troubleshooting

**Port already in use:**
Change PORT in the `.env` file of the affected service.

**Frontend can't connect to backend:**
Make sure the backend is running on the expected port. Check `src/services/api.js` for the correct API_BASE_URL.

**Upload fails:**
Check file size (< 10MB) and type (jpg, png, gif, pdf, doc, docx only).

**Token expired:**
Login again to get a new token (expires after 24 hours).

---
