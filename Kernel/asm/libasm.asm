GLOBAL cpuVendor
GLOBAL getTime
GLOBAL getkey
GLOBAL inb
GLOBAL outb
GLOBAL snapshot
GLOBAL getSP
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

; retorna un puntero a una zona de memoria donde se encuentra el estado de todo los registros
snapshot:

	; es inevitable que algunos registros tengan valores fijos porque para llegar aca 
	; hay que invitablemente usar registros, entonces no es un snapshot real

	mov [regsBuffer], rax
	mov [regsBuffer+8], rbx
	mov [regsBuffer+16], rdx
	mov [regsBuffer+24], rcx
	mov [regsBuffer+32], rsi
	mov [regsBuffer+40], rdi 
	mov [regsBuffer+48], rbp
	mov [regsBuffer+56], rsp
	mov [regsBuffer+64], r8
	mov [regsBuffer+72], r9
	mov [regsBuffer+80], r10
	mov [regsBuffer+88], r11
	mov [regsBuffer+96], r12
	mov [regsBuffer+104], r13
	mov [regsBuffer+112], r14
	mov [regsBuffer+120], r15

	mov rax, regsBuffer

	ret
getSP:
	mov rax, rsp
	ret

section .bss 
regsBuffer resb 128