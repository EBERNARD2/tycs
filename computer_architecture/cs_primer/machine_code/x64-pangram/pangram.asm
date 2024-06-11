section .text
global pangram
pangram:
	; rdi: source string
	mov rdx, 0 ; set index
	mov r8, 0


loop:
	mov rsi, [rdi + rdx]
	cmp rsi, 0
	je finish


	inc 

	inc rdx
	jmp loop

finish:
	sub rdx, 0x07fffffe
	je true
	mov rax, 0
	ret

true:
	mov rax, 1
	ret
