const fs = require('node:fs');

const COMMENT_SYMBOLS = ['//', '/*'];

const BLANK_LINE = "";
const KEYWORD_CONSTANT = 'KEYWORD';
const SYMBOL_CONSTANT = 'SYMBOL';
const INTERGER_CONSTANT = 'INT_CONST';

const RESERVED_KEYWORDS = [
  "class",
  "constructor",
  "function",
  "method",
  "field",
  "static",
  "var",
  "int",
  "char",
  "boolean",
  "void",
  "true",
  "false",
  "null",
  "this",
  "let",
  "do",
  "if",
  "else",
  "while",
  "return"
];

const RESERVED_SYMBOLS = [
  "{",
  "}",
  "(",
  ")",
  "[",
  "]",
  ".",
  "'",
  ";",
  "+",
  "-",
  "/",
  "&",
  "|",
  "<",
  ">",
  "=",
  "~"
];


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
     
     const lineValues = currentLine.split(" ");

     const scrubValues = lineValues.reduce((accumulator, value) => {


      let valuesToPush = [];
      
      if (value[value.length - 1] === ';') {
        valuesToPush.push(value.slice(0, value.length - 1));
        valuesToPush.push(";");
      } 

      const hasUpdatedValue = valuesToPush[0] ? true : false;
      
      if (value[0] === '(' && value.length > 1 && value[value.length - 1] === ")"){
        const valueToPush = value.split(/[()]/)[1];
        valuesToPush[0] = valueToPush;
      }
      
      if (hasUpdatedValue && valuesToPush[0][0] === "(" && valuesToPush[0][valuesToPush[0].length - 1] === ")") {
        valuesToPush[0] = valuesToPush[0].split(/[()]/)[1];
      }

      valuesToPush.length ? accumulator.push(...valuesToPush) : accumulator.push(value);

      return accumulator;
     }, []);

     this.#currentValuesToParse = scrubValues;

     this.#currentLineIndex++;
  }

  advance() {
    // Go to next line if there aren't any more values to parse 
    if (this.#currentValuesToParse.length === 0 ) this.#getNextValidLine();

    while(this.#currentValuesToParse[0] === '' || this.#currentValuesToParse[0] === '//'){
      if (this.#currentValuesToParse[0] === '//') {
        this.#currentLineIndex++;
        this.#getNextValidLine();
      } else {
        this.#currentValuesToParse.shift();
      }
    }

    if (this.#currentValuesToParse[0] === '//') {
      this.#currentLineIndex++;
      this.#getNextValidLine();
    }
      

    this.currentToken = this.#currentValuesToParse.shift();
  }

  tokenType(){
    // There are 5 categories:
    // Keywords, symbols, intergerConstants, stringConstants, and identifiers

    if (RESERVED_KEYWORDS.includes(this.currentToken))
      return KEYWORD_CONSTANT;

    if (RESERVED_SYMBOLS.includes(this.currentToken)) 
      return SYMBOL_CONSTANT;
    

    if (parseInt(this.currentToken)) 
      return INTERGER_CONSTANT;

  }

  keyword(){}
  
  symbol(){}

  identifier(){}

  intVal(){}

  stringVal(){}
}