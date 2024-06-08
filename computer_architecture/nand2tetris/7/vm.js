const fs = require('node:fs');


const STACK_MAX = 2047;
const MEMORY_MAX = 24576;
const BASE_LCL = 3000;
const BASE_ARG = 3500;
const BASE_THIS = 4000;
const BASE_THAT = 10000; 
const BASE_SP = 256; 
const BASE_TEMP = 5;
const BASE_STATIC = 16;

const VALID_SEGMENTS = [
  'argument',
  'local',
  'static',
  'constant',
  'this',
  'that',
  'pointer',
  'temp'
];

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

/* 
  2- Change lq, eq, gt to jumps

*/

// Register 0 - 15 will be slots 0 - 15 in memory idx
class CodeWriter {
  constructor(outputFile){
    if (!outputFile){
      console.log('Please enter a path for the output file');
      process.exit(1);
    }
    // we probably need to manage regester and ram memory
    this.outputFile = outputFile;
    this.Unique_Label_Id = 0;
    
  }


  write(hackCommand){
    try {
      fs.appendFileSync(this.outputFile, `${hackCommand}\n`);
    } catch(err){
      console.log('Error wrirting file', err);
    }
  }


  writeArithmetic(command){
    const commandToExecute = command.toLowerCase();
    // we need to make sure there are enough values on stack to decrement first
    if (!ARITHMETIC_OPTIONS.includes(commandToExecute)) {
      console.log("Error - please enter valid arithmetic option");
      process.exit(1);
    }

    if (commandToExecute === 'add') {
      this.writeArithmeticStart();
      this.write("M=D+M");
    }

    if (commandToExecute === 'sub') {
      this.writeArithmeticStart();
      this.write("M=M-D");
    } 

    if (commandToExecute === 'neg'){
      this.write("// Load Stack pointer and negate value"); 
      this.write("@SP"); 
      this.write("AM=M-1"); 
      this.write("M=-M");
    }
    
    if (commandToExecute === 'eq') {

      const labelForTrueCase = `EQUAL${this.Unique_Label_Id++}`;
      const labelForStopCase = `DONE${this.Unique_Label_Id++}`;
    
      this.write("// Determine last two values in stack are equal");
      this.writeComparisionOperations();
      this.writeComparisonJumps(labelForTrueCase, labelForStopCase);
    }
    
    if (commandToExecute === 'gt') value = x > y;
    if (commandToExecute === 'lt') value = x < y;

    if (commandToExecute === 'and'){
      this.writeArithmeticStart();
      this.write("M=D&M");
    }

    if (commandToExecute === 'or'){
      this.writeArithmeticStart();
      this.write("M=D|M");
    }

    if (commandToExecute === 'not') {
      this.write("// Load Stack pointer and not value"); 
      this.write("@SP"); 
      this.write("AM=M-1"); 
      this.write("M=!M");
    }



  }
  
  writePushPop(command, segment, index){
  
  }


  // leave these methods
  validPointerIndex(index){
    const stringToNumber = parseInt(index);
    return stringToNumber === 0 || stringToNumber === 1;
  }

  validTempIndex(index){
    return parseInt(index) + BASE_TEMP < 13;
  }

  validStaticIndex(index){
    return parseInt(index) + BASE_STATIC < 240;
  }

  validLclIndex(index){
    return parseInt(index) < (BASE_ARG - BASE_LCL);
  }

  validArgIndex(index){
    return parseInt(index) < (BASE_THIS - BASE_ARG);
  }

  validThisIndex(index){
    return parseInt(index) < (BASE_THAT - BASE_THIS);  
  }

  validThatIndex(index){
    return parseInt(index) < (MEMORY_MAX - BASE_THAT);  
  }


  // leave this method
  getSegmentIndex(segment, index){
    const segmentToAdd = segment.toLowerCase();

    const validLocal = this.validLclIndex(index);
    const validPointer = this.validPointerIndex(index);
    const validArg = this.validArgIndex(index);
    const validThis = this.validThisIndex(index);
    const validThat = this.validThatIndex(index);
    const validStatic = this.validStaticIndex(index);
    const validTemp = this.validTempIndex(index);

 
    if(!validLocal || !validPointer || !validArg || !validThis || !validThat || !validStatic || !validTemp){
      console.log(`invalid index ${index} for ${segment}`);
      process.exit(1);
    }



    if (segmentToAdd === 'local') return parseInt(index) + BASE_LCL;
    if (segmentToAdd === 'argument') return parseInt(index) + BASE_ARG;
    if (segmentToAdd === 'this') return parseInt(index) + BASE_THIS;
    if (segmentToAdd === 'that') return parseInt(index) + BASE_THAT;
    if (segmentToAdd === 'pointer') return parseInt(index) + 3;
    if (segmentToAdd === 'temp') return parseInt(index) + 5;

    // for static 
    return parseInt(index) + 16;
  }

  pushStack(value){
    this.write(`// Push ${value} to Stack`);
  
    // write to file 
    this.write(`@${value}`);
    this.write('D=A');
    this.write('@SP'); // load address of stack pointer
    this.write('A=M'); // load current stack pointer address
    this.write('M=D'); // store value in memory
    this.write('@SP'); // Increment SP
    this.write("AM=M+1");
  }

  writeComparisionOperations(){
    this.write("@SP"); // load sp
    this.write("AM=M-1"); // get current sp address
    this.write("D=M");
    this.write("@SP");
    this.write("A=M-1"); 
    this.write("D=M-D");
  }

  writeComparisonJumps(trueLabel, endLabel){
    this.write(`@${trueLabel}`);
    this.write("D;JEQ");
    this.write("M=0");
    this.write(`@${endLabel}`);
    this.write("0;JMP");
    this.write(`(${trueLabel})`);
    this.write("M=-1");
    this.write("0;JMP");
    this.write(`(${endLabel})`);
    this.write("0;JMP");
  }

  write
  popStack(segment, index){
    const validSegment = VALID_SEGMENTS.includes(segment.toLowerCase());

    if(!validSegment){
      console.log("Invalid segment");
      process.exit(1);
    }

    this.write(`// Pop stack and save value in ${segment}`);

    //need to calculate Segment address

    const segmentAddress = this.getSegmentIndex(segment, index);

    this.write("@SP"); // load current stack value
    this.write("A=M");
    this.write("D=M");
    this.write("@SP");  
    this.write("M=M-1");
    
    this.write(`@${segmentAddress}`); // load segment address
    this.write("M=D"); // store popped value in segment

  }

  writeArithmeticStart(){
    this.write('// Load last 2 values on stack');
    this.write("@SP"); // load sp
    this.write("AM=M-1"); // get current sp address
    this.write("D=M"); // store value at sp address in data register
    this.write("@SP"); // 
    this.write("A=M-1");
  }

  close(){
  }

}


const code = new CodeWriter('test.asm');
 