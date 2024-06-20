const fs = require('node:fs');

const COMMENT_SYMBOLS = ['//', '/*'];

const BLANK_LINE = "";


module.exports = class JackTokenizer {
  constructor(inputFile){
    const currentFile = fs.readFileSync(inputFile);

    const fileLines = currentFile.toString().split('\n');

    this.file = fileLines.map((line) => line.trim());
    this.currentIndex = 0;
    this.currentToken = null;
  }

  hasMoreTokens(){
    if (this.currentIndex != this.file.length) {
      return true;
    }

    return false;
  }

  advance(){

    // Skip invalid lines until we find a line to process
    let currentLine = this.file[this.currentIndex];
    let comment = currentLine.slice(0,2);

    while (COMMENT_SYMBOLS.includes(comment) || currentLine === BLANK_LINE) {
      this.currentIndex++;
      currentLine = this.file[this.currentIndex];
      comment = currentLine.slice(0,2);
    }

    console.log(currentLine, 'found a line');
    this.currentIndex++;
  }

  tokenType(){}

  keyword(){}
  
  symbol(){}

  identifier(){}

  intVal(){}

  stringVal(){}
}