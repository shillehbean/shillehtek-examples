# Javascript examples

- [`recaptchamiddleware.js`](./recaptchamiddleware.js) — Express middleware that verifies the Google reCAPTCHA token by calling the siteverify API and blocks the request if verification fails.
- [`server.js`](./server.js) — Simple Express server that exposes a /api/login route, uses the reCAPTCHA middleware, and issues a JWT on successful credentials.
- [`login.js`](./login.js) — React Login component that renders the form, integrates react-google-recaptcha, sends login requests to the backend, and shows toast notifications.
- [`app.js`](./app.js) — Root React App component that renders the Login component.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/react-nodejs-recaptcha-secure-login)  
Parts: [shop at shillehtek.com](https://shillehtek.com)
