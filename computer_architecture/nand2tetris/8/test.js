const fs = require('node:fs');

try {
  if (process.argv.length === 2) {
    console.error('Expected at least one argument!');
    process.exit(1);
  }
  const dir = fs.readdirSync(process.argv[2]);
  debugger;
  const splitDirPath = process.argv[2].split("/");
  const asmFileName = splitDirPath[splitDirPath.length - 1];

  for (const file of dir){
    const vmFile = file.split(".");
    if (vmFile[1] === 'vm')
      console.log(vmFile[0]);
  }
  
} catch (err) {
  console.error(err);
}
