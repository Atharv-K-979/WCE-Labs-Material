import { useState, useEffect } from 'react';
import { useSearchParams } from 'react-router-dom';
import api from '../lib/axios';
import PostCard from '../components/PostCard';
import { BookOpen, Sparkles } from 'lucide-react';

const SkeletonCard = () => (
  <div className="bg-white rounded-2xl shadow-sm border border-slate-100 overflow-hidden h-full flex flex-col animate-pulse">
    <div className="w-full aspect-[16/10] bg-slate-200"></div>
    <div className="p-6 flex flex-col flex-grow">
      <div className="flex items-center mb-4">
        <div className="h-6 w-6 rounded-full bg-slate-200 mr-2 shrink-0"></div>
        <div className="h-4 bg-slate-200 rounded w-1/3"></div>
      </div>
      <div className="h-6 bg-slate-200 rounded w-3/4 mb-2"></div>
      <div className="h-6 bg-slate-200 rounded w-1/2 mb-4"></div>
      <div className="space-y-2 mb-6">
        <div className="h-4 bg-slate-200 rounded w-full"></div>
        <div className="h-4 bg-slate-200 rounded w-5/6"></div>
      </div>
      <div className="mt-auto pt-4 border-t border-slate-100 flex justify-between">
        <div className="h-4 bg-slate-200 rounded w-1/4"></div>
        <div className="flex space-x-2">
          <div className="h-4 w-4 bg-slate-200 rounded"></div>
          <div className="h-4 w-4 bg-slate-200 rounded"></div>
        </div>
      </div>
    </div>
  </div>
);

const Home = () => {
  const [posts, setPosts] = useState([]);
  const [loading, setLoading] = useState(true);
  const [totalPages, setTotalPages] = useState(1);
  const [searchParams, setSearchParams] = useSearchParams();
  
  const page = parseInt(searchParams.get('page')) || 1;
  const keyword = searchParams.get('keyword') || '';

  useEffect(() => {
    const fetchPosts = async () => {
      try {
        setLoading(true);
        const { data } = await api.get(`/posts?page=${page}&keyword=${keyword}`);
        setPosts(data.posts);
        setTotalPages(data.pages);
      } catch (error) {
        console.error('Error fetching posts:', error);
      } finally {
        setLoading(false);
      }
    };

    fetchPosts();
  }, [page, keyword]);

  const handlePageChange = (newPage) => {
    setSearchParams({ keyword, page: newPage });
    window.scrollTo({ top: 0, behavior: 'smooth' });
  };

  return (
    <div className="max-w-7xl mx-auto w-full">
      <div className="flex flex-col md:flex-row justify-between items-end mb-10 gap-4">
        <div>
          <h1 className="text-4xl md:text-5xl font-extrabold font-poppins text-slate-900 tracking-tight mb-3">
            {keyword ? 'Search Results' : 'Latest Stories'}
          </h1>
          <p className="text-slate-500 text-lg flex items-center">
            <Sparkles className="w-5 h-5 mr-2 text-indigo-500" />
            {keyword ? `Showing results for "${keyword}"` : 'Discover insights, stories, and ideas from our community.'}
          </p>
        </div>
      </div>

      {loading ? (
        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8">
          {[...Array(6)].map((_, i) => (
            <SkeletonCard key={i} />
          ))}
        </div>
      ) : posts.length === 0 ? (
        <div className="flex flex-col items-center justify-center py-24 px-4 bg-white rounded-3xl shadow-sm border border-slate-100 border-dashed text-center">
          <div className="h-20 w-20 bg-indigo-50 rounded-full flex items-center justify-center mb-6">
            <BookOpen className="w-10 h-10 text-indigo-500" />
          </div>
          <h3 className="text-2xl font-bold font-poppins text-slate-900 mb-2">No stories found</h3>
          <p className="text-slate-500 max-w-md mx-auto mb-8 text-lg">
            {keyword 
              ? `We couldn't find anything matching "${keyword}". Try adjusting your search.`
              : 'It seems quiet here. Be the first to share your thoughts with the community!'}
          </p>
          {!keyword && (
            <a 
              href="/create-post" 
              className="inline-flex items-center text-white bg-slate-900 px-6 py-3 rounded-full font-medium hover:bg-slate-800 hover:shadow-lg hover:-translate-y-0.5 transition-all duration-300"
            >
              Write a story
            </a>
          )}
        </div>
      ) : (
        <>
          <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8">
            {posts.map((post) => (
              <PostCard key={post._id} post={post} />
            ))}
          </div>

          {/* Pagination */}
          {totalPages > 1 && (
            <div className="flex justify-center mt-16 space-x-2">
              <button
                onClick={() => handlePageChange(page - 1)}
                disabled={page === 1}
                className="px-5 py-2.5 rounded-full text-sm font-medium transition-all duration-300 disabled:opacity-50 disabled:cursor-not-allowed border border-slate-200 text-slate-600 bg-white hover:bg-slate-50 hover:text-slate-900"
              >
                Previous
              </button>
              
              <div className="hidden sm:flex space-x-1">
                {[...Array(totalPages).keys()].map((p) => (
                  <button
                    key={p + 1}
                    onClick={() => handlePageChange(p + 1)}
                    className={`w-10 h-10 rounded-full text-sm font-medium transition-all duration-300 flex items-center justify-center ${
                      page === p + 1
                        ? 'bg-indigo-600 text-white shadow-md shadow-indigo-500/20'
                        : 'text-slate-600 hover:bg-slate-100'
                    }`}
                  >
                    {p + 1}
                  </button>
                ))}
              </div>

              <button
                onClick={() => handlePageChange(page + 1)}
                disabled={page === totalPages}
                className="px-5 py-2.5 rounded-full text-sm font-medium transition-all duration-300 disabled:opacity-50 disabled:cursor-not-allowed border border-slate-200 text-slate-600 bg-white hover:bg-slate-50 hover:text-slate-900"
              >
                Next
              </button>
            </div>
          )}
        </>
      )}
    </div>
  );
};

export default Home;
