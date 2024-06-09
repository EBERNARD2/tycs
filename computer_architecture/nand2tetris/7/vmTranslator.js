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

// const writer = new CodeWriter('simpleAdd.asm');

// writer.writePushPop("CPUSH", 'constant', 7);
// writer.writePushPop("CPUSH", 'constant', 8);
// writer.writeArithmetic("add");
 