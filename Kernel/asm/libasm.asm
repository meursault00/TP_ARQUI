GLOBAL cpuVendor
GLOBAL timeUTC
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
timeUTC:
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
getkey:
	push rbp
	mov rbp, rsp
	mov rax,0
loop: 
	in al,0x64
	mov cl,al
	and al,0x01
	cmp al,0
	je loop
	in al,0x60
	mov rsp, rbp
	pop rbp
	ret

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
	push rbp
	mov rbp, rsp

	mov rax, 6523464
	mov rbx, 73
	mov rdx, 75
	mov rcx, 80

	mov [snapshotBuffer], rax
	mov [snapshotBuffer+8], rbx
	mov [snapshotBuffer+16], rdx
	mov [snapshotBuffer+24], rcx
	mov [snapshotBuffer+32], rsi
	mov [snapshotBuffer+40], rdi
	mov [snapshotBuffer+48], rbp
	mov [snapshotBuffer+56], rsp
	mov [snapshotBuffer+64], r8
	mov [snapshotBuffer+72], r9
	mov [snapshotBuffer+80], r10
	mov [snapshotBuffer+88], r11
	mov [snapshotBuffer+96], r12
	mov [snapshotBuffer+104], r13
	mov [snapshotBuffer+112], r14
	mov [snapshotBuffer+120], r15

	mov rax, snapshotBuffer

	mov rsp, rbp
	pop rbp
	ret

section .bss
snapshotBuffer resb 128 