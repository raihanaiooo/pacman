#ifndef UI_H
#define UI_H

#define TILE_SIZE 20 
#define ROWS 24
#define COLS 32

#include "pacman.h"

// Prosedur untuk menggambar map
void Map();

// Prosedur untuk menghitung skor ~Fathi
void hitungScore(int score, int x, int y, int isWin);

// Prosedur untuk menampilkan tampilan awal
void GameStart();

// Prosedur untuk menampilkan kemenangan
void GameWin();

// Fungsi untuk menghitung dots
int countDotsAndPowerUps();

// Prosedur untuk menampilkan game over
int GameOver(int score);

// Prosedur untuk menampilkan nyawa ke layar ~Seruni
void displayLives(Pacman *pacman);

#endif
