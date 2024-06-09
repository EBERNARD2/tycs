const CodeWriter = require("./codeWriter.js");


function virtualMachineTranslator(fileName){

};


// virtualMachineTranslator('./StackArihmetic/.vm');

const writer = new CodeWriter('simpleAdd.asm');

writer.writePushPop("CPUSH", 'constant', 7);
writer.writePushPop("CPUSH", 'constant', 8);
writer.writeArithmetic("add");
 