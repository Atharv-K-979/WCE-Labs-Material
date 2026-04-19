const express = require('express');
const app = express();

app.get('/', (req, res) => {
    res.send('Welcome to the Home Page');
});

app.get('/about', (req, res) => {
    res.send('This is the About Page');
});

app.get('/contact', (req, res) => {
    res.send('Contact us at: email@example.com');
});

app.use((req, res) => {
    res.status(404).send('Page Not Found');
});

app.listen(3000, () => {
    console.log('Server running on port 3000');
});