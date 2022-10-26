#include <system_calls.h>

static int tronOn = 0;
static int gameOn = 0;
static char lastKey = 0;

#define MATCHES 3
#define ESC 27
#define SQUARE_SIDE 8 //largo del lado del cuadrado con el cual se dibujan las lineas

#define BOARD_WIDTH 119 // 1000 (ancho seccion pantalla usada para el juego) / SQUARE_SIDE
#define BOARD_HEIGTH 87 // 744 (alto seccion pantalla usada para el juego) / SQUARE_SIDE

// para que se imprima en la porrcion de pantalla elegida
// estaria centrada y los margenes (para poner menu y etc) serian de 12 pixeles
#define OFFSET_X 36
#define OFFSET_Y 36


#define P1_STARTING_X 60
#define P1_STARTING_Y 10
#define P2_STARTING_X 60
#define P2_STARTING_Y 70

#define P1_COLOR 0x0000FF //azul
#define P2_COLOR 0xFF0000 //rojo

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

//se usa para evitar switchs al mover jugadores
static const int mover[4][2] = {{0,-1},{1,0},{0,1},{-1,0}}; //potencial problema

// BOARD_WIDTH x BOARD_HEIGHT
static int board[BOARD_WIDTH][BOARD_HEIGTH] = {{0}}; 

typedef struct player_t{
    int color;
    int currX;
    int currY;
    int alive;
    int direction; // sera usada en conjunto con la matriz mover
    int score; //puntaje
} player_t;

static player_t p1,p2;

void initialize_players(){ // se pasan los parametros default a cada jugador
    p1.color=P1_COLOR;
    p1.currX=P1_STARTING_X;
    p1.currY=P1_STARTING_Y;
    p1.alive=1;
    p1.direction=DOWN;
    p1.score=0;

    p2.color=P2_COLOR;
    p2.currX=P2_STARTING_X;
    p2.currY=P2_STARTING_Y;
    p2.alive=1;
    p2.direction=UP;
    p2.score=0;
    //board = {{0}}; causa un error
    for(int i=0; i<1024; i+=OFFSET_X){
        putSquare(i,0,OFFSET_X,0x00FF00);
        putSquare(0,i,OFFSET_X,0x00FF00);
    }

    for(int i=0; i<1024; i+=OFFSET_X){
        putSquare(i,768-OFFSET_X,OFFSET_X,0x00FF00);
        putSquare(1024-OFFSET_X,i,OFFSET_X,0x00FF00);
    }

    for(int i=0; i<BOARD_WIDTH; i++){
        for(int j=0; j<BOARD_HEIGTH; j++){
            board[i][j]=0;
        }
    }
}

// chequeo si jugador se encuentra en la matriz (que representa la pantalla)
// la macro usada anteriormente no terminaba de convencer

int insideBoard(int x, int y){
    return (x >= 0) && (x < BOARD_WIDTH) && (y >= 0) && (y < BOARD_HEIGTH);
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
        putSquare(0,0,1024,0); //Todo hacer q no frene y espera una tecla para jugar otra partida(imprimir socre cuando termina la partida)
        return 0;
    }
}

void changePlayerDirection(int player, int direction){ //solo recibira 1 o 2
    //cambio dir del jugador que corresponda
    if(player == 1 && MOD(direction - p1.direction) != 2) // para q no pueda invertir su direccion
        p1.direction = direction;
    else if(MOD(direction - p2.direction) != 2)
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
    putSquare(p1.currX*SQUARE_SIDE+1024*(p1.currY + OFFSET_Y)+ OFFSET_X,p1.currY*SQUARE_SIDE + OFFSET_Y,SQUARE_SIDE,P1_COLOR);
    putSquare(p2.currX*SQUARE_SIDE+1024*(p2.currY + OFFSET_Y) + OFFSET_X,p2.currY*SQUARE_SIDE + OFFSET_Y,SQUARE_SIDE,P2_COLOR);
}

void movePlayers(){
    //actualizo poiscion de ambos jugadors
    p1.currX += mover[p1.direction][0];
    p1.currY += mover[p1.direction][1];
    p2.currX += mover[p2.direction][0];
    p2.currY += mover[p2.direction][1];

    if(checkPlayersPosition()){ //si es que estan vivos marco respectivos cuadros y dibujo
        board[p1.currX][p1.currY] = 1;
        board[p2.currX][p2.currY] = 1;
        // x -> ya que el cursor en x es acumulativo le sumo la cantidad de renglones multiplicada por su ancho
        // y -> simplemente le paso la cantidad de renglones multiplicada por la altura
        // tamaño es el definido arriba
        // paso los colores correspondientes
        drawPlayers();
    }
}

void playTron(){
    tronOn = 1;
    putSquare(0,0,1034,0);

    for(int i=0; i<MATCHES && tronOn; i++){
        initialize_players();
        lastKey = 0;
        gameOn = 1;
        while(gameOn){
            keyboardHandler();
            if(gettick() % 2 == 0){
                movePlayers();
            }
        }
    }

    tronOn = 0;
}