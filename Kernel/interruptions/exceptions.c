#include <video_driver.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_EXCEPTION_ID 6


static void zero_division();
static void invalid_op_code();

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
        put_rectangle(200,200,800,300,0x2f2b2b);
        put_rectangle(190,190,800,300,0xFF0000);

        put_word(message,200,200,3,0xFFFFFF);
        put_word("escriba y ejecute",200,200+34*3,3,0xFFFFFF);
        put_word("clear para continuar   !!!",200,200+68*3,3,0xFFFFFF);
}      

static void zero_division() {
    error_sign("division por cero");
}


static void invalid_op_code(){
    error_sign("codigo de operaciones invalido");
}
