GLOBAL cpuVendor
GLOBAL getTime
GLOBAL getkey
GLOBAL inb
GLOBAL outb
GLOBAL snapshot

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

;recibe el modo y cual quiere q este de minutos horas etc
;devuelve en BCD el numero correspondiente a al hora minutos... etc
getTime:
	push rbp
	mov rbp, rsp

	push rbx

	mov eax,edi
	out 70h,al
	in al,71h

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
;

inb:
	push rbp
	mov rbp, rsp
	mov rdx,rdi	;puerto
	in al,dx	;valor del puerto
	leave
	ret

outb:
	push rbp
	mov rbp, rsp
	mov rax, rsi ;valor	
	mov rdx, rdi ;puerto
	out dx, al
	leave
	ret


snapshot:

	; en rdi tengo el puntero al comienzo de donde tengo que llenar con las cosas


	mov [rdi], rax
	mov [rdi+8], rbx
	mov [rdi+16], rdx
	mov [rdi+24], rcx
	mov [rdi+32], rsi
	mov [rdi+40], rdi
	mov [rdi+48], rbp
	mov [rdi+56], rsp
	mov [rdi+64], r8
	mov [rdi+72], r9
	mov [rdi+80], r10
	mov [rdi+88], r11
	mov [rdi+96], r12
	mov [rdi+104], r13
	mov [rdi+112], r14
	mov [rdi+120], r15

	mov rax, rdi

	ret
