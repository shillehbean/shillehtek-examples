// Express POST /signup route that creates a new user record, generates a JWT email verification token, triggers the verification email, and saves the user to the database.
//
// Full tutorial: https://shillehtek.com/blogs/news/nodejs-nodemailer-gmail-app-password-authentication
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

router.post('/signup', async (req, res) => {
    const signedUpUser = new Schemas.SignUp({
        fullName: req.body.fullName,
        username: req.body.username,
        email: req.body.email,
        password: req.body.password,
        role: req.body.role
    })
    const emailToken = jwt.sign({
        username: req.body.username
    }, 'secret1234', { expiresIn: '1h' })
    emails.verifyUserEmail(req.body.fullName, req.body.email, req.body.username, emailToken)
    signedUpUser.save()
        .then(data => {
            res.json(data)
        })
        .catch(error => {
            res.json(error)
        })
})
