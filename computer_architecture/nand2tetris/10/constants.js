const KEYWORD_CONSTANT = 'KEYWORD';
const SYMBOL_CONSTANT = 'SYMBOL';
const INTERGER_CONSTANT = 'INT_CONST';
const STRING_CONSTANT = 'STRING_CONST';
const IDENTIFIER_CONSTANT = "IDENTIFIER";
const BLANK_LINE = "";


const CLASS_VAR_CONSTANTS = [
  'static',
  'field'
];

const STATEMENT_CONSTANTS = [
  'while',
  'do',
  'return',
  'let'
];

const SUBROUTINE_DEC_CONSTANTS = [
  '"constructor',
  'function',
  'method',
]
const COMMENT_SYMBOLS = [
  '//', 
  '/*'
];

const TYPE_KEYWORDS = [
  "var",
  "int",
  "char",
  "boolean",
  "void",
];

const KEYWORD_CONSTANTS = [
  'true',
  'false',
  'null',
  'this'
];


const RESERVED_KEYWORDS = [
  "class",
  "constructor",
  "function",
  "method",
  "field",
  "static",
  "var",
  "int",
  "char",
  "boolean",
  "void",
  "true",
  "false",
  "null",
  "this",
  "let",
  "do",
  "if",
  "else",
  "while",
  "return"
];

const RESERVED_SYMBOLS = [
  "{",
  "}",
  "(",
  ")",
  "[",
  "]",
  ".",
  "'",
  ";",
  "+",
  "-",
  "/",
  "&",
  "|",
  "<",
  ">",
  "=",
  "~"
];

const OP_SYMBOLS = [
  '+' ,
   '-' , 
   '*' , 
   '/' , 
   '&' , 
   ',' , 
   '<' , 
   '>' , 
   '='
];

const UNARY_OP_CONSTANTS = [
  '~',
  '-',
]


module.exports = {
  RESERVED_KEYWORDS,
  RESERVED_SYMBOLS,
  COMMENT_SYMBOLS,
  KEYWORD_CONSTANT,
  STRING_CONSTANT,
  SYMBOL_CONSTANT,
  BLANK_LINE,
  INTERGER_CONSTANT,
  IDENTIFIER_CONSTANT,
  CLASS_VAR_CONSTANTS,
  SUBROUTINE_DEC_CONSTANTS,
  STATEMENT_CONSTANTS,
  TYPE_KEYWORDS, 
  OP_SYMBOLS,
  KEYWORD_CONSTANTS,
  UNARY_OP_CONSTANTS
}