const fs = require('node:fs');


const MEMORY_MAX = 24576;
const BASE_LCL = 3000;
const BASE_ARG = 3500;
const BASE_THIS = 4000;
const BASE_THAT = 10000; 
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
module.exports = class CodeWriter {
  constructor(outputFile){
    if (!outputFile){
      console.log('Please enter a path for the output file');
      process.exit(1);
    }
    // we probably need to manage regester and ram memory
    this.outputFile = outputFile;
    this.Unique_Label_Id = 0;
    this.currentFileName = null;
    this.stackInit();
    
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
    // we need to make sure there are enough values on stack to decrement 
    console.log(commandToExecute);
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
    
      this.write("// check if x and y are equal");
      this.writeComparisionStart();
      this.writeComparisonJumps(labelForTrueCase, labelForStopCase, 'D;JEQ');
    }

    if (commandToExecute === 'gt') {
      const labelForTrueCase = `GREATER_THAN${this.Unique_Label_Id++}`;
      const labelForStopCase = `DONE${this.Unique_Label_Id++}`;
    
      this.write("// check if x is greater than y");
      this.writeComparisionStart();
      this.writeComparisonJumps(labelForTrueCase, labelForStopCase, 'D;JGT');
    }
    if (commandToExecute === 'lt'){
      const labelForTrueCase = `LESS_THAN${this.Unique_Label_Id++}`;
      const labelForStopCase = `DONE${this.Unique_Label_Id++}`;
    
      this.write("// check if if x is less than y");
      this.writeComparisionStart();
      this.writeComparisonJumps(labelForTrueCase, labelForStopCase, 'D;JLT');
    }

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

  pushStack(value, segment){
    this.write(`// Push ${value} to Stack`);
    if (segment){
      const validSegment = VALID_SEGMENTS.includes(segment.toLowerCase());

      if (!validSegment){
        console.error('Invalid location');
        process.exit();
      }

      const segmentAddress = this.getSegmentIndex(segment, value);

      this.write(`@${segmentAddress}`);
      this.write('D=M');
      this.write('@SP'); 
      this.write('A=M'); 
      this.write('M=D'); 
      this.write('@SP'); 
      this.write("AM=M+1");


      return;
    }
    // write to file 
    this.write(`@${value}`);
    this.write('D=A');
    this.write('@SP'); // load address of stack pointer
    this.write('A=M'); // load current stack pointer address
    this.write('M=D'); // store value in memory
    this.write('@SP'); // Increment SP
    this.write("AM=M+1");
  }

  writeComparisionStart(){
    this.write("@SP"); // load sp
    this.write("AM=M-1"); // get current sp address
    this.write("D=M");
    this.write("@SP");
    this.write("A=M-1"); 
    this.write("D=M-D");
  }

  writeComparisonJumps(trueLabel, endLabel, conditionalCheck){
    // need to work on the operation part
    this.write(`@${trueLabel}`);
    this.write(conditionalCheck);
    this.write("M=0");
    this.write(`@${endLabel}`);
    this.write("0;JMP");
    this.write(`(${trueLabel})`);
    this.write("M=-1");
    this.write("0;JMP");
    this.write(`(${endLabel})`);
    this.write("0;JMP");
  }
 
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

  writePushPop(command, segment, index){
    if (command === 'C_PUSH') this.pushStack(index);
    else this.popStack(segment, index);
  }

  writeLabel(label){
    this.write(`(${label})`);
  }

  writeGoto(label){
    this.write(`@${label}`);
    this.write("0;JMP");
  }

  writeIf(label){
    this.write("@SP");
    this.write("A=M-1");
    this.write("D=M");
    this.write(`@${label}`);
    this.write("");
  }

  writeFunction(functionName, nVars){
    const nArgs = parseInt(nVars);

    this.write(`(${functionName})`);

    for(let i = 0; i < nArgs; i++){
      this.pushStack(0);
    }
  }

  writeCall(functionName, nVars){
    //this method will create a new stack frame in hack machine language

    this.write(`// create stack frame before calling ${functionName} `);

    // push address of instruction we want to return to
    const uniqueLabel = `${functionName}$ret.${this.Unique_Label_Id++}`;
    this.write("// push address of instruction we want to return to");
    this.pushStack(uniqueLabel);

    // push lcl, arg, this, that to stack
    this.write('// push lcl, arg, this, that to stack');
    this.pushStack("LCL");
    this.pushStack("ARG");
    this.pushStack("THIS");
    this.pushStack("THAT");

    // set ARG to SP - 5 - nArgs
    this.write('// Set arg and stack poiner');

    this.write("@5 // set arg to SP - 5 - nArgs");
    this.write("D=A");
    this.write("@SP");
    this.write("D=D-M");
    this.write(`@${nVars}`);
    this.write("D=D-A");
    this.write('@ARG');
    this.write("M=D");

    // set lcl to sp
    this.write('// Set LCL to SP');
    this.write("@SP");
    this.write("D=M");
    this.write("@LCL");
    this.write("M=D");

    // jump to function -- probably need to change this 
    this.write('// Jump to new function');

    this.write(`@${functionName}`);
    this.write('0;JMP');

    // write return address
    this.write('// Write return address');
    this.write(`(${uniqueLabel})`);

  }

  writeReturn(){
    // we need to set frame to LCL
    this.write('// Write return address');

    this.write("@LCL");
    this.write("D=M");
    this.write("@FRAME");
    this.write("M=D");
  

    // set return address to address of frame - 5 
    this.write("@5");
    this.write("A=D-A");
    this.write("D=M");
    this.write("@RETURN");
    this.write("M=D");



    // pop last value into argument
    this.popStack('argument', 0);


    // reposition stack pointer
    this.write("@ARG");
    this.write("D=M");
    this.write("@SP");
    this.write("M=D+1");


    // set that to address of frame - 1
    this.write("@FRAME");
    this.write("D=A");
    this.write("@1");
    this.write("A=D-A");
    this.write("D=M");
    this.write("@THAT");
    this.write("M=D");

    // set this to address of frame - 2

    this.write("@FRAME");
    this.write("D=A");
    this.write("@2");
    this.write("A=D-A");
    this.write("D=M");
    this.write("@THIS");
    this.write("M=D");
    // set arg to address of frame - 3
    this.write("@FRAME");
    this.write("D=A");
    this.write("@3");
    this.write("A=D-A");
    this.write("D=M");
    this.write("@ARG");
    this.write("M=D");
    
    // set LCL to address of frame - 4
    this.write("@FRAME");
    this.write("D=A");
    this.write("@4");
    this.write("A=D-A");
    this.write("D=M");
    this.write("@LCL");
    this.write("M=D");

    //jump to return address - this is a tentative solution.. Load address at frame - 5 (where return address should be)
    // then jump to that address
    this.write("@FRAME");
    this.write("D=A");
    this.write("@5");
    this.write("A=D-A");
    this.write("0;JMP");
  }

  setFileName(fileName){
    this.currentFileName = fileName;
    this.Unique_Label_Id = 0;
  }

  stackInit(){
    this.write("@256");
    this.write("D=A");
    this.write("@SP");
    this.write("M=D");
    this.write("@Sys.init");
    this.write("0;JMP");
  }

}

