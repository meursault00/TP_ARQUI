#include <keyboard_driver.h>


static int language = SPANISH;

//estan cargados los teclados en ingles y español
static char keyboards[2][MAX_SCANCODE][2] ={
    {
    {   0,0   },
    {ESC , ESC}, 
    { '1','!' }, 
    { '2','@' },
    { '3','#' },
    { '4','$' }, 
    { '5','%' }, 
    { '6','^' },
    { '7','&' },
    { '8','*' }, 
    { '9','(' }, 
    { '0',')' },
    { '-','_' },
    { '=','+' }, 
    {'\b','\b'}, 
    {'\t','\t'},
    { 'q','Q' },
    { 'w','W' }, 
    { 'e','E' }, 
    { 'r','R' },
    { 't','T' },
    { 'y','Y' }, 
    { 'u','U' }, 
    { 'i','I' },
    { 'o','O' },
    { 'p','P' }, 
    { '[','{' }, 
    { ']','}' },
    {'\n','\n'},
    {   0,0   }, 
    { 'a','A' }, 
    { 's','S' },
    { 'd','D' },
    { 'f','F' }, 
    { 'g','G' }, 
    { 'h','H' },
    { 'j','J' },
    { 'k','K' }, 
    { 'l','L' }, 
    { ';',':' },
    {'\'','\"'},
    { '`','~' }, 
    {   0,0   }, 
    { '\\','|'},
    { 'z','Z' },
    { 'x','X' }, 
    { 'c','C' }, 
    { 'v','V' },
    { 'b','B' },
    { 'n','N' }, 
    { 'm','M' }, 
    { ',','<' },
    { '.','>' },
    { '/','?' }, 
    {   0,0   }, 
    {   0,0   },
    {   0,0   },
    { ' ',' ' }    
    },
    {
    {   0,0   },
    {ESC , ESC}, 
    { '1','!' }, 
    { '2','"' },
    { '3','#' },
    { '4','$' }, 
    { '5','%' }, 
    { '6','&' },
    { '7','/' },
    { '8','(' }, 
    { '9',')' }, 
    { '0','=' },
    { '\'','?'},
    { '|','}' }, 
    {'\b','\b'}, 
    {'\t','\t'},
    { 'q','Q' },
    { 'w','W' }, 
    { 'e','E' }, 
    { 'r','R' },
    { 't','T' },
    { 'y','Y' }, 
    { 'u','U' }, 
    { 'i','I' },
    { 'o','O' },
    { 'p','P' }, 
    { '`','\"' }, 
    { '+','*' },
    {'\n','\n'},
    {   0,0   }, 
    { 'a','A' }, 
    { 's','S' },
    { 'd','D' },
    { 'f','F' }, 
    { 'g','G' }, 
    { 'h','H' },
    { 'j','J' },
    { 'k','K' }, 
    { 'l','L' }, 
    { '~'+1,'~' },
    {'{','['},
    { '`','~' }, 
    {   0,0   }, 
    { '}',']'},
    { 'z','Z' },
    { 'x','X' }, 
    { 'c','C' }, 
    { 'v','V' },
    { 'b','B' },
    { 'n','N' }, 
    { 'm','M' }, 
    { ',',';' },
    { '.',':' },
    { '-','_' }, 
    {   0,0   }, 
    {   0,0   },
    {   0,0   },
    { ' ',' ' }    
}};

static int shiftActivated = 0;
static int capsActivated = 0;

static char keyBuffer[MAX_BUFFER];
static int bufferCount = 0;

void clearKeyBuffer(){
	for ( int i = 0; i < MAX_BUFFER; i++ )
		keyBuffer[i] = (char)0;
	bufferCount= 0;
}

void changeLanguage(int lan){
    language = lan;
}



//saca el primero que esta en el vector
static char popBuffer(){
    char key = keyBuffer[0];
    for(int i = 0; i < bufferCount; i++){
        keyBuffer[i] = keyBuffer[i+1];
    }
    bufferCount--;
    return key;
}
/**
 * 
 * @return devuelve el la primer tecla presionada
 */
char getKey(){
    if(bufferCount <= 0)
        return 0;
    
    return popBuffer();
}
/**
 * @return el ultimo caracter presionado
 */
char getLastChar(){
    return keyBuffer[bufferCount-1];
}


static int isValidScancode(int scancode){
    return scancode > 0 && scancode < MAX_SCANCODE;
}

static int isLetter(int scancode){
    if(scancode == 0x27)
        return 1;
    char ascii = keyboards[language][scancode][0];
    return  (ascii >= 'a' && ascii <= 'z');
}

/**
 * @brief guarda el caracter q se presiono en el buffer 
 */
void storeKey(){

    int scancode  = inb(0x60);
    
    switch(scancode){
        case LSHIFT_PRESSED:
            shiftActivated = 1;
            break;
        case RSHIFT_PRESSED:
            shiftActivated = 1;
            break;
        case LSHIFT_RELEASED:
            shiftActivated = 0;
            break;  
        case RSHIFT_RELEASED:
            shiftActivated = 0;
            break;
        case CAPSLOCK:
            capsActivated = !capsActivated;
            break;
        case SCANCODE_UP_ARROW:
            keyBuffer[bufferCount++] = ASC_UP;
            break;
        case SCANCODE_DOWN_ARROW:
            keyBuffer[bufferCount++] = ASC_DOWN;
            break;
        case SCANCODE_LEFT_ARROW:
            keyBuffer[bufferCount++] = ASC_LEFT;
            break;
        case SCANCODE_RIGHT_ARROW:
            keyBuffer[bufferCount++] = ASC_RIGHT;
            break;
        default:
            if(isValidScancode(scancode) && bufferCount < MAX_BUFFER){
                if( isLetter(scancode) && capsActivated ){
                    keyBuffer[bufferCount] = keyboards[language][scancode][1];
                }
                else{
                    keyBuffer[bufferCount] = keyboards[language][scancode][shiftActivated ? 1: 0];   
                }
                bufferCount++;
            }
            break;

    }
    return;
    
}





















