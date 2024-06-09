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