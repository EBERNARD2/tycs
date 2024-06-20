const fs = require('node:fs');

const COMMENT_SYMBOLS = ['//', '/*'];

const BLANK_LINE = "";


module.exports = class JackTokenizer {
  #currentLineIndex; 
  #currentValuesToParse; 

  constructor(inputFile){
    const currentFile = fs.readFileSync(inputFile);

    const fileLines = currentFile.toString().split('\n');

    this.file = fileLines.map((line) => line.trim()).filter((f) => {
      const comment = f[0] + f[1];
      return !(COMMENT_SYMBOLS.includes(comment) || f === BLANK_LINE)
    });
    this.currentToken = [];
    this.#currentLineIndex = 0;
    this.#currentValuesToParse = [];
  }

  hasMoreTokens(){
    if (this.#currentLineIndex < this.file.length || this.#currentValuesToParse.length) {
      return true;
    }

    return false;
  }

  #getNextValidLine() {
     // Skip invalid lines until we find a line to process
     let currentLine = this.file[this.#currentLineIndex];
     
     this.#currentValuesToParse = currentLine.split(" ");
     this.#currentLineIndex++;
  }

  advance() {
    // Go to next line if there aren't any more values to parse 
    if (this.#currentValuesToParse.length === 0 ) this.#getNextValidLine();
    this.currentToken = this.#currentValuesToParse.shift();
  }

  tokenType(){
    
  }

  keyword(){}
  
  symbol(){}

  identifier(){}

  intVal(){}

  stringVal(){}
}