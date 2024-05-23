const fs = require('node:fs');
const { Buffer } = require('node:buffer');

const A_SYMBOL= '@';
const L_SYMBOL = '(';
const A_INSTRUCTION = 'A_INSTRUCTION';
const L_INSTRUCTION = 'L_INSTRUCTION';
const C_INSTRUCTION = 'C_INSTRUCTION';



if (process.argv.length === 2) {
    console.error('Please add file to parse');
    process.exit(1);
}
 
class Assembler {
  constructor(){
    const fileName = process.argv[2];
    this.assemblyCode = fs.readFileSync(`./${fileName}`).toString();
    this.index = 0; 
    this.currentInstruction = null;
  }

  advance(){
    const line = [];
    while(this.assemblyCode[this.index] != '\n'){
      const comment = (this.assemblyCode[this.index] === '/') && this.assemblyCode[this.index+1] === '/';
      if (comment){
        this.skipLine();
        continue;

      } else {

        const currentValue = this.assemblyCode[this.index];
        const charCode = currentValue.charCodeAt;
        const validChar = currentValue != ' ' && charCode != 13 && charCode && currentValue != '\r'; 
        
        if (validChar) line.push(currentValue);
      }

      this.index++;
    }

    if (line.length) this.currentInstruction = line.join('');
    else this.currentInstruction = null;
  }

  code(){}

  comp(){
    const currentInstruction = this.currentInstruction.split('');

    const hasDestination = currentInstruction.includes('=');

    if (hasDestination){
      const eqlIdx = currentInstruction.indexOf('=');
      return currentInstruction.slice(eqlIdx+1).join('');
    }

    const jmpIdx = currentInstruction.indexOf(';');
    return currentInstruction.slice(0,jmpIdx).join('');
    

  }

  dest() {
    const destination = this.currentInstruction.split('');

    const hasDestination = destination.includes('=');

    if (!hasDestination) return 'the value is not stored';
    let destinationSymbol = '';
    let index = 0;

    while(destination[index] != '='){
      destinationSymbol += destination[index];
      index++;
    }

    return destinationSymbol;
  }
  
  hasMoreLines() {
    return !(this.assemblyCode.length - 1 == this.index);
  }

  instructionType(){
    // determines type of instruction.. This design won't be very sophisticated with error checking / hadnling but could be an improvement for the future

    // A instruction lead with @ followed by integer or symbol name
    const aSymbol = A_SYMBOL === this.currentInstruction[0];
    const lSymbol = L_SYMBOL === this.currentInstruction[0];

    if (aSymbol) return A_INSTRUCTION;
    if (lSymbol) return L_INSTRUCTION;
    return C_INSTRUCTION;
  } 

  jump(){
    if(this.currentInstruction[1] === ';'){
      const jumpInstruction = this.currentInstruction.split('');
      return jumpInstruction.slice('2').join('');
    }
    return 'no jump';
  }

  parser(){
    while (this.assemblyCode[this.index]){
      // if there are more lines advance
      if (this.hasMoreLines()) {
        this.advance();

        if (this.currentInstruction) {
          const typeOfInstruction = this.instructionType();

          if (typeOfInstruction === A_INSTRUCTION || typeOfInstruction === L_INSTRUCTION){
            const currentSymbol = this.symbol();
          } else {
            const destination = this.dest();
            const jump = this.jump();
            const computation = this.comp();
          }

        }
      }
      this.index++;
    }
  }

  skipLine(){
    while(this.assemblyCode[this.index] != '\n'){
      this.index++;
    }
    this.index++;
    return;
  }

  start(){
    this.parser();
  }
  symbol(){
    let extractSymbol = '';
    for (const char of this.currentInstruction){
      const validChar = char != '@' && char != '(' && char != ')';
      if (validChar) extractSymbol += char;
    }
    return extractSymbol;
  }

}

const assembler = new Assembler();
assembler.start();
