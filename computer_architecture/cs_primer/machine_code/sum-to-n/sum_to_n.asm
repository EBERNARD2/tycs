section .text
global sum_to_n
sum_to_n:
	xor rax, rax
	mov rsi, rdi
	cmp rsi, 0 
	jg  loop
	jmp done

loop: 
	add rax, rsi
	sub rsi, 1
	cmp rsi, 0
	jg loop

done:
	ret