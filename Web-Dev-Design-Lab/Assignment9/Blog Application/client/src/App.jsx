import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import { Toaster } from 'react-hot-toast';
import { useEffect } from 'react';
import useAuthStore from './store/useAuthStore';

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
      <div className="flex items-center justify-center min-h-screen">
        <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-indigo-600"></div>
      </div>
    );
  }

  return (
    <BrowserRouter>
      <div className="min-h-screen bg-gray-50 flex flex-col">
        <Navbar />
        <main className="flex-grow container mx-auto px-4 py-8">
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
        <footer className="bg-white border-t py-6 mt-auto">
          <div className="container mx-auto px-4 text-center text-gray-500">
            &copy; {new Date().getFullYear()} Simple Blog. All rights reserved.
          </div>
        </footer>
      </div>
      <Toaster position="bottom-right" />
    </BrowserRouter>
  );
}

export default App;
