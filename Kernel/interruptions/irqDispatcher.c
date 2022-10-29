#include <irqDispatcher.h>
#include <syscalls.h>
#include <sound_driver.h>
#include <video_driver.h>
#include <interrupts.h>
#include <naiveConsole.h>
#include <keyboard_driver.h>


static void int_20();
static void int_21();
static uint64_t int_80(uint64_t rdi, uint64_t rsi, uint64_t  rdx ,uint64_t rcx,uint64_t r8,uint64_t r9);

#define SYS_GETCHAR_ID 0
#define SYS_WRITE_ID 1
#define SYS_TICK_ID 2
#define SYS_HALT_ID 3
#define SYS_PUTSQUARE_ID 4
#define SYS_GETTIME_ID 5
#define SYS_GETLASTKEY_ID 6
#define SYS_GETREGISTERS_ID 7
#define SYS_BEEP_ID 8
#define SYS_SLEEP_ID 9
#define SYS_CLEARKEYBUFFER_ID 10
#define SYS_CHANGELANGUAGE_ID 11


//static void int_22(uint64_t rdi, uint64_t rsi, uint64_t rdx ,uint64_t rcx, uint64_t r8, uint64_t r9);
void (*fun_inter[256])(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
uint64_t (*fun_sys[256])(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);


void initialize(){
    (fun_inter[0])=int_20;
    (fun_inter[1])=int_21;
    (fun_inter[0x60])=int_80; // pasasr 60 en el asm

    //agreago syscalls
    (fun_sys[SYS_GETCHAR_ID])=sys_getchar;
    (fun_sys[SYS_WRITE_ID])=sys_write;
    (fun_sys[SYS_TICK_ID])=sys_tick;
    (fun_sys[SYS_HALT_ID])=sys_halt;
    (fun_sys[SYS_PUTSQUARE_ID])=sys_putSquare;
    (fun_sys[SYS_GETTIME_ID])=sys_getTime;
    (fun_sys[SYS_GETLASTKEY_ID])=sys_getLastKey;
    (fun_sys[SYS_GETREGISTERS_ID])=sys_getRegisters;
	(fun_sys[SYS_BEEP_ID])=sys_beep;
    (fun_sys[SYS_SLEEP_ID])=sys_sleep;
    (fun_sys[SYS_CLEARKEYBUFFER_ID])=sys_clearkeybuffer;
    (fun_sys[SYS_CHANGELANGUAGE_ID])=sys_changeLanguage;
}


void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t  rdx ,uint64_t rcx,uint64_t r8,uint64_t r9) {
    (*fun_inter[irq])(rdi,rsi,rdx,rcx,r8,r9);
    return;
}

void int_20() {
    timer_handler();
}

void int_21(){
    storeKey();

}

uint64_t int_80(uint64_t rdi, uint64_t rsi, uint64_t  rdx ,uint64_t rcx,uint64_t r8,uint64_t r9){
    return (*fun_sys[rdi])(rsi,rdx,rcx,r8,r9);
}