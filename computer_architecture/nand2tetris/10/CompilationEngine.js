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
    this.#currentToken = this.#tokenizer[this.#tokenIndex];
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

    console.log(this.#currentToken);
    this.#printToken('<class>');
    this.#process("class");
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

      switch(tag) {
        case constants.RESERVED_KEYWORDS.includes(tag):
          processedElement = `<keyword> ${el} </keyword>`;
          break;

        case constants.RESERVED_SYMBOLS.includes(tag):
          processedElement = `<symbol> ${el} </symbol>`;
        
        case parseInt(tag):
          processedElement = `<integerConstant> ${el} </integerConstant>`;
        
        case this.#validString(el):

      }

      this.#printToken(processedElement);

    }
    else {
      console.error("syntax error");
      process.exit(1);
    }
    this.#advance();
  }

  #validString(el) {

  }


}