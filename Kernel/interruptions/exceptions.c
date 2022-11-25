#include <exceptions.h>


void exceptionsBackupValues(uint64_t ipAdress, uint64_t stackAdress);
static void zero_division();
static void invalid_op_code();
static uint64_t continueExecutionIP, continueExecutionSP;

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
    }

}

static void error_sign(char * message,uint64_t * stackFrame){
    //dibujo contemporaneo de la exception
    char buffer[50];
    put_rectangle(0,0,955,565,MESSAGE_SHADOW);
    put_rectangle(0,0,935,545,MESSAGE_BACKROUND);

    put_word(message,230,10,2,MESSAGE_COLOR);

	char registers[17][6] = { "R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ",
	"R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
	"RAX: ", "IP: ", "RSP: "};
	for ( int i = 0; i < 16; i++ ){
        put_word(registers[i],0,i*16*2,2,MESSAGE_COLOR);
        uintToBase(*(stackFrame+i),buffer,16);
        put_word(buffer,32*3,i*16*2,2,MESSAGE_COLOR);
	}
    put_word(registers[16],0,16*16*2,2,MESSAGE_COLOR);
	uintToBase((uint64_t)(stackFrame + 15 + 3), buffer, 16); //RSP, caso especial
	put_word(buffer,32*3,16*16*2,2,MESSAGE_COLOR);


    put_word("reiniciando consola en ",230,10+34*2,2,MESSAGE_COLOR);
    put_word("5 segundos  !!!",230,10+68*2,2,MESSAGE_COLOR);
    for(int i=0;i<(18*5);i++){ //espera 5 segundo o 18*5 ticks
        _hlt();
    }

}   
//strlen
int strlen(char * string){
	int i=0;
	while(string[i]!=0){
		i++;
	}
	return i;
}   
// restart sample code module
static void restartSampleCodeModule(uint64_t * exceptionStackframe){
	exceptionStackframe[15] = continueExecutionIP;
	exceptionStackframe[15+3] = continueExecutionSP;
    
}
static void zero_division(uint64_t * stackFrame) {
    error_sign("division por cero",stackFrame);
	restartSampleCodeModule(stackFrame);

}


static void invalid_op_code(uint64_t * stackFrame){
    error_sign("codigo de operaciones invalido",stackFrame);
    restartSampleCodeModule(stackFrame);

}

void exceptionsBackupValues(uint64_t ipAdress, uint64_t stackAdress){
	continueExecutionIP = ipAdress;
	continueExecutionSP = stackAdress;

}

