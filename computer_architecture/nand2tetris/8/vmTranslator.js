const CodeWriter = require("./codeWriter.js");
const Parser = require("./parser.js");

function virtualMachineTranslator(fileName){
    const parser = new Parser(fileName);
    const writer = new CodeWriter(`${fileName.split(".vm")[0]}.asm`);
  
    while (parser.lines){
        if (parser.hasMoreLines()){
            parser.advance();
            const currentCmd = parser.currentCommand;
            const cmdType = parser.commandType();
            
            // refactor this to use arg1 and arg2 parser functions
            // arg1 can be called only by everything but C_ARITHMETIC and C_RETURN
            // arg2 can only be called if command if current cmd is C_PUSH, C_POP, C_FUNCTION, C_CALL
            if (cmdType === 'C_ARITHMETIC'){
                console.log(currentCmd.trim());
                writer.writeArithmetic(currentCmd.trim());
            } else {
                const splitCommand = currentCmd.split(" ");
                const scrubInt = splitCommand[2].split('\r')[0];
                writer.writePushPop(cmdType, splitCommand[1], scrubInt);
            }
        }
    }

};


virtualMachineTranslator('./StackArithmetic/StackTest/StackTest.vm');

 