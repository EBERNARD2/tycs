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
  constructor(){
    
    const filePath = process.argv[2];
    const hasVmFileType = filePath.includes('.vm');

    if (!filePath || !hasVmFileType || process.argv.length < 2){
      if(process.argv.length < 2) console.error('Please add file to parse');
      if (!filePath)  console.error('Please add file to parse. Pass file path in when initializing new Parser');
      if (!hasVmFileType) console.error('Must have a .vm file extension');

      process.exit(1);
    }
    this.file = fs.readFileSync(filePath).toString();
    this.lines = this.calculateLines();
    this.currentInstruction = null;
    this.currentInsructionType = null;
    this.currentCommand = null;
    this.index;
  }

  hasMoreLines(){
    // a file has more lines if the current index is not the length of the file
    return this.lines > 0 ? true : false;
  }

  advance(){
    this.currentCommand = '';


  }

  calculateLines(){
    let lines  = 0;
    let index = 0;
    
    while(index != this.file.length){
      if(this.file[index] === '\n') lines++;
      index++
    }
    return lines;
  }

  commandType(){}

  arg1(){}

  arg2(){}
}


const parse = new Parser('')
