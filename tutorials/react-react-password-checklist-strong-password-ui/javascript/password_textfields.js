// Two TextField JSX inputs for password and confirm-password, wired to change handlers and toggling between text and password types.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-react-password-checklist-strong-password-ui
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

<TextField
  label='Password'
  placeholder='Enter password'
  onChange={handlePassword}
  value={password}
  variant="standard"
  type={passwordShown ? "text" : "password"}
  fullWidth
  required
/>

<TextField
  label='Confirm Password'
  placeholder='Enter password'
  onChange={handleConfirmPassword}
  value={confirmPassword}
  variant="standard"
  type={passwordShown ? "text" : "password"}
  fullWidth
  required
/>
