const fs = require("node:fs");
const constants = require("./constants");

module.exports = class CompilationEngine {
  #output;
  #tokenizer
  #tokenIndex;
  #currentToken;

  constructor(input,outputFile){
    this.#output = outputFile;
    this.#tokenizer = input;
    this.#tokenIndex = 0;
    this.#currentToken = null;
    console.log(this.#tokenizer);

  }

  #advance(){
    this.#currentToken = this.#tokenizer[this.#tokenIndex++];
  }

  #printToken(tag){
    try{
      console.log(tag);
      // fs.writeFileSync(this.#output, tag, { flag: 'a' })
    } catch (err) {
      console.error(err);
      process.exit(1);
    }
  }
  
  compileClass() {
    this.#advance();

    if (this.#tokenIndex === 0 && this.#currentToken !== "class") {
      console.error("Syntax error: Code must be built inside of a class");
      process.exit(1);
    }
    this.#printToken('<class>');
    this.#process("class");
    this.#process("")
    // this.#printToken(this.#inputTokens[++this.#tokenIndex]);

    this.#printToken('</class>');


  }

  compileClassVarDec(){}
  compileParameterList(){}
  compileSubroutineBody(){}
  compileVarDec(){}
  compileStatements(){}
  compileLet(){}
  compileIf(){}
  compileWhile(){}
  compileDo(){}
  compileReturn(){}
  compileExpresion(){}
  compileTerm(){}
  compileExpressionList(){}

  #process(el) {
    if (this.#currentToken == el){
      let processedElement;

      switch(el) {
        case constants.RESERVED_KEYWORDS.includes(el):
          processedElement = `<keyword> ${el} </keyword>`;
          break;

        case constants.RESERVED_SYMBOLS.includes(el):
          processedElement = `<symbol> ${el} </symbol>`;
        
        case parseInt(el):
          processedElement = `<integerConstant> ${el} </integerConstant>`;
        
        case this.#validString(el):
          const completeString = el[el.length - 1] === '"';

          if (completeString)
            processedElement = `<stringConstant> ${el.slice(1, el.length - 1)} </stringConstant>`;
          else 
            processedElement = this.#findCompleteString();

        default:
          processedElement = `<identifier> ${el} </identifier>`

      }

      this.#printToken(processedElement);

    }
    else {
      console.error("syntax error");
      process.exit(1);
    }
    this.#advance();
  }

  #findCompleteString() {

    let buildString = this.#currentToken.slice(1);

    this.#advance();

    while (this.#currentToken[this.#currentToken.length - 1] !== '"' && this.#tokenIndex < this.#tokenizer.length) {
      buildString +=  ` ${this.#currentToken}`;
      this.#advance();
    }
    
    if (buildString[buildString.length - 1] !== '"') {
      console.error("Syntax errorL invalid string");
      process.exit(1);
    }

    return buildString.slice(0, buildString.length - 1);
    
  }
  
  #validString(el) {
    return this.#currentToken[0] === '"';
  }


}