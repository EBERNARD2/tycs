const fs = require('node:fs');
const { Buffer } = require('node:buffer');
const binaryData = '/Users/estradabernard/Documents/tyscs/computer_architecture/cs_primer/maxint.uint64';

// read binary files
try {
  data = fs.readFileSync(binaryData);
} catch(err){
  console.log(err);
}

const bytes = [];
// get variable byte size
for (let i = 0; i < data.length; i++){
  const nonZeroByte = data[i] != 0;
  if (nonZeroByte) bytes.push(data[i]);
}

const buffer = Buffer.from(bytes)
console.log(buffer);

for(let b of buffer) console.log((b & 0x7F));



// // seperate 7 bits at a time... If there is a carry bit use with next byte 
// bytes.map((b, idx) => {
//   if (idx + 1 <= bytes.length){
//     bytes[idx] = b & 0x7F;
//     const carryBit = b & 0x80;
//     if (!!carryBit) addCarryBitToNextValue(idx);
//   }
// });


// function addCarryBitToNextValue(idx){
//   if (idx > bytes.length - 1){
//     // create new hex number to bytes
//     bytes.push(0x01);
//   } else {
//     bytes[idx + 1] = bytes[idx + 1] + 0x01;
//     console.log()
//   }
//   return;
// }


// console.log(bytes);


// // create new array buffer in memory with Typed array so we can directly modify data
// // should be variable length (between 1 and 10 bytes per: https://protobuf.dev/programming-guides/encoding/#varints) 
// const byteData = new ArrayBuffer(bytes.length, { maxByteLength: 10 });
// const values = new Uint8Array(byteData);
// //copy values to array with 8 bit unsigned interger array
// bytes.map((val, idx) =>  values[idx] = val);


 




