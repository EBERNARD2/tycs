const fs = require('node:fs');
  

let data; 

try {
  data = fs.readFileSync("./teapot.bmp");
} catch(err){
  console.log(err);
}

const widthBuff = data.subarray(18,22);
const arrBuffer = new ArrayBuffer(widthBuff.length);
const heightBuff = data.subarray(18,22);
const dataView = new DataView(arrBuffer);

for (let i = 0; i < widthBuff.length; i++){
  dataView.setInt8(i, widthBuff[i]);
}

const width = dataView.getInt32(0, true);

for (let i = 0; i < heightBuff.length; i++){
  dataView.setInt8(i, heightBuff[i]);
}

const height = dataView.getInt32(0, true);
console.log(height, width);

// copy contents of header to new bmp file