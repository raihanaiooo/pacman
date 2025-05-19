#ifndef REVALDI_H
#define REVALDI_H

#define TILE_SIZE 20 
#define ROWS 24
#define COLS 32

#include "pacman.h"

typedef struct Life {
    int x, y;               // Posisi nyawa
    struct Life *next;      // Pointer ke nyawa berikutnya
} Life;

extern Life *lives; // Pointer ke nyawa

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
// Prosedur untuk menginisiasi nyawa
void initLives();
// Fungsi untuk menggambar nyawa
void drawLives(Life *head);
// Fungsi untuk membuat nyawa baru
void addLife(Life **head, int x, int y);
// Fungsi untuk menghapus nyawa dari linked list
void removeLife(Life **head); 
// Prosdur untuk menampilkan countdown dan info powerup yang aktif
void displayPowerUpInfo();


#endif
