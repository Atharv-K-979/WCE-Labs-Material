const express = require('express');
const app = express();

// Route 1: Home Page
app.get('/', (req, res) => {
    res.send('Welcome to the Home Page');
});

// Route 2: About Page
app.get('/about', (req, res) => {
    res.send('This is the About Page');
});

// Route 3: Contact Page
app.get('/contact', (req, res) => {
    res.send('Contact us at: email@example.com');
});

// 404 Error Handler (Must be at the end)
app.use((req, res) => {
    res.status(404).send('Page Not Found');
});

// Start Server
app.listen(3000, () => {
    console.log('Server running on port 3000');
});