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

	mov r9, rsi
	sub r9, 64
	jl skip

	and rsi, 31

	mov r10, 1
	sal r10, rsi

	or r8, r10
	inc rdx
	jmp loop

skip: 
	inc rdx
	jmp loop

finish:
	sub r8, 0x07fffffe
	je true
	mov rax, 0
	ret

true:
	mov rax, 1
	ret
