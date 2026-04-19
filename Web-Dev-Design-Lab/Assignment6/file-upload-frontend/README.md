# File Upload Management Frontend

React + Tailwind CSS frontend for the File Upload and Management API.

## Features

- User authentication (Login/Register)
- Upload files (images & documents)
- View list of uploaded files with metadata
- Download files
- Delete files
- File type filtering (jpg, png, gif, pdf, doc, docx)
- File size display
- Protected routes
- Responsive design with Tailwind CSS

## Setup

1. Install dependencies:
   ```bash
   npm install
   ```

2. Start development server:
   ```bash
   npm run dev
   ```

3. Open http://localhost:5174 in your browser

## Connecting to Backend

The frontend expects the File Upload API backend to be running on **http://localhost:3001**

Make sure the backend is running:
```bash
cd file-upload-api
npm start
```

## Default Login

Email: `admin@files.com`  
Password: `admin123`

Or register a new account from the Register page.

## Pages

- **/login** - Login page
- **/register** - Register new user
- **/** or **/files** - File management dashboard with upload and file list

## Allowed File Types

- Images: JPG, JPEG, PNG, GIF
- Documents: PDF, DOC, DOCX
- Max file size: 10MB

## Tech Stack

- React 18
- React Router v6
- Tailwind CSS
- Fetch API with FormData for uploads
