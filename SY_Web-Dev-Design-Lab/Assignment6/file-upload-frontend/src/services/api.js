const API_BASE_URL = '/api';

const getAuthHeader = () => {
  const token = localStorage.getItem('token');
  return token ? { 'Authorization': `Bearer ${token}` } : {};
};

export const authAPI = {
  login: async (email, password) => {
    console.log('API: Making login request to', `${API_BASE_URL}/auth/login`);
    const response = await fetch(`${API_BASE_URL}/auth/login`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ email, password })
    });
    console.log('API: Login fetch response status:', response.status, response.statusText);
    const data = await response.json();
    console.log('API: Login response data:', data);
    return data;
  },

  register: async (email, password, name) => {
    console.log('API: Making register request to', `${API_BASE_URL}/auth/register`);
    const response = await fetch(`${API_BASE_URL}/auth/register`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ email, password, name })
    });
    console.log('API: Register fetch response status:', response.status, response.statusText);
    const data = await response.json();
    console.log('API: Register response data:', data);
    return data;
  }
};

export const filesAPI = {
  getAll: async () => {
    const response = await fetch(`${API_BASE_URL}/files`, {
      headers: getAuthHeader()
    });
    return response.json();
  },

  upload: async (formData) => {
    const token = localStorage.getItem('token');
    const response = await fetch(`${API_BASE_URL}/files/upload`, {
      method: 'POST',
      headers: {
        'Authorization': `Bearer ${token}`
      },
      body: formData
    });
    return response.json();
  },

  download: async (filename) => {
    const token = localStorage.getItem('token');
    const response = await fetch(`${API_BASE_URL}/files/${filename}/download`, {
      headers: {
        'Authorization': `Bearer ${token}`
      }
    });

    if (!response.ok) {
      throw new Error('Download failed');
    }

    return response.blob();
  },

  delete: async (filename) => {
    const response = await fetch(`${API_BASE_URL}/files/${filename}`, {
      method: 'DELETE',
      headers: getAuthHeader()
    });
    return response.json();
  }
};
