#include <video_driver.h>
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

void exceptionDispatcher(int exception) {
    switch (exception)
    {
    case ZERO_EXCEPTION_ID:
        zero_division();
        break;
    case INVALID_OP_CODE_EXCEPTION_ID:
        invalid_op_code();
        break;
    default:
        break;
    }

}
static void error_sign(char * message){
    //dibujo contemporaneo de la exception
        put_rectangle(100,100,800,300,MESSAGE_SHADOW);
        put_rectangle(90,90,800,300,MESSAGE_BACKROUND);

        put_word(message,100,100,3,MESSAGE_COLOR);
        put_word("reiniciando consola en ",100,100+34*3,3,MESSAGE_COLOR);
        put_word("5 segundos  !!!",100,100+68*3,3,MESSAGE_COLOR);
        for(int i=0;i<(18*5);i++){ //espera 5 segundo o 18*5 ticks
            _hlt();
        }

}      

static void zero_division() {
    error_sign("division por cero");
}


static void invalid_op_code(){
    error_sign("codigo de operaciones invalido");
}
