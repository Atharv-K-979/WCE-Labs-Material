import { Link } from 'react-router-dom';
import { formatDistanceToNow } from 'date-fns';
import { MessageSquare, Heart, ArrowRight } from 'lucide-react';

const PostCard = ({ post }) => {
  // Static tags for aesthetic purposes since backend doesn't support them yet
  const staticTags = ['Tech', 'Design'];

  return (
    <article className="group bg-white dark:bg-slate-900 rounded-2xl shadow-sm border border-slate-100 dark:border-slate-800 overflow-hidden hover:shadow-xl dark:hover:shadow-slate-900/50 hover:-translate-y-1 transition-all duration-300 ease-in-out flex flex-col h-full">
      {post.imageUrl && (
        <Link to={`/post/${post._id}`} className="block relative overflow-hidden aspect-[16/10]">
          <img
            src={post.imageUrl}
            alt={post.title}
            className="w-full h-full object-cover group-hover:scale-105 transition-transform duration-500"
          />
          <div className="absolute inset-0 bg-gradient-to-t from-slate-900/20 to-transparent opacity-0 group-hover:opacity-100 transition-opacity duration-300"></div>
        </Link>
      )}
      
      <div className="p-6 flex flex-col flex-grow">
        {/* Author & Time */}
        <div className="flex items-center text-sm text-slate-500 dark:text-slate-400 mb-4">
          <div className="h-6 w-6 rounded-full bg-indigo-100 dark:bg-indigo-900/50 text-indigo-600 dark:text-indigo-400 flex items-center justify-center font-bold text-xs mr-2 shrink-0">
            {post.author?.name?.charAt(0).toUpperCase() || 'A'}
          </div>
          <span className="font-medium text-slate-700 dark:text-slate-300 truncate">{post.author?.name}</span>
          <span className="mx-2 shrink-0">•</span>
          <time className="shrink-0">{formatDistanceToNow(new Date(post.createdAt), { addSuffix: true })}</time>
        </div>
        
        {/* Title & Description */}
        <Link to={`/post/${post._id}`} className="block mb-4 flex-grow">
          <h2 className="text-xl font-bold font-poppins text-slate-900 dark:text-white mb-2 group-hover:text-indigo-600 dark:group-hover:text-indigo-400 transition-colors line-clamp-2 leading-snug">
            {post.title}
          </h2>
          <p className="text-slate-500 dark:text-slate-400 line-clamp-3 text-sm leading-relaxed">
            {post.content}
          </p>
        </Link>

        {/* Tags */}
        <div className="flex flex-wrap gap-2 mb-6">
          {staticTags.map((tag) => (
            <span key={tag} className="px-2.5 py-1 bg-slate-100 dark:bg-slate-800 text-slate-600 dark:text-slate-300 text-xs font-medium rounded-md">
              {tag}
            </span>
          ))}
        </div>

        {/* Footer */}
        <div className="flex items-center justify-between border-t border-slate-100 dark:border-slate-800 pt-4 mt-auto">
          <Link
            to={`/post/${post._id}`}
            className="text-indigo-600 dark:text-indigo-400 text-sm font-semibold hover:text-indigo-700 dark:hover:text-indigo-300 flex items-center group/btn"
          >
            Read article 
            <ArrowRight className="w-4 h-4 ml-1 transform group-hover/btn:translate-x-1 transition-transform" />
          </Link>
          <div className="flex items-center space-x-4 text-slate-400 dark:text-slate-500 text-sm">
            <span className="flex items-center hover:text-rose-500 transition-colors cursor-pointer">
              <Heart className="w-4 h-4 mr-1.5" />
              <span className="font-medium">{post.likes?.length || 0}</span>
            </span>
            <span className="flex items-center hover:text-indigo-500 transition-colors cursor-pointer">
              <MessageSquare className="w-4 h-4 mr-1.5" />
              <span className="font-medium">Reply</span>
            </span>
          </div>
        </div>
      </div>
    </article>
  );
};

export default PostCard;
