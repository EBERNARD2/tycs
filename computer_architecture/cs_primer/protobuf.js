const fs = require('node:fs');
const { Buffer } = require('node:buffer');
const binaryData = '/Users/estradabernard/Documents/tyscs/computer_architecture/cs_primer/150.uint64';
const test = require('node:test');
const { assert } = require('node:console');

const getData = (path) => {
  // read binary files
  let data;
  try {
    data = fs.readFileSync(path);
  } catch(err){
    console.log(err);
  }
  return data;
};



function getNumberFromBuffer(data) {
  const bytes = [];
  // get variable byte size
  for (let i = 0; i < data.length; i++){
    const nonZeroByte = data[i] != 0;
    if (nonZeroByte) bytes.push(data[i]);
  }
  const uInt8Array = new Uint8Array(data);
  const arrBuffer = new ArrayBuffer(data.length, { maxByteLength: 10 });
  const dataView = new DataView(arrBuffer);
  for (let i = 0; i < uInt8Array.length; i++){
    dataView.setUint8(i, uInt8Array[i]);
  }
  // need atleast 4 bytes for Uint32 
  const byteOffset = bytes.length > 4 ? bytes.length : 4;

  return dataView.getUint32(byteOffset, false);

}



function encode(num, binaryData){

  let numberFromBuffer; 
  if (!num){
    const data = getData(binaryData);
    numberFromBuffer = getNumberFromBuffer(data);

  } else numberFromBuffer = num;
  


  const finalBytes = [];

  while (numberFromBuffer > 0){
    let isolated7bits = numberFromBuffer & 0x7f;
    numberFromBuffer >>= 7;
    if (numberFromBuffer > 0) isolated7bits |= 0x80;
    finalBytes.push(isolated7bits);
  }

  return Buffer.from(finalBytes);

}


function decode(bytes){

  let num = 0;
  for(let i = bytes.length - 1; i >= 0 ; i--){
    num <<= 7; 
    const byte = bytes[i] & 0x7f;
    num += byte;
  }

  return num;
}


console.log(decode(encode(150)));


 


