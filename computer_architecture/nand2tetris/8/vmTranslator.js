const CodeWriter = require("./codeWriter.js");
const Parser = require("./parser.js");

function virtualMachineTranslator(fileName){
    const parser = new Parser(fileName);
    const writer = new CodeWriter(`${fileName.split(".vm")[0]}.asm`);
  
    while (parser.lines){
        if (parser.hasMoreLines()){
            parser.advance();
            // const currentCmd = parser.currentCommand;
            const cmdType = parser.commandType();
            
            // arg1 can be called only by everything but C_ARITHMETIC and C_RETURN
            // arg2 can only be called if command if current cmd is C_PUSH, C_POP, C_FUNCTION, C_CALL
            if (cmdType === 'C_ARITHMETIC'){
                writer.writeArithmetic(parser.currentCommand.trim());
            }
            if (cmdType === 'C_PUSH' || cmdTyp === 'C_POP') {
                const arg1 = parser.arg1();
                const scrubInt = arg1.split('\r')[0];
                writer.writePushPop(cmdType, splitCommand[1], scrubInt);
            }

            if (cmdType === 'C_LABEL'){}

            if (cmdType === 'C_GOTO'){}

            if (cmdType === 'C_IF'){}

            if (cmdType === 'C_FUNCTION'){}

            if (cmdType === 'C_RETURN'){}

            if (cmdType === 'C_CALL') {}
        }
    }

};


virtualMachineTranslator('./StackArithmetic/StackTest/StackTest.vm');

 