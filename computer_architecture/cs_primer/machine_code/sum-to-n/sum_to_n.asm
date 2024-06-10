section .text
global sum_to_n
sum_to_n:
	xor eax, eax
	cmp rdi, 0 
	jg  loop
	jmp done

loop: 
	add eax, edi
	dec edi
	cmp edi, 0
	jg loop
ls

done:
	ret