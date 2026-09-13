# Javascript examples

- [`forgot_password_button.js`](./forgot_password_button.js) — Renders a 'Forgot Password' button in a React Native UI that calls the forgot-password handler when pressed.
- [`handle_forgot_navigation.js`](./handle_forgot_navigation.js) — Navigates to the ForgotPassword screen and clears local state when the forgot-password action is triggered.
- [`reset_password_button.js`](./reset_password_button.js) — Renders a 'Reset Password' button in a React Native UI that calls the reset-password handler when pressed.
- [`request_reset_password.js`](./request_reset_password.js) — Client-side function that sends the user's email to the server to request a password reset, then stores the email in context and navigates on success.
- [`route_post_resetpassword.js`](./route_post_resetpassword.js) — Express server endpoint that looks up a user by email, generates and stores a reset token and expiration, and emails the token to the user.
- [`submit_reset_button.js`](./submit_reset_button.js) — Renders a 'Submit' button in a React Native UI that triggers the password-reset confirmation handler when pressed.
- [`confirm_reset_password.js`](./confirm_reset_password.js) — Client-side function that submits the verification code and new password to the server to confirm and complete the password reset flow.
- [`route_post_resetpasswordconfirm.js`](./route_post_resetpasswordconfirm.js) — Express server endpoint that verifies the reset token, checks password strength, hashes the new password, and updates the user's credentials.
- [`model_signin.js`](./model_signin.js) — Mongoose schema definition for the SIGNIN collection including fields for password, email, verification code, verification flag, and reset token/expiration.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/react-native-node-mongodb-forgot-password-flow)  
Parts: [shop at shillehtek.com](https://shillehtek.com)
