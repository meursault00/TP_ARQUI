
GLOBAL keyboardActive
section .text


keyboardActive:
    push rbp
	mov rbp, rsp
	
    mov rax, 0
	in al, 64h
	and al, 01h
	
    leave
    ret