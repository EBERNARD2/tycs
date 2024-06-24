const fs = require("node:fs");

module.exports = class CompilationEngine {
  #output;
  #inputTokens
  #tokenIndex;

  constructor(input,outputFile){
    this.#output = outputFile;
    this.#inputTokens = input;
    this.#tokenIndex = 0;

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
  
  compileClass(){

    if (this.#tokenIndex === 0 && this.#inputTokens[this.#tokenIndex] !== "CLASS") {
      console.error("Syntax error: Code must be built inside of a class");
      process.exit(1);
    }

    this.#printToken('<class>');
    this.#printToken(this.#inputTokens[++this.#tokenIndex]);


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

}