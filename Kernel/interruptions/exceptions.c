#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_EXCEPTION_ID 1


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

static void zero_division() {
    // Handler para manejar excepcíon
    //((EntryPoint) sampleCodeModuleAddress)(); creemos q reinicia la consola xq va al user
}


static void invalid_op_code(){

}