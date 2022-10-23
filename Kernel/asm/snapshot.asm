GLOBAL snapshot
section .text

snapshot:
	push rbp
	mov rbp, rsp

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