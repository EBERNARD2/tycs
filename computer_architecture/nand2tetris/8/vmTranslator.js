const CodeWriter = require("./codeWriter.js");
const Parser = require("./parser.js");
const fs = require('node:fs');


function virtualMachineTranslator(outputFileName, dir){
    
    const writer = new CodeWriter(`${outputFileName}.asm`);
  
    for(const file of dir){
        const vmFile = file.split(".");
        
        if (vmFile[1] != '.vm')
            continue;

        const parser = new Parser(`${process.argv[2]}/${file}`);

        writer.currentFileName = vmFile[0];

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
    }
};


try {
    if (process.argv.length === 2) {
      console.error('Expected at least one argument!');
      process.exit(1);
    }
    const dir = fs.readdirSync(process.argv[2]);

    const splitDirPath = process.argv[2].split("/");
    const asmFileName = splitDirPath[splitDirPath.length - 1];
    virtualMachineTranslator(asmFileName, dir);
    
    
  } catch (err) {
    console.error(err);
  }

 