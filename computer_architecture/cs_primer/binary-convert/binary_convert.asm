section .text
global binary_convert
binary_convert:
	xor rcx, rcx ; set counter to 0
	xor cl, cl; set shift counter to 0
	xor rax, rax ; set return value to 0
	xor r12, r12
	xor rsi, rsi

count: 
 	inc rsi
	cmp byte [rdi + rsi], 0x00
	jne count

sub rsi, 0x01

loop:
	mov r10, 0x00
	mov r11, 0x01
	movzx r12, byte [rdi + rsi]
	sub  r12, 48; get values from lsb to msb
	cmovg r10, r11 ; determine to use 0 or 1 as base shift value
	
	sal r10, cl
	add rax, r10
	inc cl

	dec rsi 
	cmp rsi, 0x00
	jge loop

ret





