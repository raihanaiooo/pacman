#ifndef SCORING_H
#define SCORING_H

#include <graphics.h>

// Konstanta untuk dot
#define DOT_RADIUS 3
#define ROWS 10
#define COLS 15
#define DOT_SPACING 40

// Struktur untuk menyimpan status titik yang bisa dimakan
extern int dots[ROWS][COLS];

// Fungsi untuk menggambar dot dan mengecek collision
void initializeDots();
void drawDots();
void checkCollisionWithDots(int pacmanX, int pacmanY, int *score);

#endif
