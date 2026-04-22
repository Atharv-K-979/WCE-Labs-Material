const express = require('express');
const router = express.Router();
const Comment = require('../models/Comment');
const Post = require('../models/Post');
const { protect } = require('../middleware/auth');

// POST /posts/:id/comments — Add comment
router.post('/posts/:id/comments', protect, async (req, res) => {
  try {
    const post = await Post.findById(req.params.id);
    if (!post) {
      return res.status(404).redirect('/');
    }

    await Comment.create({
      text: req.body.text,
      author: req.user._id,
      post: post._id
    });

    res.redirect(`/posts/${post._id}`);
  } catch (err) {
    res.redirect(`/posts/${req.params.id}`);
  }
});

// DELETE /posts/:postId/comments/:commentId — Delete own comment
router.delete('/posts/:postId/comments/:commentId', protect, async (req, res) => {
  try {
    const comment = await Comment.findById(req.params.commentId);

    if (!comment) {
      return res.redirect(`/posts/${req.params.postId}`);
    }

    // Only the comment author can delete it
    if (comment.author.toString() !== req.user._id.toString()) {
      return res.redirect(`/posts/${req.params.postId}`);
    }

    await Comment.findByIdAndDelete(req.params.commentId);
    res.redirect(`/posts/${req.params.postId}`);
  } catch (err) {
    res.redirect(`/posts/${req.params.postId}`);
  }
});

module.exports = router;
