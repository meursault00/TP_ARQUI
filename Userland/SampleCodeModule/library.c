
#include <system_calls.h>
#include <library.h>
#include <stdarg.h>
#define CURSOR_TICKS 9



#define IN_BOUNDS ((cursorX+fontsize*8)/1024)*16*fontsize < 736 // no termino de entender porque con 768 se pasa, REVISAR

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

// char strcmp( const char* stringA,const char* stringB)  
// {  
//     char flag = 0;
// 	int i = 0;
//     while(stringA[i]!='\0' && stringB[i]!='\0')  {  
//        if(stringA[i]!=stringB[i])  
//        {  
//            flag=1;  
//            break;  
//        }  
//        i++;  
//     }  
// 	if(stringA[i] != 0 || stringB[i] != 0){
// 		return 0;
// 	}
//     if(flag==0)  
//     	return 1;  
//  	return 0;  
// }  


char isHexChar( char character ){
	return ( character == 'A' || character == 'B' ||character == 'C' ||character == 'D' ||character == 'E' ||character == 'F' ||character == '0' ||character == '1' ||character == '2' ||character == '3' ||character == '4' ||character == '5' ||character == '6' ||character == '7' || character == '8' ||character == '9' );
}

char onlyHexChars( char * string ){
	for ( int i = 0; string[i] != 0; i++ )
		if ( !(isHexChar(string[i])))
			return 0;
	return 1;
}

void splitString( char * original, char * firstSplit, char splitter ){
	int i = 0, j = 0, k = 0;
	int flag = 0;
	for ( ; original[i] != 0; i++ ){
		if ( original[i] == ' ' && flag == 0){
			flag = 1;
			i++;
		}
		if ( flag ){
			firstSplit[j++] = original[i];
		}else{
			original[k++] = original[i];
		}
	}
	firstSplit[j]=0;
	original[k] = 0;
	return;
}


int countDigits( int number ){
    int digits, limit;
    if ( number < 0 )
        number*=-1;
    for ( digits = 1, limit = 10; ; digits++, limit*=10 ){
        if ( number < limit )
            break;
    }
	return digits;
}

void numLoader( int number, char * buffer, int digits ){
	for ( digits--; number != 0; number/=10, digits--){
        buffer[digits] = number%10 + 48;       // voy construyendo el numero de atras para adelante
    }
}

void intToString( int number, char * buffer, int digits ){
	if ( number<0 ){
		buffer[0]= '-';
		buffer[digits+1]=0;
		numLoader(-number, buffer+1,digits);
	}
	else{
		buffer[digits]=0;
		numLoader(number, buffer,digits);
	}
   
	return;
}

void floatToString( float number, char * buffer, int digits  ){
	intToString(number,buffer,digits);
	buffer[digits]='.';
	if ( number < 0 )
		number*=-1;
	
    number-=(int)number;
    int i;
	for ( i = digits+1; i < digits+1 + 8; i++ ){
        int aux =((int) (number*10)) %10;
		number*=10;
        buffer[i] = (char) (aux + 48);
    }
	buffer[i]=0;
	return;
}

static void updateCursor(){
	cursorX += fontsize*8;
	if((cursorX / 1024)*fontsize*16 > cursorY){ // cursorX % 1024 == 0 
			cursorY += fontsize*16; 
	}
}

void appendchar( char character ){
	if(character == '\n'){
		newline();
		return;
	}
	
	drawCursor(0x000000);
	putcharSpecifics(character,cursorX,cursorY,fontsize,fontcolor);
	updateCursor();
	drawCursor(fontcolor);
}

void newline(){
	int aux = cursorY;
	do{appendchar(' ');} while(cursorY == aux && IN_BOUNDS);
}

void backspace(){
	if(cursorX != 0){
		drawCursor(0x000000);
		cursorX -= fontsize * 8;
		cursorY = (cursorX / 1024)*16*fontsize;
		putSquare(cursorX,cursorY,fontsize*8,0x000000);
		putSquare(cursorX,cursorY+fontsize*8,fontsize*8,0x000000);
		drawCursor(fontcolor);
	}
}

