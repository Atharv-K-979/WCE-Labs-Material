import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import { Toaster } from 'react-hot-toast';
import { useEffect } from 'react';
import useAuthStore from './store/useAuthStore';
import useThemeStore from './store/useThemeStore';
import { Globe, Mail, MessageCircle } from 'lucide-react';

// Components
import Navbar from './components/Navbar';

// Pages
import Home from './pages/Home';
import Login from './pages/Login';
import Register from './pages/Register';
import CreateEditPost from './pages/CreateEditPost';
import PostDetails from './pages/PostDetails';

function App() {
  const { checkAuth, isAuthenticated, isLoading } = useAuthStore();
  const { theme } = useThemeStore();

  useEffect(() => {
    checkAuth();
  }, [checkAuth]);

  useEffect(() => {
    if (theme === 'dark') {
      document.documentElement.classList.add('dark');
    } else {
      document.documentElement.classList.remove('dark');
    }
  }, [theme]);

  if (isLoading) {
    return (
      <div className="flex items-center justify-center min-h-screen bg-slate-50 dark:bg-slate-900 transition-colors duration-300">
        <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-indigo-600 dark:border-indigo-400"></div>
      </div>
    );
  }

  return (
    <BrowserRouter>
      <div className="min-h-screen flex flex-col font-sans selection:bg-indigo-100 selection:text-indigo-900 dark:selection:bg-indigo-900/30 dark:selection:text-indigo-200">
        <Navbar />
        <main className="flex-grow container mx-auto px-4 sm:px-6 lg:px-8 py-8 md:py-12 max-w-7xl">
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/login" element={!isAuthenticated ? <Login /> : <Navigate to="/" />} />
            <Route path="/register" element={!isAuthenticated ? <Register /> : <Navigate to="/" />} />
            <Route path="/post/:id" element={<PostDetails />} />
            
            {/* Protected Routes */}
            <Route path="/create-post" element={isAuthenticated ? <CreateEditPost /> : <Navigate to="/login" />} />
            <Route path="/edit-post/:id" element={isAuthenticated ? <CreateEditPost /> : <Navigate to="/login" />} />
          </Routes>
        </main>
        <footer className="bg-white dark:bg-slate-900 border-t border-slate-200 dark:border-slate-800 py-8 mt-auto transition-colors duration-300">
          <div className="container mx-auto px-4 max-w-7xl flex flex-col md:flex-row items-center justify-between gap-4">
            <div className="text-slate-500 dark:text-slate-400 text-sm">
              &copy; {new Date().getFullYear()} SimpleBlog. All rights reserved.
            </div>
            <div className="flex items-center space-x-6">
              <a href="#" className="text-slate-400 hover:text-indigo-600 dark:hover:text-indigo-400 transition-colors" title="Website">
                <Globe className="h-5 w-5" />
              </a>
              <a href="#" className="text-slate-400 hover:text-indigo-600 dark:hover:text-indigo-400 transition-colors" title="Contact">
                <Mail className="h-5 w-5" />
              </a>
              <a href="#" className="text-slate-400 hover:text-indigo-600 dark:hover:text-indigo-400 transition-colors" title="Community">
                <MessageCircle className="h-5 w-5" />
              </a>
            </div>
          </div>
        </footer>
      </div>
      <Toaster 
        position="bottom-right" 
        toastOptions={{
          className: 'bg-white dark:bg-slate-800 text-slate-900 dark:text-slate-100 border border-slate-100 dark:border-slate-700 shadow-lg rounded-xl font-medium',
          duration: 4000,
        }} 
      />
    </BrowserRouter>
  );
}

export default App;
