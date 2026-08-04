# File Upload and Management API

A RESTful API for uploading, viewing, downloading, and managing files with user authentication.

## Features

- User registration and JWT authentication
- File upload with Multer (images and documents)
- File listing with metadata
- File download
- File deletion
- File type filtering and size limits
- JSON file-based metadata persistence

## Setup

1. Install dependencies:
   ```bash
   npm install
   ```

2. Configure environment:
   - Edit `.env` file to change PORT, JWT_SECRET, or UPLOAD_DIR if needed
   - Default upload directory is `uploads/`

3. Start the server:
   ```bash
   npm start
   ```

   For development with auto-reload:
   ```bash
   npm run dev
   ```

The API will run on http://localhost:3001

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

Returns a JWT token in response.

### File Management (All protected - require `Authorization: Bearer <token>`)

**List all uploaded files:**
```
GET /api/files
Authorization: Bearer <token>
```

Response:
```json
{
  "success": true,
  "message": "Files retrieved successfully",
  "data": [
    {
      "id": 1,
      "filename": "image-123456789.jpg",
      "originalName": "vacation.jpg",
      "mimetype": "image/jpeg",
      "size": 123456,
      "path": "uploads/image-123456789.jpg",
      "uploadedBy": 1,
      "uploadedAt": "2024-01-15T10:30:00.000Z"
    }
  ],
  "count": 1
}
```

**Upload a file:**
```
POST /api/files/upload
Content-Type: multipart/form-data
Authorization: Bearer <token>

Form field name: file
```

Allowed file types:
- Images: jpg, jpeg, png, gif
- Documents: pdf, doc, docx

Maximum file size: 10MB

Response:
```json
{
  "success": true,
  "message": "File uploaded successfully",
  "data": {
    "id": 1,
    "filename": "image-123456789.jpg",
    "originalName": "vacation.jpg",
    "mimetype": "image/jpeg",
    "size": 123456,
    "uploadedAt": "2024-01-15T10:30:00.000Z"
  }
}
```

**Download a file:**
```
GET /api/files/:filename/download
Authorization: Bearer <token>
```

The file will be downloaded with its original filename.

**Delete a file:**
```
DELETE /api/files/:filename
Authorization: Bearer <token>
```

## Testing with cURL

```bash
# 1. Register a user
curl -X POST http://localhost:3001/api/auth/register \
  -H "Content-Type: application/json" \
  -d '{"email":"test@test.com","password":"test123","name":"Test User"}'

# 2. Login and get token
curl -X POST http://localhost:3001/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"email":"test@test.com","password":"test123"}'

# Copy the token from response

# 3. Upload an image (replace TOKEN and file path)
curl -X POST http://localhost:3001/api/files/upload \
  -H "Authorization: Bearer TOKEN" \
  -F "file=@/path/to/your/image.jpg"

# 4. List all files
curl http://localhost:3001/api/files \
  -H "Authorization: Bearer TOKEN"

# 5. Download a file (use filename from step 4)
curl http://localhost:3001/api/files/FILENAME.jpg/download \
  -H "Authorization: Bearer TOKEN" \
  -o downloaded-file.jpg

# 6. Delete a file
curl -X DELETE http://localhost:3001/api/files/FILENAME.jpg \
  -H "Authorization: Bearer TOKEN"
```

## Data Storage

- **Metadata** stored in `data/` directory:
  - `users.json` - User accounts (with hashed passwords)
  - `files.json` - File metadata records
  - `indexes.json` - Auto-increment counters

- **Uploaded files** stored in `uploads/` directory (or custom directory from UPLOAD_DIR env variable)

## Notes

- JWT tokens expire after 24 hours
- All file operations require authentication
- Files retain their original names in the Content-Disposition header when downloaded
- Deleted files are removed from both metadata and disk
- Uploaded files are renamed to avoid conflicts (original-timestamp-random.ext)
