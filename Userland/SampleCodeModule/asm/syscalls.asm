GLOBAL sys_time
GLOBAL sys_write
GLOBAL sys_read

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro
sys_write:
    push rbp 
    mov rbp,rsp

    mov rcx,rdx 
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,1
    int 80h
	
    pop rbp 
    mov rsp,rbp
    ret
