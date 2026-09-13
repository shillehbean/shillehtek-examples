// Loads an image with Sharp, reads raw pixel data, replaces pure white pixels with a specific RGBA value, and saves the result to new.png.
//
// Full tutorial: https://shillehtek.com/blogs/news/nodejs-sharp-edit-pixels-export-png
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const sharp = require("sharp")

imagePath = 'original.png'
maskImage = 'mask_file.png'
const width = 300; 
const height = 200;

async function editPixels(imagePath) {
  const buffer = await sharp(imagePath)
  .ensureAlpha()
  .raw()
  .toBuffer({ resolveWithObject: true })
  .then( async ({ data, info }) => {
    const { width, height, channels } = info;
    for (let i = 0; i < data.length; i += channels) {
      if ([data[i]] == 255 && [data[i + 1]] == 255 
         && [data[i + 2]] == 255) {
          data[i] = 100;
          data[i + 1] = 200;
          data[i + 2] = 30;
          data[i + 3] = 125;
        }
    }
   await sharp(data, { raw: { width, height, channels } })
        .toFormat('png')
        .toFile('new.png')
  })
}

editPixels(maskImage)
