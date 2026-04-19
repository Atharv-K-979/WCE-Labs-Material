const express = require('express');
const router = express.Router();
const authMiddleware = require('../middleware/auth');
const upload = require('../middleware/upload');
const fileController = require('../controllers/fileController');

router.use(authMiddleware);

router.get('/', fileController.getAllFiles);
router.post('/upload', upload.single('file'), fileController.uploadFile);
router.get('/:filename/download', fileController.downloadFile);
router.delete('/:filename', fileController.deleteFile);

module.exports = router;
