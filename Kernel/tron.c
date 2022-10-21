#include <video_driver.h>

static int tronSwitch = 0;
static int gameOn = 0;

#define MATCHES 1

#define SQUARE_SIDE 8

#define BOARD_WIDTH 125
#define BOARD_HEIGTH 93

#define P1_STARTING_X 63
#define P1_STARTING_Y 20
#define P2_STARTING_X 63
#define P2_STARTING_Y 65

#define P1_COLOR 0x0000FF
#define P2_COLOR 0xFF0000

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

static int mover[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
static int board[1000][744] = {0};

typedef struct player_t{
    int color;
    int currX;
    int currY;
    int alive;
    int direction;
    int score;    
} player_t;

static player_t p1,p2;


void display_menu(){
    // escribir intro al juego
    
}

static void initialize_players(){
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
}

static int insideBoard(int x, int y){
    return (x >= 0) && (x <= BOARD_WIDTH) && (y >= 0) && (y <= BOARD_HEIGTH);
}

/**
@param player tiene current position en X e Y
@returns boolean 0 si algun jugador ha muerto
*/
int checkPlayersPosition(){
    if(!insideBoard(p1.currX,p1.currY || board[p1.currX][p1.currY])){
        p1.alive =0;
    }
    if(!insideBoard(p2.currX,p2.currY) || board[p2.currX][p2.currY]){
        p2.alive =0;
    }
    if(p1.alive && p2.alive)
        return 1;
    else{
        if(p1.alive)
            p1.score++;
        else if(p2.alive)
            p2.score++;
        gameOn = 0; 
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

void changePlayerDirection(int player, int direction){
    if(player == 1)
        p1.direction = direction;
    else
        p2.direction = direction;
}

//retorna 1 mientras sigan vivos
void movePlayers(){
    p1.currX += mover[p1.direction][1];
    p1.currY += mover[p1.direction][2];
    p2.currX += mover[p2.direction][1];
    p2.currY += mover[p2.direction][2];

    if(checkPlayersPosition()){
        board[p1.currX][p1.currY] = 1;
        board[p2.currX][p2.currY] = 1;
        put_square(p1.currX*SQUARE_SIDE+1024*p1.currY,p1.currY*SQUARE_SIDE,SQUARE_SIDE,P1_COLOR);
        put_square(p2.currX*SQUARE_SIDE+1024*p2.currY,p2.currY*SQUARE_SIDE,SQUARE_SIDE,P2_COLOR);
    }
}

int gameSwitch(int value){
    gameOn = value;
}

void tronMotherfucker(){
    tronSwitch = 1;
}

/*
void drawPlayers(){
    put_square(p1.currX*SQUARE_SIDE+1024*p1.currY,p1.currY*SQUARE_SIDE,SQUARE_SIDE,P1_COLOR);
    put_square(p2.currX*SQUARE_SIDE+1024*p2.currY,p2.currY*SQUARE_SIDE,SQUARE_SIDE,P2_COLOR);
}
*/

void play(){

    //tronSwitch = 1;

    //display_menu();

    /*
    for(int y = 0; y < BOARD_HEIGHT; y++){
        board[y][0] = 1; // ocupado
        board[y][BOARD_WIDTH-1] = 1; //ocupado
    }
    for(int x = 0; x < BOARD_WIDTH; x++){
        board[0][x] = 1; // ocupado
        board[0][BOARD_HEIGHT-1] = 1; //ocupado
    }
    */
    for(int i=0; i<MATCHES; i++){
        while(!gameOn)
        VideoClearScreen();
        initialize_players();
        drawPlayers();
        while(gameOn);
    }
    while(1); // para testing
    VideoClearScreen();

    tronSwitch = 0;

}

int isGameOn(){
    return gameOn;
}