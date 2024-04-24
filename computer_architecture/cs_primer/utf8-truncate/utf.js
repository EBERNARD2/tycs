const fs = require('node:fs');

const cases = fs.readFileSync('./cases');


const length = cases.length;


const processLine = (line) => {
  const bytesToTruncate = line[0];
  console.log(bytesToTruncate);
  return
}
function getLine(idx) {
  const start = idx;
  // 10 is the newline character
  while(cases[idx] != 10){
    idx++;
  }

  return {
    line,
    idx,
  }
}

let count = 1; 

for(let i = 0; i < length; i++){
  const lineData = getLine(i);
  i = lineData.idx;
  processLine(lineData.line);
  count++
}

console.log(cases.length);