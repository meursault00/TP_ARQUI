
#include <system_calls.h>
#include <library.h>
#include <stdarg.h>
#define CURSOR_TICKS 9



#define IN_BOUNDS ((cursorX+fontsize*8)/1024)*16*fontsize < 736 // no termino de entender porque con 768 se pasa, REVISAR
int lastEnter(){
	return cursorY+16*fontsize > 736;
}

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

unsigned char hexToChar( unsigned char a, unsigned char b ){
	unsigned char returnChar = 0; // 0000 0000
	if ( a >= 'A' && a <= 'F' )
		returnChar = (a%'A')+10; // caso B seria 0000 1011
	else if ( a >= '0' && a <= '9' )
		returnChar =  a%'0';
	returnChar = returnChar<<4; // 1011 0000
	if ( b >= 'A' && b <= 'F' )
		returnChar = returnChar + (b%'A')+10; // caso b = F seria 1011 1111 
	else if ( b >= '0' && b <= '9' )
		returnChar = returnChar + (b%'0');
	return returnChar;
}

void memCopy( char * pointer1, char * pointer2, int chars ){
	for ( int i = 0; i < chars; i++ )
		pointer1[i] = pointer2[i];
}

uint64_t hexstringToInt(char * s){
    int c;
    uint64_t rta = 0;

    if(s == '0' &&(s+1) == 'x')
        s += 2;

    int len = strlen(s);

    for (int i = 0; i < len; i++){
        c = s[len - 1 - i] - '0';
        if(c < 0 || c > 9){
            c = s[len - 1 - i] - 'A' + 10;
            if(c < 10 || c > 15)
                return 0;
        }
        rta += c*pow(16, i);
    }
    return rta;
}

int pow(int base, unsigned int exp){
	int rta=1;
	for(int i=0;i<exp;i++)
		rta*=base;
	return rta;
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
	if(cursorX + fontsize * 8 >= 1024){
		cursorY += fontsize*16;
		cursorX = 4;
	}
	else{
		cursorX += fontsize*8;
	}
}

void appendchar( char character ){
	if(character == '\n'){
		newline();
		return;
	}
	
	drawCursor(currentCursorColor);
	putcharSpecifics(character,cursorX,cursorY,fontsize,fontcolor);
	updateCursor();
	drawCursor(fontcolor);
}

void newline(){
	drawCursor(currentCursorColor);
	cursorX = 4;
	cursorY += 16*fontsize;
}
void rollLeft(){
	drawCursor(currentCursorColor);
	cursorX -= 8*fontsize;
	if(cursorX < 4){
		cursorX = 1024 - 8*fontsize;
		cursorY -= 16*fontsize;
	}
	drawCursor(fontcolor);
}
void backspace(){
	if(cursorX != 4){
		drawCursor(currentCursorColor);
		if(cursorX-fontsize*8 < 0){
			cursorY -= fontsize*16;
			cursorX = 1023;
		}
		else
			cursorX -= fontsize * 8;
		putSquare(cursorX,cursorY,fontsize*8,BACKGROUND_COLOR);
		putSquare(cursorX,cursorY+fontsize*8,fontsize*8,BACKGROUND_COLOR);
		drawCursor(fontcolor);
	}
}


void putchar(char c){
	appendchar(c);
}
void putcharSpecifics(char character, int x, int y, int size,int color){
	write(character,x,y,size,color);
}

void putstringSpecifics(char * string, int x, int y, int size, int color){
	int accum;
	for ( int i = 0; string[i] != 0; i++ ){
		accum=  i*size*8;
		putcharSpecifics(string[i], x + accum, y, size, color);

	}
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
void setCursor( int x, int y ){
	cursorX = x;
	cursorY = y;
}

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
	cursorX = 4;
	cursorY = 4;
}

void changeFontSize(int increment){
	if((fontsize + increment) > 0 && (fontsize + increment) <= 64)
		fontsize+=increment;
}

void refreshCursor(){
	if(gettick() % CURSOR_TICKS == 0){
		if(currentCursorColor == fontcolor){
			currentCursorColor = BACKGROUND_COLOR;
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
int stringToInt(char * string, int base){
    int number = 0;
    int i = 0;
    int sign = 1;
    if ( string[0] == '-' ){
        sign = -1;
        i++;
    }
    for ( ; string[i] != 0; i++ ){
        if ( string[i] >= '0' && string[i] <= '9' ){
            number = number*base + string[i] - '0';
        }else if ( string[i] >= 'A' && string[i] <= 'F' ){
            number = number*base + string[i] - 'A' + 10;
        }
    }
    return number*sign;
}

static unsigned char atointhex( unsigned char a){
    unsigned char returnChar = 0; // 0000 0000
    if ( a >= 'A' && a <= 'F' )
        returnChar = (a%'A')+10; // caso B seria 0000 1011
    else if ( a >= '0' && a <= '9' )
        returnChar =  a%'0';
    return returnChar;
}

int scan (char * str, ...){
	va_list vl;
    int i = 0, j=0, ret = 0;
    char buff[100] = {0};
 	va_start( vl, str );
 	i = 0;
 	while (str && str[i])
 	{
 	    if (str[i] == '%') 
 	    {
 	       i++;
 	       switch (str[i]) 
 	       {
				case 's':
				{	char *string;
					string=va_arg( vl, char* );
					char buff[100];
					strcpy(buff,string);
					int k = 0;
                char c;
					do{
					c= getchar();      //clear buffer de los espacios
					}while (c==' ');
				appendchar('A');
                while(c != '\n' && c!=' '){
					buff[k++] = c;
                    c = getchar();
                }
                	buff[k] = '\0';
					strcpy(string,buff);
					ret++;
					break;
				}
 	           case 'c': 
 	           {	char c;
					do{
					c= getchar();      //clear buffer de los espacios
					}while (c==' ');
	 	           *(char *)va_arg( vl, char* ) =c;
	 	           ret ++;
	 	           break;
 	           }
 	           case 'd': 
 	           {
	 	        	char c;
					do{
					c= getchar();      //clear buffer de los espacios
					}while (c==' ');

                	int sign = 1;
                	if(c == '-'){
                    	sign = -1;
                    	c = getchar();
                	}
                	int result = 0;
                	while(c != '\n' && c!=' '){
                    	result = result*10 + (c - '0');
                    	c = getchar();
                	}
				*(int *)va_arg( vl, int* ) =result*sign;
	 	           ret++;
	 	           break;
 	            }
 	            case 'x': 
 	            {	
					char c;
					do{
					c= getchar();      //clear buffer de los espacios
					}while (c==' ');
                	int result = 0;
                	while(c != '\n' && c!=' '){
                    	result = result*16 + atointhex(c);
                    	c = getchar();
                	}
				*(int *)va_arg( vl, int* ) =result;
	 	        
	 	           ret++;
	 	           break;
 	            }
				case 'f':
				{
					char c;
					do{
					c= getchar();      //clear buffer de los espacios
					}while (c==' ');
                int sign = 1;
                if(c == '-'){
                    sign = -1;
                    c = getchar();
                }
                int result = 0;
                while(c != '.'){
                    result = result*10 + (c - '0');
                    c = getchar();
                }
                c = getchar();
                int decimal = 0;
                int decimalCount = 0;
                while(c != '\n' && c!=' '){
                    decimal = decimal*10 + (c - '0');
                    c = getchar();
                    decimalCount++;
                }
				*(float*)va_arg( vl, float* )=((float)result + (float)decimal/(float)pow(10,decimalCount))*sign;
				ret++;
					break;
				}
 	        }
 	    } 
        i++;
    }
    va_end(vl);
    return ret;
}

