const fs = require('node:fs');

const packet = fs.readFileSync('./synflood.pcap');

const length = packet.readUIntLE(36,4);
const l = packet.readUIntLE(32,4);


const packet1Start = 40;

const packet1end = 44;

let count = 0; 

while(count != packet1end){
    console.log(packet[packet1Start]);
    count++;
}
