const express = require('express');
const router = express.Router();
const User = require('../models/User');
const { signToken, protect } = require('../middleware/auth');

// GET /signup
router.get('/signup', (req, res) => {
  if (res.locals.currentUser) return res.redirect('/');
  res.render('auth/signup', { title: 'Sign Up', error: null });
});

// POST /signup
router.post('/signup', async (req, res) => {
  try {
    const { username, email, password, confirmPassword } = req.body;

    // Validate passwords match
    if (password !== confirmPassword) {
      return res.render('auth/signup', {
        title: 'Sign Up',
        error: 'Passwords do not match'
      });
    }

    // Check if user already exists
    const existingUser = await User.findOne({ $or: [{ email }, { username }] });
    if (existingUser) {
      return res.render('auth/signup', {
        title: 'Sign Up',
        error: 'Username or email already exists'
      });
    }

    const user = await User.create({ username, email, password });
    const token = signToken(user._id);

    res.cookie('jwt', token, {
      httpOnly: true,
      maxAge: 7 * 24 * 60 * 60 * 1000, // 7 days
      secure: process.env.NODE_ENV === 'production'
    });

    res.redirect('/');
  } catch (err) {
    res.render('auth/signup', {
      title: 'Sign Up',
      error: err.message
    });
  }
});

// GET /login
router.get('/login', (req, res) => {
  if (res.locals.currentUser) return res.redirect('/');
  res.render('auth/login', { title: 'Log In', error: null });
});

// POST /login
router.post('/login', async (req, res) => {
  try {
    const { email, password } = req.body;

    if (!email || !password) {
      return res.render('auth/login', {
        title: 'Log In',
        error: 'Please provide email and password'
      });
    }

    const user = await User.findOne({ email });
    if (!user || !(await user.comparePassword(password))) {
      return res.render('auth/login', {
        title: 'Log In',
        error: 'Invalid email or password'
      });
    }

    const token = signToken(user._id);

    res.cookie('jwt', token, {
      httpOnly: true,
      maxAge: 7 * 24 * 60 * 60 * 1000,
      secure: process.env.NODE_ENV === 'production'
    });

    res.redirect('/');
  } catch (err) {
    res.render('auth/login', {
      title: 'Log In',
      error: 'Something went wrong. Please try again.'
    });
  }
});

// GET /logout
router.get('/logout', (req, res) => {
  res.clearCookie('jwt');
  res.redirect('/');
});

module.exports = router;
