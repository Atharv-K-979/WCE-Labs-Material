import { Link } from 'react-router-dom';
import { formatDistanceToNow } from 'date-fns';
import { MessageSquare, Heart } from 'lucide-react';

const PostCard = ({ post }) => {
  return (
    <article className="bg-white rounded-xl shadow-sm border border-gray-100 overflow-hidden hover:shadow-md transition-shadow duration-300">
      {post.imageUrl && (
        <Link to={`/post/${post._id}`}>
          <img
            src={post.imageUrl}
            alt={post.title}
            className="w-full h-48 object-cover"
          />
        </Link>
      )}
      <div className="p-6">
        <div className="flex items-center text-sm text-gray-500 mb-3">
          <span className="font-medium text-gray-900">{post.author?.name}</span>
          <span className="mx-2">•</span>
          <time>{formatDistanceToNow(new Date(post.createdAt), { addSuffix: true })}</time>
        </div>
        
        <Link to={`/post/${post._id}`} className="block group">
          <h2 className="text-xl font-bold text-gray-900 mb-2 group-hover:text-indigo-600 transition-colors line-clamp-2">
            {post.title}
          </h2>
          <p className="text-gray-600 line-clamp-3 mb-4 text-sm leading-relaxed">
            {post.content}
          </p>
        </Link>

        <div className="flex items-center justify-between border-t border-gray-50 pt-4 mt-4">
          <Link
            to={`/post/${post._id}`}
            className="text-indigo-600 text-sm font-medium hover:text-indigo-800"
          >
            Read more →
          </Link>
          <div className="flex items-center space-x-4 text-gray-500 text-sm">
            <span className="flex items-center">
              <Heart className="w-4 h-4 mr-1" />
              {post.likes?.length || 0}
            </span>
            <span className="flex items-center">
              <MessageSquare className="w-4 h-4 mr-1" />
              Comments
            </span>
          </div>
        </div>
      </div>
    </article>
  );
};

export default PostCard;
