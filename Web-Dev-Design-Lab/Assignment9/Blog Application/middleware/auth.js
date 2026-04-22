const jwt = require('jsonwebtoken');
const User = require('../models/User');

// Protect routes — requires authentication
exports.protect = async (req, res, next) => {
  try {
    const token = req.cookies.jwt;
    if (!token) {
      return res.redirect('/login');
    }

    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    const user = await User.findById(decoded.id);
    if (!user) {
      return res.redirect('/login');
    }

    req.user = user;
    next();
  } catch (err) {
    res.clearCookie('jwt');
    return res.redirect('/login');
  }
};

// Non-blocking check — sets res.locals for views
exports.isLoggedIn = async (req, res, next) => {
  try {
    if (req.cookies.jwt) {
      const decoded = jwt.verify(req.cookies.jwt, process.env.JWT_SECRET);
      const user = await User.findById(decoded.id);
      if (user) {
        res.locals.currentUser = user;
        req.user = user;
        return next();
      }
    }
  } catch (err) {
    // Token invalid — continue as guest
  }
  res.locals.currentUser = null;
  next();
};

// Generate JWT token
exports.signToken = (id) => {
  return jwt.sign({ id }, process.env.JWT_SECRET, {
    expiresIn: process.env.JWT_EXPIRES_IN || '7d'
  });
};
