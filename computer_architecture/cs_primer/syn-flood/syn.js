const fs = require('node:fs');
const packet = fs.readFileSync('./synflood.pcap');
const { buffer } = require('node:buffer');


const headBuff = Buffer.alloc(24);
const magicNumber = packet.readUIntLE(0,4);

const majorVersion = packet.readUintLE(4,2);
const minorVersion = packet.readUintLE(6,2);
const linkLayerHeader = packet.readUintLE(20,4);

const packetBuffs = [];



for (let i = 24; i < packet.length; i++){
  const perPacketLength = packet.readUintLE(i + 8, 4);
  const truncatedLength = packet.readUintLE(i + 12, 4);
  console.log(perPacketLength, truncatedLength);
  console.log(perPacketLength === truncatedLength, "Equal lengths");
  
  const buffer = Buffer.alloc(perPacketLength);

  i += 16; 

  let buffCount = 0;
  while (buffCount < perPacketLength){
    buffer.writeUInt8(packet[i], buffCount);
    buffCount++;
    i++;
  }
  console.log(i, 'i');

  packetBuffs.push(buffer);

}

console.log(packetBuffs);
//   const packetLength = packet.readUintLE(i + 8, 4);
//   console.log(packetLength)
//   variablePacketLengths.push(packetLength);
//   i = i + 16 + packetLength;
//   console.log(i);
// }

// console.log(variablePacketLengths);


