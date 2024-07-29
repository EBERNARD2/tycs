const fs = require('node:fs');
const buffer = require('node:buffer')

const cases = fs.readFileSync('./cases');


// const processLine = (line) => {
//   const bytesToTruncate = line[0];
//   console.log(bytesToTruncate);
//   return
// }
// function getLine(idx) {
//   const start = idx;
//   // 10 is the newline character
//   while(cases[idx] != 10){
//     idx++;
//   }

//   return {
//     line,
//     idx,
//   }
// }

// let count = 1; 

// for(let i = 0; i < length; i++){
//   const lineData = getLine(i);
//   i = lineData.idx;
//   processLine(lineData.line);
//   count++
// }

// function copyBytes(buffer) {
//   const bytes = [];
//   for (let byte of buffer)
//       bytes.push(byte);
//   return bytes;
// }

// function getLineEndIndex(bytes, i) {
//   while (bytes[i] !== 10)
//     i++;
//   return i + 1;
// }

// const bytes = copyBytes(cases);
 
// const buf = Buffer.alloc(bytes.length);

// for (let i = 0; i < bytes; i++) {
//   let truncatedLength = bytes[i++];

//   const lineEnd = getLineEndIndex(bytes, i);

//   if (lineEnd >= bytes.length)
//     break;

//   let j = i;

//   while (j < lineEnd && j < truncatedLength) {

//   }

// }


// first we need to read the first byte - this is the number of bytes to read

// Then we read each character... This could be 1 to 4 bytes (sometimes 6)

  // if the bytes of the character aren't greater than the current space of the line, add the character
    // otherwise don't add the character