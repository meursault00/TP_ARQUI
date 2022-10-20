GLOBAL cpuVendor
GLOBAL timeUTC
GLOBAL getkey
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

