#ifndef SCORING_H
#define SCORING_H

#include <graphics.h>
// Konstanta untuk dot
#define DOT_RADIUS 3
#define ROWS 24
#define COLS 32
#define DOT_SPACING 40

// Struktur untuk menyimpan status titik yang bisa dimakan
// extern int dots[ROWS][COLS];
typedef struct Dot {
  int x, y;
  struct Dot* next;
} Dot;

extern Dot* dotHead;
// Fungsi untuk menggambar dot dan mengecek collision
void setTitikDot();
void gambarDot();
void scoring(int pacmanX, int pacmanY, int *score);
void freeDot();


#endif
