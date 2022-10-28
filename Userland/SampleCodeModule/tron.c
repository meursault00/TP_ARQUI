#include <system_calls.h>
#include <library.h>

static int tronOn = 0;
static int gameOn = 0;
static char lastKey = 0;
static int lastTick = 0;

#define BESTOF 3
#define ESC 27
#define SQUARE_SIDE 8 //largo del lado del cuadrado con el cual se dibujan las lineas

#define BOARD_WIDTH 119 // 1000 (ancho seccion pantalla usada para el juego) / SQUARE_SIDE
#define BOARD_HEIGHT 87 // 744 (alto seccion pantalla usada para el juego) / SQUARE_SIDE

// para que se imprima en la porrcion de pantalla elegida
// estaria centrada y los margenes (para poner menu y etc) serian de 12 pixeles
#define OFFSET_X 36
#define OFFSET_Y 36


#define P1_STARTING_X 60
#define P1_STARTING_Y 10
#define P2_STARTING_X 60
#define P2_STARTING_Y 70

#define P1_COLOR 0x333652 //azul
#define P2_COLOR 0xFAD02C //amarillo

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define MOD(x) ((x)>0? (x) : (x)*(-1))

static void initialize_players();
static int insideBoard(int x, int y);
static int checkPlayersPosition();
static void changePlayerDirection(int player, int direction);
static void keyboardHandler();
static void resetScore();
static void printScore();
static void daleBo();

//se usa para evitar switchs al mover jugadores
static const int mover[4][2] = {{0,-1},{1,0},{0,1},{-1,0}}; //potencial problema

// BOARD_WIDTH x BOARD_HEIGHT
static int board[BOARD_WIDTH][BOARD_HEIGHT] = {{0}}; 

typedef struct player_t{
    int color;
    int currX;
    int currY;
    int alive;
    int direction; // sera usada en conjunto con la matriz mover
    char score; //puntaje
} player_t;

static player_t p1,p2;

void initialize_players(){ // se pasan los parametros default a cada jugador
    p1.color=P1_COLOR;
    p1.currX=P1_STARTING_X;
    p1.currY=P1_STARTING_Y;
    p1.alive=1;
    p1.direction=DOWN;

    p2.color=P2_COLOR;
    p2.currX=P2_STARTING_X;
    p2.currY=P2_STARTING_Y;
    p2.alive=1;
    p2.direction=UP;
    //board = {{0}}; causa un error

    for(int i=OFFSET_X; i<1024-OFFSET_X; i+=SQUARE_SIDE){
        for(int j=OFFSET_Y; j<768 - OFFSET_Y; j++){
            putSquare(i,j,1,0x90ADC6);
        }
    }

    for(int i=OFFSET_Y; i<768-OFFSET_Y; i+=SQUARE_SIDE){
        for(int j=OFFSET_X; j<1024 - OFFSET_X; j++){
            putSquare(j,i,1,0x90ADC6);
        }
    }

    for(int i=0; i<1024; i+=OFFSET_X){
        putSquare(i,0,OFFSET_X,0x90ADC6);
        putSquare(0,i,OFFSET_X,0x90ADC6);
    }

    for(int i=0; i<1024; i+=OFFSET_X){
        putSquare(i,768-OFFSET_X,OFFSET_X,0x90ADC6);
        putSquare(1024-OFFSET_X,i,OFFSET_X,0x90ADC6);
    }

    for(int i=0; i<BOARD_WIDTH; i++){
        for(int j=0; j<BOARD_HEIGHT; j++){
            board[i][j]=0;
        }
    }
}

// chequeo si jugador se encuentra en la matriz (que representa la pantalla)
// la macro usada anteriormente no terminaba de convencer

int insideBoard(int x, int y){
    return (x >= 0) && (x < BOARD_WIDTH) && (y >= 0) && (y < BOARD_HEIGHT);
}

/**
@param player tiene current position en X e Y
@returns boolean 0 si algun jugador ha muerto, 1 si ambos viven
*/

int checkPlayersPosition(){
    // si pasa no esta en el tablero o esta en una posicion pisada los mato
    if(!insideBoard(p1.currX,p1.currY) || board[p1.currX][p1.currY]){
        p1.alive =0;
    }
    if(!insideBoard(p2.currX,p2.currY) || board[p2.currX][p2.currY]){
        p2.alive =0;
    }

    if(p1.alive && p2.alive)
        return 1;
    else{
        if(p1.alive)
            p1.score++; // si uno sobrevivio aumento su puntaje
        else if(p2.alive)
            p2.score++;
        gameOn = 0;
        putSquare(0,0,1024,0xE9EAEC); //Todo hacer q no frene y espera una tecla para jugar otra partida(imprimir socre cuando termina la partida)
        return 0;
    }
}

void changePlayerDirection(int player, int direction){ //solo recibira 1 o 2
    int aux = MOD(direction - p1.direction);
    //cambio dir del jugador que corresponda
    if(player == 1){ // para q no pueda invertir su direccion
        if(aux == 2 || aux == 0)
            return;
        p1.direction = direction;
        return;
    }
    aux = MOD(direction - p2.direction);
    if(aux != 2 && aux != 0)
        p2.direction = direction;
}

