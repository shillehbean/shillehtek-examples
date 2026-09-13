// Client-side function that submits the verification code and new password to the server to confirm and complete the password reset flow.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-native-node-mongodb-forgot-password-flow
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const handleSubmit = async () => {
    if (newPassword !== confirmPassword) {
      setErrorMessage('Passwords do not match. Please try again.');
      return;
    }

    try {
      const data = {
        email: forgotEmail,
        verificationCode: verificationCode,
        password: newPassword,
      };
      const response = await axios.post('http://localhost:3001/resetPasswordConfirm', data, {
        headers: {
          'Content-Type': 'application/json',
        },
      });
      if (response.data.success) {
        setSuccessMessage('Password reset successful!');
        setErrorMessage('')
        navigation.navigate('Home');
        setForgotEmail('')
      } else {
        setErrorMessage(response.data.message);
      }
    } catch (error) {
      console.error(error);
      setErrorMessage('An error occurred. Please try again later.');
    }
  };
