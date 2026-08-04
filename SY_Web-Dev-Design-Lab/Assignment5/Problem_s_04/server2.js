const express = require('express');
const app = express();

app.get('/', (req, res) => {
    res.send('Welcome to the Home Page');
});

app.get('/users/:id', (req, res) => {
    const userId = req.params.id;
    res.send(`User ID: ${userId}`);
});

app.get('/products/:category/:productId', (req, res) => {
    const { category, productId } = req.params;
    
    res.json({
        category: category,
        productId: productId
    });
});

app.use((req, res) => {
    res.status(404).send('Page Not Found');
});

app.listen(3000, () => {
    console.log('Server running on port 3000');
});