# Simple Blog Application

A full-stack blog application built with React, Tailwind CSS, Node.js, Express, and MongoDB.

## Features
- **Authentication**: JWT-based secure authentication (HTTP-only cookies)
- **Role-based Actions**: Only post authors can edit or delete their own posts
- **CRUD Posts**: Create, Read, Update, and Delete blog posts
- **Comment System**: Add comments to posts, only delete your own comments
- **Like System**: Like and unlike posts
- **Pagination & Search**: Browse posts easily
- **Modern UI**: Clean and responsive design using Tailwind CSS v4

## Folder Structure
- `client/`: React frontend
- `server/`: Node.js & Express backend

## Prerequisites
- Node.js (v18+)
- MongoDB (Running locally or MongoDB Atlas)

## Setup Instructions

### 1. Backend Setup
1. Navigate to the server folder: `cd server`
2. Install dependencies: `npm install`
3. Create a `.env` file based on `.env.example`:
   ```
   PORT=5000
   MONGODB_URI=mongodb://localhost:27017/blog-app
   ACCESS_TOKEN_SECRET=your_access_secret
   REFRESH_TOKEN_SECRET=your_refresh_secret
   NODE_ENV=development
   COOKIE_SECURE=false
   COOKIE_SAMESITE=Lax
   CLIENT_URL=http://localhost:5173
   ```
4. Start the backend server: `npm run dev` (Runs on port 5000)

### 2. Frontend Setup
1. Navigate to the client folder: `cd client`
2. Install dependencies: `npm install`
3. Start the Vite development server: `npm run dev` (Runs on port 5173)

## Usage
- Register an account
- Log in
- Click "Write" to create a post
- View a post to like it or leave comments
- Go to "Edit post" to modify your existing posts

## API Endpoints
- `POST /api/auth/register`: Register user
- `POST /api/auth/login`: Login user
- `POST /api/auth/logout`: Logout user
- `GET /api/auth/me`: Get current user
- `GET /api/posts`: Get all posts (with pagination and search)
- `POST /api/posts`: Create post
- `GET /api/posts/:id`: Get single post
- `PUT /api/posts/:id`: Update post
- `DELETE /api/posts/:id`: Delete post
- `PUT /api/posts/:id/like`: Like/unlike post
- `GET /api/posts/:postId/comments`: Get comments for post
- `POST /api/comments`: Add comment
- `DELETE /api/comments/:id`: Delete comment
