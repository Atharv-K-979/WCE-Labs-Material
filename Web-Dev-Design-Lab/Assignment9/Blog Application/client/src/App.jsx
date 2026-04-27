import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import { Toaster } from 'react-hot-toast';
import { useEffect } from 'react';
import useAuthStore from './store/useAuthStore';
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

  useEffect(() => {
    checkAuth();
  }, [checkAuth]);

  if (isLoading) {
    return (
      <div className="flex items-center justify-center min-h-screen bg-slate-50">
        <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-indigo-600"></div>
      </div>
    );
  }

  return (
    <BrowserRouter>
      <div className="min-h-screen bg-slate-50 flex flex-col font-sans text-slate-900 selection:bg-indigo-100 selection:text-indigo-900">
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
        <footer className="bg-white border-t border-slate-200 py-8 mt-auto">
          <div className="container mx-auto px-4 max-w-7xl flex flex-col md:flex-row items-center justify-between gap-4">
            <div className="text-slate-500 text-sm">
              &copy; {new Date().getFullYear()} SimpleBlog. All rights reserved.
            </div>
            <div className="flex items-center space-x-6">
              <a href="#" className="text-slate-400 hover:text-indigo-600 transition-colors" title="Website">
                <Globe className="h-5 w-5" />
              </a>
              <a href="#" className="text-slate-400 hover:text-indigo-600 transition-colors" title="Contact">
                <Mail className="h-5 w-5" />
              </a>
              <a href="#" className="text-slate-400 hover:text-indigo-600 transition-colors" title="Community">
                <MessageCircle className="h-5 w-5" />
              </a>
            </div>
          </div>
        </footer>
      </div>
      <Toaster 
        position="bottom-right" 
        toastOptions={{
          className: 'bg-white text-slate-900 border border-slate-100 shadow-lg rounded-xl font-medium',
          duration: 4000,
        }} 
      />
    </BrowserRouter>
  );
}

export default App;
