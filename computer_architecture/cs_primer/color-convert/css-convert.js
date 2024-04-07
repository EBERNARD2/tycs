const fs = require('node:fs');
const path = '/Users/estradabernard/Documents/tyscs/computer_architecture/cs_primer/color-convert/advanced.css';
const outputPath = '/Users/estradabernard/Documents/tyscs/computer_architecture/cs_primer/color-convert/advanced-output.css'
const FULL_HEX_LENGTH = 6;
const WITH_ALPHA_HEX_LENGTH = 8;
let buffer, cssSheet;
// read file

function populateCSSBuffer(){
  try {
    buffer = fs.readFileSync(path);
  } catch(err){
    console.log(err);
  }
  cssSheet = Buffer.from(buffer).toString();
}
function addAlpha(hex){
  const arrBuffer = new ArrayBuffer(4);
  // get last byte 
  let alphaByte = 0;
  alphaByte <<= 4; 
  const first4bits = Number(`0x${hex[6]}`);
  alphaByte |= first4bits;
  alphaByte <<= 4; 
  const second4bits = Number(`0x${hex[7]}`);
  alphaByte |= second4bits;

  return alphaByte / 256;
}

function expandHex(hex){
  const newHex = [];
  for (let val of hex){
    newHex.push(val);
    newHex.push(val);
  }
  return newHex;
}

function createRGBColor(hex = []){
  // variable path ways
  if (hex.length === 3 || hex.length === 4) hex = expandHex(hex);
  let rgb = "rgb("
  for (let i = 0; i < FULL_HEX_LENGTH; i+=2){
    let createByte = 0;
    createByte <<= 4;
    const halfByte1 = Number(`0x${hex[i]}`);
    createByte |= halfByte1;
    createByte <<= 4;
    const halfByte2= Number(`0x${hex[i+1]}`);
    createByte |= halfByte2;
    rgb += `${createByte}`;
    if (i + 2 < hex.length) rgb += " ";
  }
  if (hex.length == WITH_ALPHA_HEX_LENGTH){
    const alpha = addAlpha(hex);
    rgb += ` / ${alpha}`;
  }
  rgb += ");";
  return rgb; 
}

function writeFile(content){
  try {
    fs.writeFileSync(outputPath, content.join(""));
  } catch (err) {
    console.error(err);
  }  
  return;
}

function convertCss(){
  populateCSSBuffer();
  let content = [];

  for (let i = 0; i < cssSheet.length; i++){
    if (cssSheet[i] === '#' && cssSheet[i+1] != "h") {
      i++;
      let hexFound = false;
      const currentHex = [];

      while(!hexFound){
        if (cssSheet[i] === ";" ) hexFound = true;
        else currentHex.push(cssSheet[i]);
        i++;
      }
      const rgb = createRGBColor(currentHex);
      content.push(rgb);
      content.push('\n');
      continue;
    }
    content.push(cssSheet[i]); 
  }

  writeFile(content);
  return 0;
}


convertCss();
