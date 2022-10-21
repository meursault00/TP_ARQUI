#include <video_driver.h>

static int tronSwitch = 0;

#define SQUARE_SIDE 4

#define BOARD_HEIGHT 1000
#define BOARD_WIDTH 744

#define P1_STARTING_X 500
#define P1_STARTING_Y 200
#define P2_STARTING_X 500
#define P2_STARTING_Y 600

#define P1_COLOR 0x0000FF
#define P2_COLOR 0xFF0000

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

#define INSIDE_BOARD(x,y) x >= 0

static const mover[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
static int board[BOARD_WIDTH][BOARD_HEIGHT] = {0};

typedef struct player_t{
    int color;
    int currX,currY;
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

void play(){
    display_menu();

    for(int y = 0; y < BOARD_HEIGHT; y++){
        board[y][0] = 1; // ocupado
        board[y][BOARD_WIDTH-1] = 1; //ocupado
    }
    for(int x = 0; x < BOARD_WIDTH; x++){
        board[0][x] = 1; // ocupado
        board[0][BOARD_HEIGHT-1] = 1; //ocupado
    }
    
    put_bound();

    tronSwitch = 1;

    tronSwitch = 0;
}


void put_bound(int length, int width){
    for(int i = 0; i< length; i++){
        
        
    }
}

int tronOn(){
    return tronSwitch;
}

void changePlayerDirection(int player, int direction){
    if(player == 1)
        p1.direction = direction;
    else
        p2.direction = direction;
}

void movePlayers(){
    p1.currX += mover[p1.direction][1];
    p1.currY += mover[p1.direction][2];
    p2.currX += mover[p2.direction][1];
    p2.currY += mover[p2.direction][2];

    if(!checkPlayerPositions()){
        board[p1.currX][p1.currY] = 1;
        board[p2.currX][p2.currY] = 1;
    }
}

/**
@param player tiene current position en X e Y
@returns boolean 1 si algun jugador ha muerto
*/
int checkPlayerPositions(){
    if(board[p1.currX][p1.currY] ||  ){
        p1.alive =0;
    }
    if(board[p2.currX][p2.currY]){
        p2.alive =0;
    }
    return p1.alive && p2.alive;
}