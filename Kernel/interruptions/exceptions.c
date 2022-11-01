#include <video_driver.h>
#include <interrupts.h>
#include <lib.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_EXCEPTION_ID 6
#define MESSAGE_COLOR 0xFFFFFF
#define MESSAGE_BACKROUND 0xFF0000
#define MESSAGE_SHADOW  0x0a0a0a

static void zero_division();
static void invalid_op_code();

/**
 * @brief selecciona el tipo de exception que se lanzo y vuelve a la consola
 *
 * @param exception numero de la exception
 */

void exceptionDispatcher(int exception,uint64_t * stackFrame) {
    switch (exception)
    {
    case ZERO_EXCEPTION_ID:
        zero_division(stackFrame);
        break;
    case INVALID_OP_CODE_EXCEPTION_ID:
        invalid_op_code(stackFrame);
        break;
    default:
        break;
    }

}

static void error_sign(char * message,uint64_t * stackFrame){
    //dibujo contemporaneo de la exception
    char buffer[50];
        put_rectangle(0,0,955,565,MESSAGE_SHADOW);
        put_rectangle(0,0,935,545,MESSAGE_BACKROUND);

        put_word(message,230,10,2,MESSAGE_COLOR);

	char registers[17][4] = { "RAX", "RBX", "RDX", "RCX", "RSI", "RDI", "RBP", "RSP", " R8", " R9", "R10", "R11", "R12", "R13", "R14", "R15","RIP"};
	for ( int i = 0; i < 17; i++ ){
        put_word(registers[i],0,i*16*2,2,MESSAGE_COLOR);
        uintToBase(*(stackFrame+i),buffer,16);
        put_word(buffer,32*3,i*16*2,2,MESSAGE_COLOR);
	}
        put_word("reiniciando consola en ",230,10+34*2,2,MESSAGE_COLOR);
        put_word("5 segundos  !!!",230,10+68*2,2,MESSAGE_COLOR);
        for(int i=0;i<(18*5);i++){ //espera 5 segundo o 18*5 ticks
            _hlt();
        }

}      

static void zero_division(uint64_t * stackFrame) {
    error_sign("division por cero",stackFrame);
}


static void invalid_op_code(uint64_t * stackFrame){
    error_sign("codigo de operaciones invalido",stackFrame);
}

