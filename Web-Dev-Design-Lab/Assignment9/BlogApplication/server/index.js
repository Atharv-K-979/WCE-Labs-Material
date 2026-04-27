// import express from 'express';
// import dotenv from 'dotenv';
// import cors from 'cors';
// import cookieParser from 'cookie-parser';
// import connectDB from './config/db.js';

// import authRoutes from './routes/authRoutes.js';
// import postRoutes from './routes/postRoutes.js';
// import commentRoutes from './routes/commentRoutes.js';

// // If running from root directory, specify path
// dotenv.config({ path: '../.env' });
// // In case the script is run from inside server/
// dotenv.config();

// connectDB();

// const app = express();

// app.use(cors({
//   origin: process.env.CLIENT_URL || 'http://localhost:5173',
//   credentials: true,
// }));

// app.use(express.json());
// app.use(cookieParser());

// // Routes
// app.use('/api/auth', authRoutes);
// app.use('/api/posts', postRoutes);
// app.use('/api', commentRoutes);

// app.get('/', (req, res) => {
//   res.send('API is running...');
// });

// const PORT = process.env.PORT || 5000;

// app.listen(PORT, () => {
//   console.log(`Server running in ${process.env.NODE_ENV} mode on port ${PORT}`);
// });



import express from 'express';
import dotenv from 'dotenv';
import cors from 'cors';
import cookieParser from 'cookie-parser';
import path from 'path';
import { fileURLToPath } from 'url';

import connectDB from './config/db.js';

import authRoutes from './routes/authRoutes.js';
import postRoutes from './routes/postRoutes.js';
import commentRoutes from './routes/commentRoutes.js';

// Load environment variables
dotenv.config();

// Connect DB
connectDB();

const app = express();

// Fix __dirname for ES modules
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Middleware
app.use(cors({
  origin: true, // allow same-origin (Render deployment)
  credentials: true,
}));

app.use(express.json());
app.use(cookieParser());

// API Routes
app.use('/api/auth', authRoutes);
app.use('/api/posts', postRoutes);
app.use('/api', commentRoutes);

// Test route
app.get('/api', (req, res) => {
  res.send('API is running...');
});


// app.use(express.static(path.join(__dirname, '../client/dist')));

// app.get('*', (req, res) => {
//   res.sendFile(path.join(__dirname, '../client/dist/index.html'));
// });
app.use(express.static(path.join(__dirname, '../client/dist')));

app.get(/.*/, (req, res) => {
  res.sendFile(path.join(__dirname, '../client/dist/index.html'));
});


// Start server
const PORT = process.env.PORT || 5000;

app.listen(PORT, () => {
  console.log(`Server running in ${process.env.NODE_ENV} mode on port ${PORT}`);
});