void putchar(char c){
	appendchar(c);
}
void putcharSpecifics(char character, int x, int y, int size,int color){
	write(character,x,y,size,color);
}
int strcmp(const char* s1, const char* s2){
    while (*s1 && (*s1 == *s2)){
        s1++, s2++;
	}
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int strlen(const char *str){
	int s;
	for (s = 0; str[s] != 0; ++s);
	return s;
}

void print (char * foundation, ...){

	// se inicializa la lista de parametros indefinidos
	va_list vl;
	int i = 0, j=0;
	// el buffer final y el buffer temporal para las conversiones numericas
	// buff deberia ser dinamico pero no tenemos malloc :/
	char buff[100]={0}, tmp[20];
	// buffer para el string
	char * str_arg;

	// macro de inicializacion
	va_start( vl, foundation );

	// mientras haya caracteres y argumentos
	while (foundation && foundation[i])
	{
		// caso especial de que encuentre un porcentaje que representa la insercion de una variable
	  	if (foundation[i] == '%'){
	  	i++;
	  	switch (foundation[i]) {
	  	  // caso char
	  	  case 'c': {
			// se toma el argumento que se presume de tipo char y se lo castea para guardarlo
	  	    buff[j] = (char)va_arg( vl, int );
	  	    j++;
	  	    break;
	  	  }
	  	  // caso integer
	  	  case 'd': {
			// se toma un int, se lo pasa a decimal y luego a string guardandose en tmp
	  	    _itoa(va_arg( vl, int ), tmp, 10);
			// se copia tmp al buffer
	  	    strcpy(&buff[j], tmp);
			// se aumenta la posicion del string final
	  	    j += strlen(tmp);
	  	    break;
	  	  }
	  	  // caso hexa
	  	  case 'x': {
			// identico al previo pero con base 16
	  	    _itoa(va_arg( vl, int ), tmp, 16);
	  	    strcpy(&buff[j], tmp);
	  	    j += strlen(tmp);
	  	    break;
	  	  }
	  	  // caso octal
	  	  case 'o': {
			// identico al anterior pero con base 8
	  	    _itoa(va_arg( vl, int ), tmp, 8);
	  	    strcpy(&buff[j], tmp);
	  	    j += strlen(tmp);
	  	    break;
	  	  }
	  	  // caso string
	  	  case 's': {
			// no se necesita conversion entonces se guarda directo
	  	    str_arg = va_arg( vl, char* );
	  	    strcpy(&buff[j], str_arg);
	  	    j += strlen(str_arg);
	  	    break;
	  	  }
	  	}
		// caso donde no hay un porcentaje y se continua el string como si nada
	  	}else {
	    	buff[j] = foundation[i];
	    	j++;
	  	}
	  i++;
	} 
  appendstring(buff);
  va_end(vl);
}

void strcpy( char * destination, char * origin ){
	int i;
	for (  i = 0; origin[i]!='\0'; i++ )
		destination[i] = origin[i];
	destination[i] = '\0';
}

char *_strrev (char *str){
  int i;
  int len = 0;
  char c;
  if (!str)
    return 0;
  while(str[len] != '\0'){
    len++;
  }
  for(i = 0; i < (len/2); i++)
  {
    c = str[i];
    str [i] = str[len - i - 1];
    str[len - i - 1] = c;
  }
  return str;
}

char * _itoa(int i, char *strout, int base){
  char *str = strout;
  int digit, sign = 0;
  if (i < 0) {
    sign = 1;
    i *= -1;
  }
  while(i) {
    digit = i % base;
    *str = (digit > 9) ? ('A' + digit - 10) : '0' + digit;
    i = i / base;
    str ++;
  }
  if(sign) {
  *str++ = '-';
  }
  *str = '\0';
  _strrev(strout);
  return strout;
}


void printf ( char * foundation, void * parameters[] ){
    int j = 0; // posicion en los parametros
    for ( int i = 0; foundation[i] != 0; i++ ){
        if ( foundation[i] == '%' ){
            i++;
            switch (foundation[i])
            {
            case 's':{
                appendstring((char*)parameters[j++]); 
                break;
            }
            
            case 'd':{
                int number = *((int*)parameters[j++]);
                int digits = countDigits(number);
	            char buffer[ number < 0 ? digits+2:digits+1];
	            intToString(number,buffer,digits);
                appendstring(buffer); 
                break;
            }
            case 'f':{
                float floatNumber = *((float*)parameters[j++]);
                int digits = countDigits((int)floatNumber);
	            char buffer2[ floatNumber < 0 ? digits+3+8:digits+2+8]; // 8 es la precision de decimales que tiene nuestro float 2 es en casode que haya que agregar un punto y un '\0' al final, y tambien esta el caso del menos
	            floatToString(floatNumber,buffer2,digits);
	            appendstring(buffer2); 
                break;
            }
            default:
                break;
            }
        }else{
            appendchar(foundation[i]);
        } 
    }
}

void printInt(uint64_t integer){
	char buffer[20] = {0};
	uintToBase(integer,buffer,10);
	appendstring(buffer);
}
void printHex(uint64_t integer){
	char buffer[20] = {0};
	uintToBase(integer,buffer,16);
	appendstring(buffer);
}

void println(char * string){
	appendstring(string);
	newline();
}
void appendstring( char * string ){
	for ( int i = 0; string[i] != 0; i++ ){
		appendchar( string[i]);
	}
}


/*


void putnewline( void) {
	int i = 0;
	while( i < 256 ){
		putchar(1,' ');
		i++;
	}
}
*/

void drawCursor(int color){
	/* cursor editor de texto
	for(int i=0; i<8; i++){
		put_square(cursorX+fontSize*2,cursorY+fontSize*2*i,fontSize*2,color);
	*/
	// CURSOR TERMINAL
	putSquare(cursorX,cursorY,fontsize*8,color);
	putSquare(cursorX,cursorY+fontsize*8,fontsize*8,color);	
}

void restartCursor(){
	cursorX = 0;
	cursorY = 0;
}

void changeFontSize(int increment){
	if((fontsize + increment) > 0 && (fontsize + increment) <= 64)
		fontsize+=increment;
}

void refreshCursor(){
	if(gettick() % CURSOR_TICKS == 0){
		if(currentCursorColor == fontcolor){
			currentCursorColor = 0x000000;
		}
		else{
			currentCursorColor = fontcolor;
		}
		drawCursor(currentCursorColor);
	}
}

char streql( const char* stringA,const char* stringB)  
{  
	int i = 0;
    while(stringB[i]!='\0')  {  
		if (stringA[i] == '\0' || stringA[i]!=stringB[i])
			return 0;
       	i++;  
    }  
	if ( stringA[i]!=0 ) 
		return 0;
    return 1;
} 