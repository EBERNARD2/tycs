section .text
global index
index:
	; rdi: matrix
	; esi: rows
	; edx: cols
	; ecx: rindex
	; r8d: cindex
	imul rdx, 4
	imul rcx, rdx
	imul r8, 4
	add rcx, r8
	mov rax, [rdi + rcx]
	ret

