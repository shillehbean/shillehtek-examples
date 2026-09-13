# Javascript examples

- [`mailer.js`](./mailer.js) — Load environment variables and create a Nodemailer transporter configured for Gmail using credentials from environment variables (app password).
- [`emailservice.js`](./emailservice.js) — Export a verifyUserEmail function that sends a verification email (HTML link) to a new user using the configured transporter.
- [`routes_imports.js`](./routes_imports.js) — Import the email service module so it can be used in route handlers.
- [`signuproute.js`](./signuproute.js) — Express POST /signup route that creates a new user record, generates a JWT email verification token, triggers the verification email, and saves the user to the database.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/nodejs-nodemailer-gmail-app-password-authentication)  
Parts: [shop at shillehtek.com](https://shillehtek.com)
