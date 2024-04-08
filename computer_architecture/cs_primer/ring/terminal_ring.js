const readline = require('node:readline');

const { stdin: input, stdout: output } = require('node:process');
const process = require('node:process');


const rl = readline.createInterface({ input, output });

function createBellSound(value){
  const valueToNum = Number(value);
  if (valueToNum === NaN) return;
  
  for (let i = 0; i < valueToNum; i++){
  }  
}
process.stdin.on("keypress", createBellSound);

rl.on('SIGINT', () => {
  rl.close();
}); 



