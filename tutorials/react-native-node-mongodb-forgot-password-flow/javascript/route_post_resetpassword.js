// Express server endpoint that looks up a user by email, generates and stores a reset token and expiration, and emails the token to the user.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-native-node-mongodb-forgot-password-flow
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

app.post('/resetPassword', async(req, res) => {
  try {
    const email = req.body.email;
    signinTable = Schemas.SIGNIN
    const existingUser = await signinTable.findOne({ email });

    if (!existingUser) {
      console.error({ success: false, message: 'There was an Error' });
      return res.send({ success: false, message: 'If user exists, an email was sent' });
    }

    const token = await generateCode(5)
    existingUser.resettoken = token;
    existingUser.resettokenExpiration = Date.now() + 3600000;
    await existingUser.save();
    await sendEmail(email, `Here is your Reset Token ${token}`)
    return res.send({ success: true, message: 'Email sent' });

  } catch (error) {
    console.error(error)
  }
})
