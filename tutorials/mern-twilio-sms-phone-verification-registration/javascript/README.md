# Javascript examples

- [`registration.js`](./registration.js) — React Native registration component that collects name, password, and phone number, posts them to the backend /register endpoint, and navigates to the verification screen on success.
- [`verification.js`](./verification.js) — React Native verification component that accepts a verification code, posts it to the backend /verify endpoint to confirm the phone number, and shows the verification status to the user.
- [`server.js`](./server.js) — Express.js server that connects to MongoDB via Mongoose, exposes a /register route that saves a user, generates a verification code, and sends the code via Twilio SMS.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/mern-twilio-sms-phone-verification-registration)  
Parts: [shop at shillehtek.com](https://shillehtek.com)
