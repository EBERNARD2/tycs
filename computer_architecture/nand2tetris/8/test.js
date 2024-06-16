const fs = require('node:fs');

try {
  if (process.argv.length === 2) {
    console.error('Expected at least one argument!');
    process.exit(1);
  }

  const dir = fs.readdirSync(process.argv[2]);
  
} catch (err) {
  console.error(err);
}
