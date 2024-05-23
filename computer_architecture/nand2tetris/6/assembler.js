const fs = require('node:fs');
const { Buffer } = require('node:buffer');

const SYMBOL_INSTRUCTIONS = ['@', '('];

if (process.argv.length === 2) {
    console.error('Please add file to parse');
    process.exit(1);
}
 
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
  }

  code(){}

  comp(){}

  dest() {}
  
  hasMoreLines() {
    return !(this.hackCode.length - 1 == this.index);
  }

  instructionType(){
    // determines type of instruction.. This design won't be very sophisticated with error checking / hadnling but could be an improvement for the future

    // A instruction lead with @ followed by integer or symbol name
    const symbolInstruction = SYMBOL_INSTRUCTIONS.includes(this.currentInstruction[0]);

    if (symbolInstruction){
      const symbol = this.symbol();
    }
  } 

  jump(){}

  parser(){
    while (this.hackCode[this.index]){
      // if there are more lines advance
      if (this.hasMoreLines()) {
        this.advance();
        this.instructionType();
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

  symbol(){
    
  }

}

const assembler = new Assembler();
assembler.parser();
