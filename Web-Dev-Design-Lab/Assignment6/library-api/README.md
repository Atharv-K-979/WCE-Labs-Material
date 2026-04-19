# Library Management API

A RESTful API for managing a library collection with user authentication.

## Features

- User registration and JWT authentication
- CRUD operations for books
- Pagination and filtering by author/genre
- JSON file-based data persistence

## Setup

1. Install dependencies:
   ```bash
   npm install
   ```

2. Configure environment:
   - Edit `.env` file to change PORT and JWT_SECRET if needed

3. Start the server:
   ```bash
   npm start
   ```

   For development with auto-reload:
   ```bash
   npm run dev
   ```

The API will run on http://localhost:3000

## API Endpoints

### Authentication

**Register a new user:**
```
POST /api/auth/register
Content-Type: application/json

{
  "email": "user@example.com",
  "password": "password123",
  "name": "John Doe"
}
```

**Login:**
```
POST /api/auth/login
Content-Type: application/json

{
  "email": "user@example.com",
  "password": "password123"
}
```

Returns a JWT token in response:
```json
{
  "success": true,
  "message": "Login successful",
  "data": {
    "user": { "id": 1, "email": "...", "name": "..." },
    "token": "eyJhbGciOiJIUzI1NiIs..."
  }
}
```

### Books (All protected - require `Authorization: Bearer <token>`)

**Get all books with pagination and filtering:**
```
GET /api/books?page=1&limit=10&author=Tolstoy&genre=Fiction
```

**Get single book:**
```
GET /api/books/:id
```

**Create a book:**
```
POST /api/books
Content-Type: application/json
Authorization: Bearer <token>

{
  "title": "War and Peace",
  "author": "Leo Tolstoy",
  "genre": "Fiction",
  "year": 1869
}
```

**Update a book:**
```
PUT /api/books/:id
Content-Type: application/json
Authorization: Bearer <token>

{
  "title": "Updated Title",
  "author": "Updated Author",
  "genre": "Updated Genre",
  "year": 2024
}
```

**Delete a book:**
```
DELETE /api/books/:id
Authorization: Bearer <token>
```

## Testing with cURL

```bash
# 1. Register a user
curl -X POST http://localhost:3000/api/auth/register \
  -H "Content-Type: application/json" \
  -d '{"email":"test@test.com","password":"test123","name":"Test User"}'

# 2. Login and get token
curl -X POST http://localhost:3000/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"email":"test@test.com","password":"test123"}'

# Copy the token from response

# 3. Add a book (replace TOKEN with actual token)
curl -X POST http://localhost:3000/api/books \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer TOKEN" \
  -d '{"title":"The Hobbit","author":"J.R.R. Tolkien","genre":"Fantasy","year":1937}'

# 4. Get all books with pagination
curl http://localhost:3000/api/books?page=1&limit=5 \
  -H "Authorization: Bearer TOKEN"

# 5. Filter by genre
curl "http://localhost:3000/api/books?genre=Fantasy" \
  -H "Authorization: Bearer TOKEN"

# 6. Filter by author
curl "http://localhost:3000/api/books?author=Tolkien" \
  -H "Authorization: Bearer TOKEN"

# 7. Get single book
curl http://localhost:3000/api/books/1 \
  -H "Authorization: Bearer TOKEN"

# 8. Update book
curl -X PUT http://localhost:3000/api/books/1 \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer TOKEN" \
  -d '{"title":"The Hobbit: Animated Edition"}'

# 9. Delete book
curl -X DELETE http://localhost:3000/api/books/1 \
  -H "Authorization: Bearer TOKEN"
```

## Data Storage

Data is stored in JSON files in the `data/` directory:
- `users.json` - User accounts (with hashed passwords)
- `books.json` - Book records
- `indexes.json` - Auto-increment counters

## Notes

- JWT tokens expire after 24 hours
- All book operations require authentication
- Pagination uses `page` and `limit` query parameters (default: page=1, limit=10)
- Filtering is case-insensitive for author, exact match for genre
