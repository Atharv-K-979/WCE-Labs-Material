const express = require('express');
const router = express.Router();
const Post = require('../models/Post');
const Comment = require('../models/Comment');
const { protect } = require('../middleware/auth');

// GET / — Homepage: list all posts
router.get('/', async (req, res) => {
  try {
    const posts = await Post.find()
      .populate('author', 'username')
      .sort({ createdAt: -1 });
    res.render('home', { title: 'BlogVerse — Home', posts });
  } catch (err) {
    res.render('home', { title: 'BlogVerse — Home', posts: [], error: err.message });
  }
});

// GET /posts/new — New post form
router.get('/posts/new', protect, (req, res) => {
  res.render('posts/new', { title: 'Create New Post', error: null });
});

// POST /posts — Create post
router.post('/posts', protect, async (req, res) => {
  try {
    const { title, content } = req.body;
    const post = await Post.create({
      title,
      content,
      author: req.user._id
    });
    res.redirect(`/posts/${post._id}`);
  } catch (err) {
    res.render('posts/new', {
      title: 'Create New Post',
      error: err.message
    });
  }
});

// GET /posts/:id — View single post
router.get('/posts/:id', async (req, res) => {
  try {
    const post = await Post.findById(req.params.id)
      .populate('author', 'username');

    if (!post) {
      return res.status(404).render('error', {
        title: 'Post Not Found',
        message: 'The post you are looking for does not exist.'
      });
    }

    const comments = await Comment.find({ post: post._id })
      .populate('author', 'username')
      .sort({ createdAt: -1 });

    res.render('posts/show', {
      title: post.title,
      post,
      comments
    });
  } catch (err) {
    res.status(404).render('error', {
      title: 'Error',
      message: 'Post not found or invalid ID.'
    });
  }
});

// GET /posts/:id/edit — Edit post form
router.get('/posts/:id/edit', protect, async (req, res) => {
  try {
    const post = await Post.findById(req.params.id);

    if (!post) {
      return res.status(404).render('error', {
        title: 'Post Not Found',
        message: 'The post you are looking for does not exist.'
      });
    }

    // Check ownership
    if (post.author.toString() !== req.user._id.toString()) {
      return res.status(403).render('error', {
        title: 'Forbidden',
        message: 'You are not authorized to edit this post.'
      });
    }

    res.render('posts/edit', { title: 'Edit Post', post, error: null });
  } catch (err) {
    res.redirect('/');
  }
});

// PUT /posts/:id — Update post
router.put('/posts/:id', protect, async (req, res) => {
  try {
    const post = await Post.findById(req.params.id);

    if (!post) {
      return res.status(404).render('error', {
        title: 'Post Not Found',
        message: 'The post you are looking for does not exist.'
      });
    }

    // Check ownership
    if (post.author.toString() !== req.user._id.toString()) {
      return res.status(403).render('error', {
        title: 'Forbidden',
        message: 'You are not authorized to edit this post.'
      });
    }

    post.title = req.body.title;
    post.content = req.body.content;
    await post.save();

    res.redirect(`/posts/${post._id}`);
  } catch (err) {
    const post = await Post.findById(req.params.id);
    res.render('posts/edit', {
      title: 'Edit Post',
      post,
      error: err.message
    });
  }
});

// DELETE /posts/:id — Delete post
router.delete('/posts/:id', protect, async (req, res) => {
  try {
    const post = await Post.findById(req.params.id);

    if (!post) {
      return res.status(404).render('error', {
        title: 'Post Not Found',
        message: 'The post you are looking for does not exist.'
      });
    }

    // Check ownership
    if (post.author.toString() !== req.user._id.toString()) {
      return res.status(403).render('error', {
        title: 'Forbidden',
        message: 'You are not authorized to delete this post.'
      });
    }

    // Delete all comments for this post
    await Comment.deleteMany({ post: post._id });
    await Post.findByIdAndDelete(req.params.id);

    res.redirect('/');
  } catch (err) {
    res.redirect('/');
  }
});

module.exports = router;
