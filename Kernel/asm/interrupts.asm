
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _irq60Handler
GLOBAL _exception0Handler

GLOBAL _exception6Handler
EXTERN irqDispatcher
EXTERN exceptionDispatcher

SECTION .text

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

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro


; se guarda el stack para poder devolverlo cuando ocurre una excepcion
%macro exceptionHandler 1

	mov qword[regist], rax
	mov qword[regist+8], rbx
	mov qword[regist+16], rdx
	mov qword[regist+24], rcx
	mov qword[regist+32], rsi
	mov qword[regist+40], rdi
	mov qword[regist+48], rbp
	mov qword[regist+56], rsp
	mov qword[regist+64], r8
	mov qword[regist+72], r9
	mov qword[regist+80], r10
	mov qword[regist+88], r11
	mov qword[regist+96], r12
	mov qword[regist+104], r13
	mov qword[regist+112], r14
	mov qword[regist+120], r15

	; accedo al rip por medio del stack
	mov rax,[rsp] 
	mov [regist+128],rax


	pushState
	mov rdi, %1 ; pasaje de parametro
	mov rsi,regist
	call exceptionDispatcher

	popState

	; se pisa la direccion de retorno, muy parecido a lo hicimos que en el parcial
	push rax
    mov rax, 0x00400000 ;cargo la direccion de user land
    mov [rsp+8],rax  ;cambio la dir de reotrno de iretq a user land
    pop rax
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

;syscalls	
_irq60Handler:

	;se pasan 7 parametros ya que existe una syscall que recibe 6 parametros, debido al
	; corrimiento se tiene que pasar uno de esos parametros por stack
	push r9
	mov r9, r8
	mov r8,rcx
	mov rcx,rdx
	mov rdx,rsi
	mov rsi,rdi
	;muevo los parametros de handler para q al dispatcher le lleguen bien
	mov rdi,60h
	call irqDispatcher
	pop r9
	
	iretq


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid Op code Exception
_exception6Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret



SECTION .bss
	regist resq 17