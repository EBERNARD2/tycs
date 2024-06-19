section .text
global binary_convert
binary_convert:
	xor rcx, rcx ; set counter to 0
	xor cl, cl; set shift counter to 0
	xor rax, rax ; set return value to 0

count: 
 	inc rcx
	cmp byte [rdi + rcx], 0x00
	jne count

loop:
	mov r10, 0
	mov r11, 1
	sub byte [rsi + rcx], 48; get values from lsb to msb
	cmovg r10, r11 ; determine to use 0 or 1 as base shift value
	mov rax, r10
	
	ret
	sal r10, cl
	add rax, r10
	inc cl

	dec rcx 
	cmp rcx, 0x00
	jge loop

ret





