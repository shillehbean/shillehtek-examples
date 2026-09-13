// JSX example that renders the PasswordChecklist component with common password rules and props bound to component state.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-react-password-checklist-strong-password-ui
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

<PasswordChecklist
  rules={["minLength", "specialChar", "number", "capital", "match", "lowercase"]}
  minLength={8}
  value={password}
  valueAgain={confirmPassword}
/>
