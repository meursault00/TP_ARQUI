#include <video_driver.h>
#include <naiveConsole.h>

static int tronSwitch = 0;
static int gameOn = 1;
static int canMove = 0;

#define MATCHES 1

#define SQUARE_SIDE 8 //largo del lado del cuadrado con el cual se dibujan las lineas

#define BOARD_WIDTH 125 // 1000 (ancho seccion pantalla usada para el juego) / SQUARE_SIDE
#define BOARD_HEIGTH 93 // 744 (alto seccion pantalla usada para el juego) / SQUARE_SIDE

// para que se imprima en la porrcion de pantalla elegida
// estaria centrada y los margenes (para poner menu y etc) serian de 12 pixeles
#define OFFSET_X 12
#define OFFSET_Y 12


#define P1_STARTING_X 63
#define P1_STARTING_Y 10
#define P2_STARTING_X 63
#define P2_STARTING_Y 70

#define P1_COLOR 0x0000FF //azul
#define P2_COLOR 0xFF0000 //rojo

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define MOD(x) ((x)>0? (x) : (x)*(-1))

//se usa para evitar switchs al mover jugadores
static const int mover[4][2] = {{0,-1},{1,0},{0,1},{-1,0}}; //potencial problema

// BOARD_WIDTH x BOARD_HEIGHT
static int board[125][93] = {{0}}; // warning: missing braces around initializer [-Wmissing-braces]

typedef struct player_t{
    int color;
    int currX;
    int currY;
    int alive;
    int direction; // sera usada en conjunto con la matriz mover
    int score; //puntaje
} player_t;

static player_t p1,p2;

/*
void display_menu(){
    // escribir intro al juego
    
}
*/

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
    for(int i=0; i<125; i++){
        for(int j=0; j<93; j++){
            if(i==0)
                put_square(i*8,j*8,12,0x00FF00);
            if(i==124)
                put_square(i*8+20,j*8,12,0x00FF00);
            if(j==0)
                 put_square(i*8,j+11,12,0x00FF00);
            //todo el de abajo no lo puedo ver por limites de hardware -bruzo 
            board[i][j] = 0;
        }
    }
}


/*
void moveSwitch(int value){
    canMove = value;
}
*/

// chequeo si jugador se encuentra en la matriz (que representa la pantalla)
// la macro usada anteriormente no terminaba de convencer
static int insideBoard(int x, int y){
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
        tronSwitch = 0;
        VideoClearScreen(); //Todo hacer q no frene y espera una tecla para jugar otra partida(imprimir socre cuando termina la partida)
        restartCursor();
        return 0;
    }
}

/*
void put_bound(int length, int width){
    for(int i = 0; i< length; i++){
        
    }
}
*/

int tronOn(){
    return tronSwitch;
}

void changePlayerDirection(int player, int direction){ //solo recibira 1 o 2
    //cambio dir del jugador que corresponda
    if(player == 1 && MOD(direction - p1.direction) != 2) // para q no pueda invertir su direccion
        p1.direction = direction;
    else if(MOD(direction - p2.direction) != 2)
        p2.direction = direction;
}

void drawPlayers(){
    put_square(p1.currX*SQUARE_SIDE+1024*(p1.currY + OFFSET_Y)+ OFFSET_X,p1.currY*SQUARE_SIDE + OFFSET_Y,SQUARE_SIDE,P1_COLOR);
    put_square(p2.currX*SQUARE_SIDE+1024*(p2.currY + OFFSET_Y) + OFFSET_X,p2.currY*SQUARE_SIDE + OFFSET_Y,SQUARE_SIDE,P2_COLOR);
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

// se usa en el irq dispatcher para activar la partida mediante el espacio
void gameSwitch(int value){ //warning: control reaches end of non-void function [-Wreturn-type]
    gameOn = value;
}

// para prender tron por el kernel
void tronMotherfucker(int value){
    tronSwitch = value;
}

/*
void play(){

    //tronSwitch = 1;

    //display_menu();

    
    for(int y = 0; y < BOARD_HEIGHT; y++){
        board[y][0] = 1; // ocupado
        board[y][BOARD_WIDTH-1] = 1; //ocupado
    }
    for(int x = 0; x < BOARD_WIDTH; x++){
        board[0][x] = 1; // ocupado
        board[0][BOARD_HEIGHT-1] = 1; //ocupado
    }
    

    VideoClearScreen(); // una vez arrancada la partida limpio la pantalla
    initialize_players();
    put_square(p1.currX*SQUARE_SIDE+1024*p1.currY, p1.currY*SQUARE_SIDE, SQUARE_SIDE, P1_COLOR);
    put_square(p2.currX*SQUARE_SIDE+1024*p2.currY, p2.currY*SQUARE_SIDE, SQUARE_SIDE, P2_COLOR);
   // repite por la cantidad de matches que tengo definidos
    for(int i=0; i<MATCHES && tronSwitch; i++){
        //while(!gameOn); // no arranco hasta prendida el
        VideoClearScreen(); // una vez arrancada la partida limpio la pantalla
        initialize_players();
        //drawPlayers();
        while(gameOn){ // se juega hasta que se apague el flag
            movePlayers();
        }
    }
    
    tronSwitch = 0;
    VideoClearScreen();
    restartCursor();


}
*/