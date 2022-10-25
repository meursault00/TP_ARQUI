#ifndef TRON_H_
#define TRON_H_

int tronOn();
void tronMotherfucker(); //prende el tron, despues se borra

void initialize_players(); // posiciona un punto de cada jugador en pantalla
void create_board(); // define el tablero

void movePlayers(); // mueve los jugadores
void drawPlayers(); // dibuja aa los jugadores
void changePlayerDirection(int player, int direction); // cambia la direccion de los jugadores
int checkPlayersPosition(); // se fija si puede moverlos o si los mata

void gameSwitch(int value);
void moveSwitch(int value);

#endif