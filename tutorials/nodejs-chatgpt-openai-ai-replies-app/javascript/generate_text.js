// Initializes the OpenAI client with an API key and requests a text completion (text-davinci-003), then logs the generated text.
//
// Full tutorial: https://shillehtek.com/blogs/news/nodejs-chatgpt-openai-ai-replies-app
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const { Configuration, OpenAIApi } = require("openai");
const configuration = new Configuration({
    apiKey: <your api key>,
});
const openai = new OpenAIApi(configuration);


async function generateText() {
    const completion = await openai.createCompletion({
      model: "text-davinci-003",
      prompt: "How to create a simple node app",
      max_tokens: 4000,
    });
    console.log(completion.data.choices[0].text);
}
    
generateText()
