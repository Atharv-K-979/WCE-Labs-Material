const express = require('express');
const router = express.Router();
const authMiddleware = require('../middleware/auth');
const bookController = require('../controllers/bookController');

router.use(authMiddleware);

router.get('/', bookController.getAllBooks);
router.get('/:id', bookController.getBookById);
router.post('/', bookController.createBook);
router.put('/:id', bookController.updateBook);
router.delete('/:id', bookController.deleteBook);

module.exports = router;
