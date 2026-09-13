# Create a variation of an existing image using OpenAI's Image.create_variation and print the resulting image URL.
#
# Full tutorial: https://shillehtek.com/blogs/news/python-openai-image-api-generate-edit-images
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import openai

import constants

openai.api_key = constants.API_KEY

response = openai.Image.create_variation(
    image=open("dalle-2 examples/cute_cat.png", "rb"),
    n=1,
    size="512x512",
)
image_url = response["data"][0]["url"]

# Print the response
print(image_url)
