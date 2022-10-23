;GLOBAL getkey
GLOBAL getkeyScancode
GLOBAL keyboardActive
section .text


;getkey:
;	push rbp
;	mov rbp, rsp
;	mov rax,0
;loop: 
;	in al,0x64
;	mov cl,al
;	and al,0x01
;	cmp al,0
;	je loop
;	in al,0x60
;	mov rsp, rbp
;	pop rbp
;	ret

getkeyScancode:
    push rbp
	mov rbp, rsp

	mov rax, 0
	in al, 0x60

	leave
    ret

keyboardActive:
    push rbp
	mov rbp, rsp
	
    mov rax, 0
	in al, 64h
	and al, 01h
	
    leave
    ret