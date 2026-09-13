// Express server endpoint that verifies the reset token, checks password strength, hashes the new password, and updates the user's credentials.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-native-node-mongodb-forgot-password-flow
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

app.post('/resetPasswordConfirm', async (req, res) => {
  try {
    signinTable = Schemas.SIGNIN
    const email = req.body.email
    const verificationCode = req.body.verificationCode
    const password = req.body.password
    const user = await signinTable.findOne({ email });
    passwordStrength = isStrongPassword(password)
    if (!passwordStrength.strong) {
      return res.send({ success: false, message: passwordStrength.missingRequirements.join('\n') });
    }
    if (!user || user.resettoken !== verificationCode) {
      return res.status(400).send({ success: false });
    }
    if (user.resettokenExpiration < new Date()) {
      return res.status(400).send({ success: false, message: 'Token has expired.' });
    }

    const hashedPassword = await bcrypt.hash(password, 10);
    user.password = hashedPassword;
    user.token = '';
    user.tokenExpiration = null;
    await user.save();
    return res.status(200).send({ success: true });
    
  } catch (error) {
    console.error(error);
    return res.status(500).send({ success: false, message: 'An error occurred. Please try again later.' });
  }
});
