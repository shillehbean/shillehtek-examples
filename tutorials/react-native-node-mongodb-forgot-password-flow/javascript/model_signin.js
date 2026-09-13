// Mongoose schema definition for the SIGNIN collection including fields for password, email, verification code, verification flag, and reset token/expiration.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-native-node-mongodb-forgot-password-flow
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const signin = new Schema({
    password: {type:String, required:true},
    email: {type:String, required:true},
    code: {type:String, required:true},
    verified: {type:Boolean, required:true},
    resettoken: {type:String, required:false},
    resettokenExpiration: {type:Date, required:false}
})

const SIGNIN = mongoose.model('SIGNIN', signin,)
const mySchemas = {
    'SIGNIN': SIGNIN,
}
