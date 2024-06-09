; ----------------------------------------------------------------------------------------
; Writes "Hello, World" to the console using only system calls. Runs on 64-bit Linux only.
; To assemble and run:
;
;     nasm -felf64 hello.asm && ld hello.o && ./a.out
; ----------------------------------------------------------------------------------------

        global  start

        section .text
start:
        mov      rax, 0x02000004
        mov      rdi, 1
        mov      rsi, message
        mov      rdx, 13
        syscall
        mov       rax, 0x02000001
        xor      rdi, rdi
        syscall

message: db      "Hello, World", 10