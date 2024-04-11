const fs = require('node:fs');

const image = fs.readFileSync("./teapot.bmp")
const start = image.readUIntLE(10, 4);
const width = image.readUintLE(18,4);
const height = image.readUintLE(22, 4);

function copyHeader(img, stop){
  const header = [];
  for (let byte of img) header.push(byte);
  return header;
}

// copy header
const head = copyHeader(image, start);

// function createMatrix()
// turn image pixels to a matrix 


// rotate pixels 90 degress


// write new orentation to new bmp file

console.log(head);
