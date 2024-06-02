const fs = require('node:fs');

/* 
  Parser Module
  - Constructor takes input file / stream 
  - hasMoreLines method (returns boolean)
  - advance method (reads next instruction).. Does not return anything 
  - commandType method (returns a constand value describing the type of method)
  - arg1 method (returns first argument in current command)
  - arg2 method (returns second argument in current command)

*/
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
    // set current command
    this.currentCommand = '';

    //parse line
    let startingIdx = this.currentIndex;

    while(this.file[this.currentIndex] != '\n'){
      this.currentIndex++;
    }

    this.currentCommand = this.file.substring(startingIdx, this.currentIndex);
    this.lines--;
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

  commandType(){}

  arg1(){}

  arg2(){}
}


const parse = new Parser('StackArithmetic/SimpleAdd/SimpleAdd.vm');
parse.advance();
console.log(parse.currentCommand);

