const fs = require('node:fs');


module.exports = class JackTokenizer {
  constructor(inputFile){
    console.log(inputFile, 'in tokenizer');
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