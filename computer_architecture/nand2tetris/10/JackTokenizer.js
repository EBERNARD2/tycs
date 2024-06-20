const fs = require('node:fs');


module.exports = class JackTokenizer {
  constructor(inputFile){
    const currentFile = fs.readFileSync(inputFile);

    const fileLines = currentFile.toString().split('\n');

    this.file = fileLines.map((line) => line.trim());
  }

  hasMoreTokens(){}

  advance(){}

  tokenType(){}

  keyword(){}
  
  symbol(){}

  identifier(){}

  intVal(){}

  stringVal(){}
}