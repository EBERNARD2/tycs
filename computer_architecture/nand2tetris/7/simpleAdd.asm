@256
D=A
@SP
M=D
// Push 7 to Stack
@7
D=A
@SP
A=M
M=D
@SP
AM=M+1
// Push 8 to Stack
@8
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
@256
D=A
@SP
M=D
@256
D=A
@SP
M=D
@256
D=A
@SP
M=D
@256
D=A
@SP
M=D
@256
D=A
@SP
M=D
