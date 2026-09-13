# Create a backend folder, initialize npm, and install backend dependencies and dev tools like nodemon.
#
# Full tutorial: https://shillehtek.com/blogs/news/react-nodejs-recaptcha-secure-login
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

cd ..
mkdir backend
cd backend
npm init -y
npm install express axios dotenv cors jsonwebtoken express-async-handler
npm install --save-dev nodemon
