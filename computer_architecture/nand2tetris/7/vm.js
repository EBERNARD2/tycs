const fs = require('node:fs');


const STACK_MAX = 2047;
const MEMORY_MAX = 24576;
/* 
  Parser Module
  - Constructor takes input file / stream 
  - hasMoreLines method (returns boolean)
  - advance method (reads next instruction).. Does not return anything 
  - commandType method (returns a constand value describing the type of method)
  - arg1 method (returns first argument in current command)
  - arg2 method (returns second argument in current command

*/

const ARITHMETIC_OPTIONS = [
  'add',
  'sub',
  'neg',
  'eq',
  'gt',
  'lt',
  'and',
  'or',
  'not'
];

class Parser {
  constructor(filePath){
    
    const hasVmFileType = filePath.includes('.vm');

    if (!filePath || !hasVmFileType){
      if (!filePath)  console.error('Please add file to parse. Pass file path in when initializing new Parser');
      if (!hasVmFileType) console.error('Must have a .vm file extension');

      process.exit(1);
    }

    this.file = fs.readFileSync(filePath).toString();
    this.lines = this.calculateLines();

    this.currentCommand = null;
    this.currentInsructionType = null;
    this.currentIndex = 0;
  }

  hasMoreLines(){
    return this.lines > 0 ? true : false;
  }

  advance(){ 
    //parse line
    let line = [];

    let startIndex = this.currentIndex;

    while(this.file[this.currentIndex] != '\n' && this.currentIndex < this.file.length){
      const skipLine = !this.validLine(startIndex);

      if (skipLine){
        this.skipLine();
        this.lines--;
        startIndex = this.currentIndex;
        continue
      } 
  
      line.push(this.file[this.currentIndex]);
      this.currentIndex++;
    };  
    

    this.lines--;
    this.currentCommand = line.join('');
    this.currentIndex++;
  }


  skipLine(){
    while(this.file[this.currentIndex] != '\n'){
      this.currentIndex++;
    }
    this.currentIndex++;
  }

  calculateLines(){
    let lines  = 0;
    let index = 0;
    
    while(index != this.file.length){
      if(this.file[index] === '\n') lines++;
      index++
    }
    return ++lines;
  }

  commandType(){
    const command = this.currentCommand.split(' ')[0].toLowerCase();

    if (command === 'push') return 'C_PUSH';
    if (command === 'pop') return 'C_POP';
    if (command === 'push') return 'C_PUSH';
    if(ARITHMETIC_OPTIONS.includes(command)) return 'C_ARITHMETIC';
  }

  arg1(){
    const commandType = this.commandType();
    const command = this.currentCommand.split(' ');

    if(commandType === 'C_ARITHMETIC'){
      return command[0];
    }
    return command[1];
  }

  arg2(){
    const command = this.currentCommand.split(' ');
    return parseInt(command[2]);
  }

  validLine(startIndex){
    const comment = this.file[startIndex] === '/' && this.file[startIndex + 1] === '/'; 
    const blankLine = this.file[startIndex] === '\r';
    return !(blankLine || comment);
  }
}


const parser = new Parser('StackArithmetic/SimpleAdd/SimpleAdd.vm');
 

/* 
  Code Module
  - Constructor takes output file stream 
  - writeArithmetic takes a command string and writes to output file
  - writePushPop takes command
  - close output file
*/

// Register 0 - 15 will be slots 0 - 15 in memory idx
class CodeWriter {
  constructor(outputFile){
    if (!outputFile){
      console.log('Please enter a path for the output file');
      process.exit(1);
    }
    // we probably need to manage regester and ram memory
    this.file = outputFile;
    this.stackPointer = 256;
    this.tempIdx = 5;
    this.memory = []; /// There aren't static array sizes in js so we will just have to work with this dynamic version d
  }


  write(hackCommand){
    try {
      fs.appendFileSync(outputFile, `${hackCommand}\n`);
      console.log('Successfully added hack command to file')
    } catch(err){
      console.log('Error wrirting file', err);
    }
  }


  writeArithmetic(command){}
  writePushPop(command, segment, index){}
  close(){

  }

}


 