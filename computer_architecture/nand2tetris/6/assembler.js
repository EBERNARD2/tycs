const fs = require('node:fs');

const A_SYMBOL= '@';
const L_SYMBOL = '(';
const A_INSTRUCTION = 'A_INSTRUCTION';
const L_INSTRUCTION = 'L_INSTRUCTION';
const C_INSTRUCTION = 'C_INSTRUCTION';
const BASE_SYMBOL_TABLE = {
  'M': '001',
  'D': '010',
  'DM': '011',
  'A': '100',
  'AM': '101',
  'AD': '110',
  'ADM': '111',
  'JGT': '001',
  'JEQ': '010',
  'JGE': '011',
  'JLT': '100',
  'JNE': '101',
  'JLE': '110',
  'JMP': '111',
  'R0': '000000000000000',
  'R1': '000000000000001',
  'R2': '000000000000010',
  'R3': '000000000000011',
  'R4': '000000000000100',
  'R5': '000000000000101',
  'R6': '000000000000110',
  'R7': '000000000000111',
  'R8': '000000000001000',
  'R9': '000000000001001',
  'R10': '000000000001010',
  'R11': '000000000001011',
  'R12': '000000000001100',
  'R13': '000000000001101',
  'R14': '000000000001110',
  'R15': '000000000001111',
  'SP': '000000000000000',
  'LCL': '000000000000001',
  'ARG': '000000000000010', 
  'THIS': '000000000000011', 
  'THAT': '000000000000100',
  'KBD': '110000000000000',
  'SCREEN': '011111111111111',
  null: '000',
};

const computeLabels = {
  '0': '101010',
  '1': '111111',
  '-1': '111010',
  'D': '001100',
  'A': '110000',
  'M': '110000',
  '!D': '001101',
  '!A': '110001',
  '!M': '110001',
  '-D': '001111',
  '-A': '110011',
  '-M': '110011',
  'D+1': '011111',
  'A+1': '110111',
  'M+1': '110111',
  'D-1': '001110',
  'A-1': '110010',
  'D+A': '000010',
  'D+M': '000010',
  'D-A': '010011',
  'D-M': '010011',
  'A-D': '000111',
  'M-D': '000111',
  'D&A': '000000',
  'D&M': '000000',
  'D|A': '010101',
  'D|M': '010101',
  null: '000',
}

if (process.argv.length === 2) {
    console.error('Please add file to parse');
    process.exit(1);
}

class Assembler {
  constructor(){
    this.filePath = process.argv[2];
    this.assemblyCode = fs.readFileSync(`./${this.filePath}`).toString();
    this.index = 0; 
    this.currentInstruction = null;
    this.typeOfInstruction = null;
    this.symbolTable = {  ...BASE_SYMBOL_TABLE };
    this.currentSymbol = null;
    this.currentJmp = null;
    this.currentDest = null;
    this.currentCmp = null;
    this.nextAvailableAddress = 16;
    this.fileData = [];
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

  buildBinaryString(num){
    let bin = num.toString(2);

    while(bin.length < 15){
      bin = '0' + bin;
    }

    return bin;
  }  

  getAddress(){
    return this.symbolTable[this.currentSymbol];
  }

  code(){
    const dest = () => {
      if (this.currentDest) return this.symbolTable[this.currentDest];
      return '000';
    };

    const comp = () => {
      return computeLabels[this.currentCmp];
    };

    const jump = () => {
      if (this.currentJmp) return this.symbolTable[this.currentJmp];
      return '000';
    };

    const getControlBitA = () => {
      return this.currentCmp.includes('M') ? '1' : '0';
    }

    const contains = () => {
      return this.symbolTable[this.currentSymbol];
    }

    // for addresses we'll need a complete table representing the entire address space from 0 to 24576. Also will need registers. Each number should be a 15 bit representation
    
    if (this.typeOfInstruction === A_INSTRUCTION || this.typeOfInstruction === L_INSTRUCTION) {
      const containSymbol = contains();

      if (!containSymbol) {
        const binaryValue = this.buildBinaryString(this.nextAvailableAddress);
        this.nextAvailableAddress++;
        this.symbolTable[this.currentSymbol] = binaryValue;
      }

      const address = this.getAddress();
      return `0${address}`;

    };

    const controlBitString = getControlBitA();
    const computeBinaryString = comp();
    const jumpInstructionBinaryString = jump();
    const destinationBinaryString = dest();

    const cInstructionBinary = `111` + controlBitString + computeBinaryString + destinationBinaryString + jumpInstructionBinaryString;
    return cInstructionBinary;


  }

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

    if (!hasDestination) return null;
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
    return null;
  }

  parser(){
    while (this.assemblyCode[this.index]){
      // if there are more lines advance
      if (this.hasMoreLines()) {
        this.advance();
        if (this.currentInstruction) {
          this.typeOfInstruction = this.instructionType();

          if (this.typeOfInstruction === A_INSTRUCTION || this.typeOfInstruction === L_INSTRUCTION){
            this.currentSymbol = this.symbol();
          } else {
            this.currentDest = this.dest();
            this.currentJmp = this.jump();
            this.currentCmp= this.comp();
          }
          const binaryEncodedLine = this.code();
          

          // wirte binary encoding string to file
          this.fileData.push(binaryEncodedLine);
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
    this.writeFileData();
  }
  symbol(){
    let extractSymbol = '';
    for (const char of this.currentInstruction){
      const validChar = char != '@' && char != '(' && char != ')';
      if (validChar) extractSymbol += char;
    }
    return extractSymbol;
  }

  writeFileData(){
    const fileName = this.filePath.substring(0, this.filePath.indexOf('.'));
    const file = fs.createWriteStream(`${fileName}.hack`);
    debugger;
    file.on('error', function(err) { console.log(err) });
    this.fileData.forEach(function(v) { file.write(v + '\n'); });
    file.end();

  }

}

const assembler = new Assembler();
assembler.start();



class Parser {
  constructor(){}
}

class Code {
  constructor (){}
}

class SymbolTable {
  constructor(){}
}