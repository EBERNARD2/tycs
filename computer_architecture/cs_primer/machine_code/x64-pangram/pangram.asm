section .text
global pangram
pangram:
	; rdi: source string
	xor rax, rax 
	xor rcx, rcx

loop:
	mov cl, [rdi]
	inc rdi
	cmp cl, 0
	je finish

	cmp cl, 64
	jl loop

	mov rdx, 1
	and cl, 0x1f

	shl rdx, cl
	or rax, rdx
	jmp loop

finish:
	sub rax, 0x07fffffe
	je true
	mov rax, 0
	ret

true:
	mov rax, 1
	ret
