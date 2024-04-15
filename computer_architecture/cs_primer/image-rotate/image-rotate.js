const fs = require('node:fs');
const { Buffer } = require('node:buffer');

function copyHeader(img, stop){
  const header = Buffer.alloc(stop);
  for (let i = 0; i < stop; i++){
    header.writeUintLE(img[i], 0, 1);
  }
  return header;
}

function findRowSize(bitsPerPixel, width){
  // read https://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage
  return Math.ceil(((bitsPerPixel * width) / 32) * 4);
}

function rotateImage(rowSize, imgSize, image, offset){
  // to roate image we'll start at last row and iterate down
  const rowsToBuild = Math.floor(imgSize / rowSize);
  
  const rotatedImage = Buffer.alloc(imgSize);

  for (let i = rowsToBuild; i > 0; i--){
    let currentRowIdx = (i * rowSize - rowSize) + offset;
    const currentRowEnd = i * rowSize + offset;
    console.log(`Current row start: ${currentRowIdx} row end: ${currentRowEnd}`);

    while (currentRowIdx > currentRowEnd){
      rotatedImage.writeUintLE(image[currentRowIdx], 0, 1);
      currentRowIdx++; 
    }
  }
  return rotatedImage;
}

const image = fs.readFileSync("./teapot.bmp")
const start = image.readUIntLE(10, 4);
const width = image.readUintLE(18,4);
const bitsPerPixel = image.readUintLE(28, 2);
const imgSize = image.readIntLE(34,4);
const rowSize = findRowSize(bitsPerPixel, width);

// copy header
const head = copyHeader(image, start);

const rotatedImageBody = rotateImage(rowSize, imgSize, image, start);

const finalImage = Buffer.concat([head, rotatedImageBody]);

fs.writeFileSync("./rotated_image.bmp", finalImage);
console.log(finalImage.length === image.length);


