import { useState, useEffect } from 'react';
import { useParams, useNavigate, Link } from 'react-router-dom';
import { formatDistanceToNow } from 'date-fns';
import { Edit2, Trash2, Heart, ArrowLeft } from 'lucide-react';
import toast from 'react-hot-toast';
import api from '../lib/axios';
import useAuthStore from '../store/useAuthStore';
import CommentSection from '../components/CommentSection';

const PostDetails = () => {
  const { id } = useParams();
  const navigate = useNavigate();
  const { user, isAuthenticated } = useAuthStore();
  
  const [post, setPost] = useState(null);
  const [loading, setLoading] = useState(true);
  const [likeLoading, setLikeLoading] = useState(false);

  useEffect(() => {
    const fetchPost = async () => {
      try {
        const { data } = await api.get(`/posts/${id}`);
        setPost(data);
      } catch (error) {
        toast.error('Post not found');
        navigate('/');
      } finally {
        setLoading(false);
      }
    };
    fetchPost();
  }, [id, navigate]);

  const handleDelete = async () => {
    if (window.confirm('Are you sure you want to delete this post?')) {
      try {
        await api.delete(`/posts/${id}`);
        toast.success('Post deleted successfully');
        navigate('/');
      } catch (error) {
        toast.error('Failed to delete post');
      }
    }
  };

  const handleLike = async () => {
    if (!isAuthenticated) {
      toast.error('Please login to like this post');
      return;
    }
    
    try {
      setLikeLoading(true);
      const { data } = await api.put(`/posts/${id}/like`);
      setPost({ ...post, likes: data.likes });
    } catch (error) {
      toast.error('Failed to like post');
    } finally {
      setLikeLoading(false);
    }
  };

  if (loading) {
    return (
      <div className="flex justify-center py-20">
        <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-indigo-600"></div>
      </div>
    );
  }

  if (!post) return null;

  const isAuthor = user?._id === post.author?._id;
  const hasLiked = post.likes?.some(likeId => 
    typeof likeId === 'object' ? likeId._id === user?._id : likeId === user?._id
  );

  return (
    <article className="max-w-4xl mx-auto">
      <button 
        onClick={() => navigate(-1)}
        className="flex items-center text-gray-500 hover:text-indigo-600 mb-6 transition-colors"
      >
        <ArrowLeft className="w-4 h-4 mr-1" />
        Back
      </button>

      <div className="bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden">
        {post.imageUrl && (
          <img
            src={post.imageUrl}
            alt={post.title}
            className="w-full h-72 md:h-96 object-cover"
          />
        )}
        
        <div className="p-8 md:p-12">
          <div className="flex flex-wrap items-center justify-between gap-4 mb-6">
            <div className="flex items-center text-sm text-gray-500">
              <span className="font-medium text-gray-900 bg-gray-100 px-3 py-1 rounded-full">
                {post.author?.name}
              </span>
              <span className="mx-3">•</span>
              <time>{formatDistanceToNow(new Date(post.createdAt), { addSuffix: true })}</time>
            </div>

            {isAuthor && (
              <div className="flex items-center space-x-2 border rounded-lg p-1 bg-gray-50">
                <Link
                  to={`/edit-post/${post._id}`}
                  className="p-2 text-gray-600 hover:text-indigo-600 hover:bg-white rounded-md transition-all"
                  title="Edit post"
                >
                  <Edit2 className="w-4 h-4" />
                </Link>
                <button
                  onClick={handleDelete}
                  className="p-2 text-gray-600 hover:text-red-600 hover:bg-white rounded-md transition-all"
                  title="Delete post"
                >
                  <Trash2 className="w-4 h-4" />
                </button>
              </div>
            )}
          </div>

          <h1 className="text-3xl md:text-5xl font-bold text-gray-900 mb-8 leading-tight">
            {post.title}
          </h1>

          <div className="prose prose-lg max-w-none text-gray-700 leading-relaxed whitespace-pre-wrap">
            {post.content}
          </div>

          <div className="mt-12 pt-8 border-t border-gray-100 flex items-center">
            <button
              onClick={handleLike}
              disabled={likeLoading}
              className={`flex items-center space-x-2 px-4 py-2 rounded-full border transition-all ${
                hasLiked 
                  ? 'bg-red-50 border-red-100 text-red-600' 
                  : 'bg-white border-gray-200 text-gray-600 hover:bg-gray-50'
              }`}
            >
              <Heart className={`w-5 h-5 ${hasLiked ? 'fill-current' : ''}`} />
              <span className="font-medium">{post.likes?.length || 0} Likes</span>
            </button>
          </div>
        </div>
      </div>

      <div className="mt-12">
        <CommentSection postId={post._id} />
      </div>
    </article>
  );
};

export default PostDetails;
