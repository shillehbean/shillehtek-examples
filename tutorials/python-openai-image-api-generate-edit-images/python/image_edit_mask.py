# Edit an existing image using a mask and a prompt via OpenAI's Image.create_edit, uploading local image and mask files and printing the resulting image URL.
#
# Full tutorial: https://shillehtek.com/blogs/news/python-openai-image-api-generate-edit-images
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import openai

# from PIL import Image

import constants

# Set up the OpenAI API client
openai.api_key = constants.API_KEY

# Image.open("dalle-2 examples/cute_cat.png").convert("RGB").save(
#     "dalle-2 examples/cute_cat.png"
# )
# Generate a image from ChatGPT
response = openai.Image.create_edit(
    image=open("dalle-2 examples/cute_cat.png", "rb"),
    mask=open("dalle-2 examples/mask.png", "rb"),
    prompt="A black and white cat with a red ball",
    n=1,
    size="512x512",
)
image_url = response["data"][0]["url"]

# Print the response
print(image_url)
