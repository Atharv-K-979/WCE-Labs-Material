import express from 'express';
import { getCommentsForPost, createComment, deleteComment } from '../controllers/commentController.js';
import { protect } from '../middleware/auth.js';

const router = express.Router({ mergeParams: true });

router.route('/posts/:postId/comments')
  .get(getCommentsForPost);

router.route('/comments')
  .post(protect, createComment);

router.route('/comments/:id')
  .delete(protect, deleteComment);

export default router;
