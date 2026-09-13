// Load environment variables and create a Nodemailer transporter configured for Gmail using credentials from environment variables (app password).
//
// Full tutorial: https://shillehtek.com/blogs/news/nodejs-nodemailer-gmail-app-password-authentication
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

var dotenv = require("dotenv")
dotenv.config()

const nodemailer = require("nodemailer");
let transporter = nodemailer.createTransport({
    service: 'Gmail',
    host: 'smtp.gmail.com',
    secure: false,
    auth: {
        user: process.env.EMAIL_TEST,
        pass: process.env.EMAIL_TEST_APP_PSWD
    },
})
