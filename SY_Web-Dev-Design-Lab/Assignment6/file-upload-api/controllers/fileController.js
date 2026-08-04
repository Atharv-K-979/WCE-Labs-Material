const path = require('path');
const fs = require('fs');
const File = require('../models/File');

exports.getAllFiles = async (req, res) => {
  try {
    const files = await File.findAll();

    res.status(200).json({
      success: true,
      message: 'Files retrieved successfully',
      data: files,
      count: files.length
    });
  } catch (error) {
    res.status(500).json({
      success: false,
      message: 'Failed to fetch files',
      error: error.message
    });
  }
};

exports.uploadFile = async (req, res) => {
  try {
    if (!req.file) {
      return res.status(400).json({
        success: false,
        message: 'No file uploaded'
      });
    }

    const fileRecord = await File.create({
      ...req.file,
      userId: req.user.id
    });

    res.status(201).json({
      success: true,
      message: 'File uploaded successfully',
      data: {
        id: fileRecord.id,
        filename: fileRecord.filename,
        originalName: fileRecord.originalName,
        mimetype: fileRecord.mimetype,
        size: fileRecord.size,
        uploadedAt: fileRecord.uploadedAt
      }
    });
  } catch (error) {
    res.status(400).json({
      success: false,
      message: error.message
    });
  }
};

exports.downloadFile = async (req, res) => {
  try {
    const fileRecord = await File.findByFilename(req.params.filename);

    if (!fileRecord) {
      return res.status(404).json({
        success: false,
        message: 'File not found'
      });
    }

    const filePath = path.join(__dirname, '..', fileRecord.path);

    if (!fs.existsSync(filePath)) {
      return res.status(404).json({
        success: false,
        message: 'File does not exist on server'
      });
    }

    res.download(filePath, fileRecord.originalName);
  } catch (error) {
    res.status(500).json({
      success: false,
      message: 'Failed to download file',
      error: error.message
    });
  }
};

exports.deleteFile = async (req, res) => {
  try {
    const deletedFile = await File.deleteByFilename(req.params.filename);

    if (!deletedFile) {
      return res.status(404).json({
        success: false,
        message: 'File not found'
      });
    }

    const filePath = path.join(__dirname, '..', deletedFile.path);

    if (fs.existsSync(filePath)) {
      fs.unlinkSync(filePath);
    }

    res.status(200).json({
      success: true,
      message: 'File deleted successfully'
    });
  } catch (error) {
    res.status(500).json({
      success: false,
      message: 'Failed to delete file',
      error: error.message
    });
  }
};
