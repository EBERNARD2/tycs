@256
D=A
@SP
M=D
// Push 17 to Stack
@17
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 17 to Stack
@17
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if x and y are equal
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@EQUAL0
D;JEQ
M=0
@DONE1
0;JMP
(EQUAL0)
M=-1
0;JMP
(DONE1)
0;JMP
// Push 17 to Stack
@17
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 16 to Stack
@16
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if x and y are equal
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@EQUAL2
D;JEQ
M=0
@DONE3
0;JMP
(EQUAL2)
M=-1
0;JMP
(DONE3)
0;JMP
// Push 16 to Stack
@16
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 17 to Stack
@17
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if x and y are equal
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@EQUAL4
D;JEQ
M=0
@DONE5
0;JMP
(EQUAL4)
M=-1
0;JMP
(DONE5)
0;JMP
// Push 892 to Stack
@892
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 891 to Stack
@891
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if if x is less than y
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@LESS_THAN6
D;JLT
M=0
@DONE7
0;JMP
(LESS_THAN6)
M=-1
0;JMP
(DONE7)
0;JMP
// Push 891 to Stack
@891
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 892 to Stack
@892
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if if x is less than y
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@LESS_THAN8
D;JLT
M=0
@DONE9
0;JMP
(LESS_THAN8)
M=-1
0;JMP
(DONE9)
0;JMP
// Push 891 to Stack
@891
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 891 to Stack
@891
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if if x is less than y
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@LESS_THAN10
D;JLT
M=0
@DONE11
0;JMP
(LESS_THAN10)
M=-1
0;JMP
(DONE11)
0;JMP
// Push 32767 to Stack
@32767
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 32766 to Stack
@32766
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if x is greater than y
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@GREATER_THAN12
D;JGT
M=0
@DONE13
0;JMP
(GREATER_THAN12)
M=-1
0;JMP
(DONE13)
0;JMP
// Push 32766 to Stack
@32766
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 32767 to Stack
@32767
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if x is greater than y
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@GREATER_THAN14
D;JGT
M=0
@DONE15
0;JMP
(GREATER_THAN14)
M=-1
0;JMP
(DONE15)
0;JMP
// Push 32766 to Stack
@32766
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 32766 to Stack
@32766
D=A
@SP
A=M
M=D
@SP
AM=M+1
// check if x is greater than y
@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@GREATER_THAN16
D;JGT
M=0
@DONE17
0;JMP
(GREATER_THAN16)
M=-1
0;JMP
(DONE17)
0;JMP
// Push 57 to Stack
@57
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 31 to Stack
@31
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 53 to Stack
@53
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Load last 2 values on stack
@SP
AM=M-1
D=M
@SP
A=M-1
M=D+M
// Push 112 to Stack
@112
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Load last 2 values on stack
@SP
AM=M-1
D=M
@SP
A=M-1
M=M-D
// Load Stack pointer and negate value
@SP
AM=M-1
M=-M
// Load last 2 values on stack
@SP
AM=M-1
D=M
@SP
A=M-1
M=D&M
// Push 82 to Stack
@82
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Load last 2 values on stack
@SP
AM=M-1
D=M
@SP
A=M-1
M=D|M
// Load Stack pointer and not value
@SP
AM=M-1
M=!M
