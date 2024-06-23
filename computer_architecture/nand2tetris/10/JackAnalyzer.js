const fs = require('node:fs');
const CompilationEngine = require('./CompilationEngine');


/** 
 *  There are a few requirements we need to consider for this function:
 * 1. We know a inputFilePath is a file if it ends with .{file extension}
 * - If it is not a jack file there is not point of analyzing syntax in file as this is a Jack compiler
 * 2. If it does not have a file extension we can assume that it is a path to a directory// 
 * - POSIX should throw an error the dir doesn't exist
*/



// ./Path/To/File.js or /Usr/name/folder/here/file.js

// Determine whether or not input string is a directory

const processJackFiles = (inputFilePath) => {

  // Break string up where instances of char "." occur in string
  const splitPath = inputFilePath.split(".");

  // Determine whether or not the input is a file path or directory 
  // need to account for both relative and absolute paths
  const isDir = `.${splitPath[1]}` === inputFilePath || splitPath[0] === inputFilePath;
  if (isDir){
    // If not a file path try to fetch directory
    try {
      const dir = fs.readdirSync(inputFilePath).filter((file) => {
        const fileExtension = file.split(".")[1];
        return fileExtension === 'jack';
      });

      // if successful log out all files in directory
      for(const file of dir){
        jackAnalyzer(file);
        // jackAnalyzer(tokenizer);
      }

    } catch(err) {
      // if not a valid directory on machine throw an error 

      console.error(`Error: Not a valid directory path`);
      console.error(err);
      process.exit(1);
    }
  } else {

    // if it is a file then make sure it is a jack file
    const validFile = splitPath[splitPath.length - 1] === "jack";

    // if it is not a jack file throw an error and exit program

    if (!validFile) {
      console.error('Must enter a valid jack file extension');
      process.exit(1);
    }

    // const tokenizer = new JackTokenizer(inputFilePath);


    // jackAnalyzer(tokenizer);

    jackAnalyzer(inputFilePath);
    

  }
 
};

const jackAnalyzer = (inputFile) => {
  const outputFile = inputFile.split(".jack")[0] + '.xml';
  
  const compilationEngine = new CompilationEngine(inputFile, outputFile);
  compilationEngine.compileClass();
  // while (tokenizer.hasMoreTokens()) {
  //   tokenizer.advance()
    
  // }

};

processJackFiles(process.argv[2]);







