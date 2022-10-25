GLOBAL gettick
GLOBAL write
GLOBAL getchar
GLOBAL halt

GLOBAL getLastKey
GLOBAL putSquare
section .text

%macro pushState 0
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
%endmacro

%macro sys_call 1
	pushState

	mov rcx,rdx 
    mov rdx,rsi
    mov rsi,rdi
	mov rdi, %1
	int 80h
	
	popState
	ret
%endmacro

;-----------------------------------------------;
;			nuestras syscalls					;			
;												;	
;-----------------------------------------------;
write:
    sys_call 1

getchar:
	sys_call 0

gettick:
	sys_call 2

halt:
	sys_call 3

putSquare:
	sys_call 4

getTime:
	sys_call 5

getLastKey:
	sys_call 6

; sys_put_pixel
;
;
;
; sys_getTime
;
;
;
;
;
;
; sys_Beep
;
;
;
;
;
;
;
;
;
