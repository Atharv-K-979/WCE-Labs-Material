import { useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import useAuthStore from '../store/useAuthStore';
import { LogOut, PenSquare, User as UserIcon, Search, Moon } from 'lucide-react';

const Navbar = () => {
  const { user, isAuthenticated, logout } = useAuthStore();
  const navigate = useNavigate();
  const [searchInput, setSearchInput] = useState('');

  const handleLogout = async () => {
    await logout();
    navigate('/');
  };

  const handleSearch = (e) => {
    e.preventDefault();
    if (searchInput.trim()) {
      navigate(`/?keyword=${encodeURIComponent(searchInput.trim())}`);
    } else {
      navigate('/');
    }
  };

  return (
    <nav className="glass sticky top-0 z-50 border-b border-slate-200/50 supports-[backdrop-filter]:bg-white/60">
      <div className="container mx-auto px-4 sm:px-6 lg:px-8 max-w-7xl">
        <div className="flex justify-between items-center h-16 md:h-20 gap-4">
          
          {/* Logo */}
          <Link to="/" className="flex-shrink-0 flex items-center">
            <span className="text-2xl font-bold font-poppins text-transparent bg-clip-text bg-gradient-to-r from-indigo-600 to-blue-500 tracking-tight">
              SimpleBlog
            </span>
          </Link>

          {/* Center Search Bar */}
          <div className="flex-1 max-w-2xl hidden md:flex justify-center px-6">
            <form onSubmit={handleSearch} className="w-full max-w-lg relative group">
              <div className="absolute inset-y-0 left-0 pl-4 flex items-center pointer-events-none">
                <Search className="h-4 w-4 text-slate-400 group-focus-within:text-indigo-500 transition-colors" />
              </div>
              <input
                type="text"
                placeholder="Search stories, topics, or authors..."
                value={searchInput}
                onChange={(e) => setSearchInput(e.target.value)}
                className="block w-full pl-11 pr-4 py-2.5 border border-slate-200 rounded-full bg-slate-50/50 text-sm placeholder-slate-400 focus:border-indigo-500 focus:bg-white focus:ring-4 focus:ring-indigo-500/10 outline-none transition-all duration-300 shadow-sm hover:shadow-md"
              />
              <button type="submit" className="hidden">Search</button>
            </form>
          </div>

          {/* Right Nav */}
          <div className="flex items-center space-x-3 md:space-x-5 flex-shrink-0">
            {/* Dark Mode Toggle Placeholder */}
            <button className="p-2 text-slate-400 hover:text-indigo-600 rounded-full hover:bg-slate-100 transition-colors">
              <Moon className="w-5 h-5" />
            </button>

            {isAuthenticated ? (
              <>
                <Link
                  to="/create-post"
                  className="hidden sm:flex items-center text-sm font-medium text-white bg-gradient-to-r from-indigo-600 to-blue-600 px-5 py-2.5 rounded-full hover:shadow-lg hover:shadow-indigo-500/30 hover:-translate-y-0.5 transition-all duration-300"
                >
                  <PenSquare className="w-4 h-4 mr-2" />
                  Write
                </Link>
                <div className="flex items-center space-x-4 pl-2 border-l border-slate-200">
                  <div className="flex items-center space-x-3 group cursor-pointer">
                    <div className="h-9 w-9 rounded-full bg-gradient-to-br from-indigo-100 to-blue-100 border border-indigo-200 flex items-center justify-center text-indigo-700 font-bold shadow-sm">
                      {user?.name?.charAt(0).toUpperCase() || 'U'}
                    </div>
                    <span className="hidden lg:block text-sm font-medium text-slate-700 group-hover:text-indigo-600 transition-colors">
                      {user?.name}
                    </span>
                  </div>
                  <button
                    onClick={handleLogout}
                    className="p-2 text-slate-400 hover:text-red-600 hover:bg-red-50 rounded-full transition-colors"
                    title="Logout"
                  >
                    <LogOut className="w-5 h-5" />
                  </button>
                </div>
              </>
            ) : (
              <>
                <Link
                  to="/login"
                  className="hidden sm:block text-sm font-medium text-slate-600 hover:text-indigo-600 transition-colors px-2"
                >
                  Log in
                </Link>
                <Link
                  to="/register"
                  className="text-sm font-medium bg-slate-900 text-white px-5 py-2.5 rounded-full hover:bg-slate-800 hover:shadow-lg hover:-translate-y-0.5 transition-all duration-300"
                >
                  Sign up
                </Link>
              </>
            )}
          </div>
        </div>
      </div>
    </nav>
  );
};

export default Navbar;
