const { Buffer } = require('node:buffer');

function conceal(message) {
  if (message.length > 6){
    console.error(`Error: cannot conceal ${message}. Too long.`);
    process.exit(1);
  }

  const arrayBuffer = new ArrayBuffer(8);
  const buffer = Buffer.from(arrayBuffer);
  // set all exponent bits on
  buffer[0] = 0x7f;
  buffer[1] = 0xf0;

  // set remaining bytes (up to 6) to message value
  for (let i = 0; i < message.length; i++) 
    buffer[i + 2] = message[i].charCodeAt(0);
  

  // JS doesn't really deal with binary data elegantly so we neew to turn array buffer to a data view to extract value from buffer in memory
  const view = new DataView(arrayBuffer);

  return view.getFloat64(0);
}


/**
 * Note, extra steps need to be taken this solution as Javascript doesn't have an efficient solution to dealing with raw binary data.
 */

function extract(value) {
  // Create 8 byte buffer in memory
  const arrBuff = new ArrayBuffer(8);

  // Create data view to extract value
  const data = new DataView(arrBuff);
  // set buffer in memory to bytes from value
  data.setFloat64(0, value);

  // now turn data into a node buffer so we can extract data one byte at a time
  const buffer = Buffer.from(arrBuff);
  // start at byte offset 2 to skip over exponent and sign bits of floating point num
  let i = 1;

  let message = "";

  while (buffer[i++])
      message += String.fromCharCode(buffer[i]);

  return message;
}



const message = conceal("hello");

console.log(message);
console.log(message + 10);
console.log(message * 2);
console.log(extract(message));


