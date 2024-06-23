const JackTokenizer = require("./JackTokenizer");
const fs = require("node:fs");

module.exports = class CompilationEngine {
  #tokenizer; 
  #output;

  constructor(inputFile, outputFile){
    this.#tokenizer = new JackTokenizer(inputFile);
    this.#output = outputFile;
  }

  #print(tag){
    try{
      fs.writeFileSync(this.#output, tag, { flag: 'a' })
    } catch (err) {
      console.error(err);
      process.exit(1);
    }
  }
  
  compileClass(){
    this.#print('<class>');
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