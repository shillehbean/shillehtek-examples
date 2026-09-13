// Export a verifyUserEmail function that sends a verification email (HTML link) to a new user using the configured transporter.
//
// Full tutorial: https://shillehtek.com/blogs/news/nodejs-nodemailer-gmail-app-password-authentication
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

module.exports = {
    verifyUserEmail: async function verifyUserEmail(name, userEmail, username, token) {
        try {
            let info = await transporter.sendMail({
                from: process.env.EMAIL_TEST,
                to: userEmail,
                subject: "Hello " + name + " please verify your email by clicking the link",
                html: process.env.homepageDev + "/verifyUserEmail/" + username + "/" + token,
            })
        } catch (err) {
            console.log(err)
        }
    }
}
