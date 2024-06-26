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
    this.#process(this.#currentToken);
    this.#process("{");

    if (constants.CLASS_VAR_CONSTANTS.includes(this.#currentToken))
      this.compileClassVarDec();

    if (constants.SUBROUTINE_DEC_CONSTANTS.includes(this.#currentToken))
      this.compileSubroutine();

    this.#process("}");
    this.#printToken('</class>');

  }

  compileClassVarDec(){
    this.#printToken("<classVarDec>")
    this.#process(this.#currentToken); // static or field var
    this.#process(this.#currentToken); // type
    this.#process(this.#currentToken); // varName *** Need to find a solution for multiple var declarations with ',' 
    this.#process(';');
    this.#printToken("</classVarDec>")
  }

  compileSubroutine(){
    this.#printToken("<subroutineDec>")
    this.#process(this.#currentToken);
    this.#process(this.#currentToken);
    this.#process(this.#currentToken);
    this.#process("(");
    this.compileParameterList();
    this.#process(")");
    this.#process("{");
    this.compileSubroutineBody();
    this.#process("}");
    this.#printToken("</subroutineDec>")

  }

  compileParameterList(){
    this.#printToken("<parameterList>");

    while (constants.TYPE_KEYWORDS.includes(this.#currentToken)) {
      this.#process(this.#currentToken);
      this.#process(this.#currentToken);
      
      if (this.#currentToken === ',')
        this.#process(",");
    }
    this.#printToken("</parameterList>");

  }

  compileSubroutineBody(){
    this.#printToken("<subroutineBody>")
    this.#process("{");
    this.compileVarDec();
    this.compileStatements();
    this.#process("}");
    this.#printToken("</subroutineBody>")

  }

  compileVarDec(){
    this.#printToken("<varDec>");
    // right now this processes a single variable, we need to find a way to process multiple
    this.#process("var");
    this.#process(this.#currentToken);
    this.#process(this.#currentToken);
    this.#process(";");
    this.#printToken("</varDec>");
  }


  compileStatements(){
    this.#printToken("<statements>");

    while (constants.STATEMENT_CONSTANTS.includes(this.#currentToken)) {
      if (this.#currentToken === 'let')
        this.compileLet();
      else if (this.#currentToken === 'while')
        this.compileWhile();
      else if (this.#currentToken === 'do')
        this.compileDo();
      else if (this.#currentToken === 'return');
        this.compileReturn();
    }
    this.#printToken("</statements>");

  }

  compileLet(){
    this.#printToken("<letStatement>");
    this.#process(this.#currentToken);
    this.#process("=");
    this.compileExpresion(); // still need to figure out multiple values here as well
    this.#process(";");
    this.#printToken("</letStatement>");

  }
  compileIf(){
    this.#printToken("<letStatement>");
    this.#process("if");
    this.#process("(");
    this.compileExpresion();
    this.#process(")");
    this.#process("{");
    this.compileStatements();
    this.#process("}");
    // add else statement if appropriate 
    if (this.#currentToken === 'else') {
      this.#process("else");
      this.#process("{");
      this.compileStatements();
      this.#process("}");
    }
    this.#printToken("</letStatement>");
  }

  compileWhile(){
    this.#printToken("<whileStatement>");
    this.#process("while");
    this.#process("(");
    this.compileExpresion();
    this.#process(")");
    this.#process("{");
    this.compileStatements();
    this.#process("}");
    this.#printToken("</whileStatement>");


  }


  compileDo(){
    this.#printToken("<doStatement>");
    this.#process("do");
    this.compileSubroutine();
    this.#process(";");
    this.#printToken("/<doStatement>");

  }
   
  compileReturn(){
    this.#printToken("<returnStatement>");
    this.#process("return");

    if (this.#currentToken !== ';')
      this.compileExpresion();

    this.#process(";");
    this.#printToken("</returnStatement");
  }


  compileExpresion(){
    this.#printToken("<expression>");
    this.compileTerm();
    if (constants.OP_SYMBOLS.includes(this.#currentToken))
      this.compileTerm();

    this.#printToken("</expression>");

  }

  compileTerm(){
    this.#printToken("<term>");
    // this will be a name, a value, an expression or an array
    if (this.#tokenizer[this.#tokenIndex + 1] === '(') {
      this.#process("(");
      this.compileExpresion();
      this.#process(")");
    } else if (this.#tokenizer[this.#tokenIndex + 1] === '[') {
      this.#process("[");
      this.compileExpresion();
      this.#process("]");
    } else if (constants.UNARY_OP_CONSTANTS.includes(this.#currentToken))
      this.#process(this.#currentToken);
    else 
      this.#process(this.#currentToken);

    this.#printToken("</term>");

  }

  compileExpressionList(){}

  #process(el) {
    if (this.#currentToken == el){
      let processedElement;

      if (constants.RESERVED_KEYWORDS.includes(el))
        processedElement = `<keyword> ${el} </keyword>`;
      else if (constants.RESERVED_SYMBOLS.includes(el))
        processedElement = `<symbol> ${el} </symbol>`;
      else if (parseInt(el))
        processedElement = `<integerConstant> ${el} </integerConstant>`;
      else if (this.#validString()) {
        const completeString = el[el.length - 1] === '"';

          if (completeString)
            processedElement = `<stringConstant> ${el.slice(1, el.length - 1)} </stringConstant>`;
          else 
            processedElement = this.#findCompleteString();
      } else 
        processedElement = `<identifier> ${el} </identifier>`

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
  
  #validString() {
    return this.#currentToken[0] === '"';
  }


}