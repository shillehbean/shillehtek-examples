// Root React App component that renders the Login component.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-nodejs-recaptcha-secure-login
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

import React from 'react';
import Login from './Login';
import './App.css';  // Optionally, create this file for styling

const App = () => {
  return (
    <div className="App">
      <h1>Login</h1>
      <Login />
    </div>
  );
};

export default App;
