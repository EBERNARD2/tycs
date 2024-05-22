const fs = require('node:fs');
const { Buffer } = require('node:buffer');


if (process.argv.length === 2) {
    console.error('Please add file to parse');
    process.exit(1);
}

const fileName = process.argv[2];

const hackCode = fs.readFileSync(`./${fileName}`).toString();

const hasMoreLine = () => {};

const advance = () => {};

const instructionType = () => {};

const symbol = () => {};

const dest = () => {};

const comp = () => {};

const jump = () => {};