void keyboardHandler(){
    int aux = getLastKey();
    if(lastKey != aux){
        lastKey = aux;
        switch(aux){
        case ESC:
            //gameSwitch(0);
            tronOn = 0;
            putSquare(0,0,1024,0);

        /*
        case ' ':
            gameSwitch(1); // al apretar la barra espaciadora se inicia el juego
            break;
        */
        case 'w':
            changePlayerDirection(1,UP);
            break;
        case 'a':
            changePlayerDirection(1,LEFT);
            break;
        case 's':
            changePlayerDirection(1,DOWN);
            break;
        case 'd':
            changePlayerDirection(1,RIGHT);
            break;
        
        case 'i':
            changePlayerDirection(2,UP);
            break;
        case 'j':
            changePlayerDirection(2,LEFT);
            break;
        case 'k':
            changePlayerDirection(2,DOWN);
            break;
        case 'l':
            changePlayerDirection(2,RIGHT);
            break;
        default:
            break;
        }
    }
}

void drawPlayers(){
    putSquare(p1.currX*SQUARE_SIDE + OFFSET_X,p1.currY*SQUARE_SIDE + OFFSET_Y,SQUARE_SIDE,P1_COLOR);
    putSquare(p2.currX*SQUARE_SIDE + OFFSET_X,p2.currY*SQUARE_SIDE + OFFSET_Y,SQUARE_SIDE,P2_COLOR);
}

void movePlayers(){
    if(checkPlayersPosition()){ //si es que estan vivos marco respectivos cuadros y dibujo
        board[p1.currX][p1.currY] = 1;
        board[p2.currX][p2.currY] = 1;
        // x -> ya que el cursor en x es acumulativo le sumo la cantidad de renglones multiplicada por su ancho
        // y -> simplemente le paso la cantidad de renglones multiplicada por la altura
        // tamaño es el definido arriba
        // paso los colores correspondientes
        drawPlayers();
    }
    //actualizo poiscion de ambos jugadors
    p1.currX += mover[p1.direction][0];
    p1.currY += mover[p1.direction][1];
    p2.currX += mover[p2.direction][0];
    p2.currY += mover[p2.direction][1];

}

void resetScore(){
    p1.score = '0';
    p2.score = '0';
}

void printScore(){
    putcharSpecifics(p1.score,492,0,2,P1_COLOR);
    putcharSpecifics(p2.score,532,0,2,P2_COLOR);

}

void playTron(){
    tronOn = 1;
    putSquare(0,0,1024,0xE9EAEC);
    lastTick = gettick();

    resetScore();
    while((p1.score - '0' < BESTOF) && (p2.score - '0' < BESTOF) && tronOn){
        initialize_players();
        //lastKey = 0;
        printScore();
        gameOn = 1;
        while(gameOn){
            //getchar();
            keyboardHandler();
            if(gettick() != lastTick){
                movePlayers();
                lastTick = gettick();
            }
        }
        beep(440,2);
    }
    
    for(int i=0; i<1024; i+=8){
        for(int j=0; j<256; j+=8){
            putSquare(i,j,8,0x333652);
        }
        for(int j=256; j<512; j+=8){
            putSquare(i,j,8,0xFAD02C);
        }
        for(int j=512; j<768; j+=8){
            putSquare(i,j,8,0x333652);
        }
    }
    if(p1.score == '3')
        putstringSpecifics("1 WINS",32,256,20,0x333652);
    else
        putstringSpecifics("2 WINS",32,256,20,0x333652);
    
    daleBo(4);

    clearkeybuffer();

    tronOn = 0;
    //putSquare(0,0,1024,0);

}

void daleBo(int n){
    beep(262,n); //C
    beep(294,n); //D
    beep(330,n); //E
    for(int i=0; i<8; i++)
        beep(349,n); //F
    beep(330,n); //E
    beep(294,n); //D
    beep(349,n); //F
    beep(294,2*n); //D

    beep(262,n); //C
    beep(294,n); //D
    beep(330,n); //E
    for(int i=0; i<8; i++)
        beep(349,n); //F
    beep(330,n); //E
    beep(294,n); //D
    beep(349,n); //F
    beep(392,2*n); //G

    beep(262,n); //C
    beep(294,n); //D
    beep(330,n); //E
    for(int i=0; i<8; i++)
        beep(392,n); //G
    beep(349,n); //F
    beep(330,n); //E
    beep(392,n); //G
    beep(330,2*n); //E

    beep(262,n); //C
    beep(294,n); //D
    beep(330,n); //E
    for(int i=0; i<4; i++)
        beep(349,n); //F
    for(int i=0; i<3; i++)
        beep(330,n); //E
    beep(349,n); //F
    beep(330,n); //E
    for(int i=0; i<3; i++)
        beep(294,2*n); //D
}