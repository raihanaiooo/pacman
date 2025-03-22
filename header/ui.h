#ifndef UI_H
#define UI_H

#define TILE_SIZE 20 

#include "pacman.h"

void Map();

void hitungScore(int score, int x, int y, int isWin);

void GameStart();

// void GameOver();

void GameWin();

void checkWin();

int countDotsAndPowerUps();

// void GamePause();

// Menampilkan jumlah nyawa Pac-Man di layar
void displayLives(Pacman *pacman);

#endif
