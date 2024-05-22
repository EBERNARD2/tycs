const fs = require('node:fs');
const { Buffer } = require('node:buffer');


if (process.argv.length === 2) {
    console.error('Please add file to parse');
    process.exit(1);
}



const instructionType = () => {};

const symbol = () => {};

const dest = () => {};

const comp = () => {};

const jump = () => {};

 
class Assembler {
  constructor(){
    const fileName = process.argv[2];
    this.hackCode = fs.readFileSync(`./${fileName}`).toString();
    this.index = 0; 
    this.currentInstruction = null;
  }

  advance(){
    const line = [];
    while(this.hackCode[this.index] != '\n'){
      const comment = (this.hackCode[this.index] === '/') && this.hackCode[this.index+1] === '/';
      const currentValue = this.hackCode[this.index];
      if (comment){
        this.skipLine();
        continue;
      } else {
        if (currentValue != ' ') line.push(currentValue);
      }
      this.index++;
    }
    this.currentInstruction = line.join('');
    return;
  }

  code(){
  }
  
  hasMoreLines() {
    return !(this.hackCode.length - 1 == this.index);
  }

  instructionType(){
    // determines type of instruction
  }

  parser(){
    while (this.hackCode[this.index]){
      // if there are more lines advance
      if (this.hasMoreLines()) {
        this.advance();
        console.log(this.currentInstruction);
      }
      this.index++;
    }
  }

  skipLine(){
    while(this.hackCode[this.index] != '\n'){
      this.index++;
    }
    this.index++;
    return;
  }

}

const assembler = new Assembler();
assembler.parser();
