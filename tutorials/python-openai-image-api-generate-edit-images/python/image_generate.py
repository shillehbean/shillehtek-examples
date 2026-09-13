# Generate an image from a text prompt using OpenAI's Image.create and print the resulting image URL.
#
# Full tutorial: https://shillehtek.com/blogs/news/python-openai-image-api-generate-edit-images
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import openai

import constants

# Set up the OpenAI API client
openai.api_key = constants.API_KEY

description = "a stained glass window with an image of fruits"

# Generate a image from ChatGPT
response = openai.Image.create(prompt=description, n=1, size="512x512")
image_url = response["data"][0]["url"]

# Print the response
print(image_url)
