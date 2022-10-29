


#include <keyboardPiano.h>
#include <system_calls.h>
static int playingPiano = 0;


enum chcordFreq{
    C	 =	262,
    Db  =	277,
    D	 =	294,
    Eb  =  311,
    E	 =	330,
    F	 =	349,
    Gb  =	370,
    G	 =	392,
    Ab =	415,
    A	 =	440,
    Bb  =	466,
    B	 =	494
};
#define MAXCHORDS 50
//
static int keyChordMap[MAXCHORDS][2] ={
    { '1',Db/2}, 
    { '2',Eb/2},
    { '3',Gb/2},
    { '4',Ab/2}, 
    { '5',Bb/2}, 
    { '6',Db/2},
    { '7',Eb/2},
    { '8',Gb/4}, 
    { '9',Ab/4}, 
//desde aca
    { 'q',D/2 },
    { 'w',Db }, 
    { 'e',Eb }, 
    { 'r',G/2 },
    { 't',Gb },
    { 'y',Ab }, 
    { 'u',Bb }, 
    { 'i',D/2 },
    { 'o',Db*2 },
    { 'p',Eb*2 }, 
     
    { 'a',C }, 
    { 's',D },
    { 'd',E },
    { 'f',F }, 
    { 'g',G }, 
    { 'h',A },
    { 'j',B },
    { 'k',C*2 }, 
    { 'l',D*2 }, 
    { ';',E*2 },
//hasta aca 
    { 'z',G*4 },
    { 'x',A*4 }, 
    { 'c',B*4 }, 
    { 'v',C*4 },
    { 'b',D*4 },
    { 'n',E*4 }, 
    { 'm',F*4 }, 
    { ',',G*4*2 },
    { '.',A*4*2 },
    { '/',B*4*2 }
};
     
    


void playPiano(){
    drawSomething();
    playingPiano = 1;

    while(playingPiano){
        pianoKeyboardHandler();
    }
}

void pianoKeyboardHandler(){
    int aux = getchar();
    if(aux != -1){
        if(aux == ' '){
            playingPiano = 0;
        }
        else{
            playSound(aux);
        }
    }
}

void playSound(int key){   
    for(int i = 0; i < MAXCHORDS; i++){
        if(keyChordMap[i][0] == key){
            beep(keyChordMap[i][1], 1);
            break;
        }
    }

}
void drawSomething(){
    int color =0xFFFFFF;
    int tam = 3;
    for(int i = 300; i < 500; i++){
        putSquare(200-50, i, tam, color);
        putSquare(300-50, i, tam, color);
        putSquare(400-50, i, tam, color);
        putSquare(500-50, i, tam, color);
        putSquare(600-50, i, tam, color);
        putSquare(700-50, i, tam, color);
        putSquare(800-50, i, tam, color);
        putSquare(900-50, i, tam, color);
    }

}

//function to draw a line
void drawLine(int x, int y, int size, int color){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            putSquare(x+i, y+j, 3, color);
        }
    }
}
