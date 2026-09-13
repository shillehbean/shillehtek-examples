// Client-side function that sends the user's email to the server to request a password reset, then stores the email in context and navigates on success.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-native-node-mongodb-forgot-password-flow
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const { setForgotEmail } = useContext(AuthContext);
  const [email, setEmail] = useState('');
  const [error, setError] = useState('');

  const handleResetPassword = async () => {
    try {
      const data = {
        email: email,
      };
      await axios.post('http://localhost:3001/resetPassword', data, {
        headers: {
          'Content-Type': 'application/json',
        },
      }).then((response) => {
        if (response.data.success) {
          setForgotEmail(email)
          navigation.navigate('ResetPasswordConfirmation');
        } else {
          setError('There was an issue resetting your password. Please try again.');
        }
      });
    } catch (error) {
      console.error(error);
    }
  };
