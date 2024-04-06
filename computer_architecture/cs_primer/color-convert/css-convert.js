const fs = require('node:fs');
const path = '/Users/estradabernard/Documents/tyscs/computer_architecture/cs_primer/color-convert/advanced.css';

let buffer;
// read file
try {
  buffer = fs.readFileSync(path);
} catch(err){
  console.log(err);
}

const cssSheet = Buffer.from(buffer).toString();

const tempFileStorage = [];

// because the node write file api will remove all content of the destination file, let's setup a test file to write to;

// step through file char by char 
for (let i = 0; i < cssSheet.length; i++){
  // copy non hex values into new file
  if (cssSheet[i] === '#') console.log(`${cssSheet[i]} found one`);
    /// when hex value found, grab it   
      // turn each hex byte into a number between 0 and 255
      // write to rgb format



  
}


   


// write to new file