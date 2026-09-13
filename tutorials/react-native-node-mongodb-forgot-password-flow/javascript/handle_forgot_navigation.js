// Navigates to the ForgotPassword screen and clears local state when the forgot-password action is triggered.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-native-node-mongodb-forgot-password-flow
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const handleForgotPass = () => {
    navigation.navigate('ForgotPassword')
    clearStates()
  }
