const fs = require('node:fs');
const cases = fs.readFileSync('./cases');


function copyBytes(buffer) {
  const bytes = [];
  for (let byte of buffer)
      bytes.push(byte);
  return bytes;
}


const bytes = copyBytes(cases);
 
const buf = Buffer.alloc(bytes.length);

buf.writeUInt8(101, 0);
/**
 * For each byte in the buffer
 *   - while we haven't reached the end of the line
 *      - get the number of bytes that's allowed in line (first byte)
 *      - add encoded char if there is enough space
 *        - How do you now how many bytes to add? 
 *            - we may read 1 to 4 bytes. 1 byte would be situations where msb is 0
 *            - for variable length bytes 
 *        
 */
for (let i = 0; i < bytes.length; i++) {
  let currentByteIdx = 0;
  while (bytes[i] !== 0x0a) {
    let remainingBytesAllowed = bytes[i++];

    while (remainingBytesAllowed > 0 && bytes[i] !== 0x0A) {
      // Read multiple bytes
      if (0x80 & bytes[i]) {
        let byteSize = 0xf0 & bytes[i];

        while (byteSize) {
          buf.writeUInt8(bytes[i++], currentByteIdx++);
          byteSize >>= 1;
          remainingBytesAllowed--;
        }

      } else {
        // read one byte for ascii characters
       buf.writeUint8(bytes[i++], currentByteIdx++);
       remainingBytesAllowed--;
      }
    }
    buf.writeUint8(0x0A, currentByteIdx++);
  }
}

console.log(buf.toString("utf-8", 0));
