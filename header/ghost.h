#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
#include "pacman.h"

#define TILE_SIZE 20
#define MAX_GHOSTS 4  // Jumlah Ghost

#define MAX_ROW 24
#define MAX_COL 32

typedef struct {
    int row, col;  // Posisi dalam grid maze
} Node;

typedef struct Ghost {
    int x, y;
    int initialX, initialY;  // Posisi 
    int radius;              // Ukuran
    int hue;                 // Warna Ghost
    int lastDirX, lastDirY;
} Ghost;

extern int maze[24][32];

<<<<<<< HEAD
// Fungsi baru untuk reset ghost ke posisi awal
void resetGhost(Ghost *gh);
void pursuePacman(Ghost *gh, Pacman *pac);
=======
void theGhost(Ghost *gh, int x, int y, int hue);            // Inisialisasi Ghost
void designGhost(Ghost *gh);                                // Pengaturan bentuk dan warna Ghost
void moveGhost(Ghost *gh, Pacman *pac);                     // Case karakteristik setiap Ghost
void shiftGhost(Ghost *gh);                                 // Karakteristik gerakan acak
void pursuePacman(Ghost *gh, Pacman *pac);                  // Karakteristik mengejar
void escapePacman(Ghost *gh, Pacman *pac);                  // Karakteristik menjauh (Teknik Ancaman)
void blockPacman(Ghost *gh, Pacman *pac);                   // Karakteristik memotong jalur
void resetGhost(Ghost *gh);                                 // Posisi Reset
int isColliding(Ghost *gh, int newX, int newY);             // Cek tabrakan dengan dinding
int CollisionWithGhost(Pacman *pacman, Ghost *ghost);       // Cek tabrakan dengan Pacman

>>>>>>> 88329a7a5152076af8848543a23b62e2b0bd0292
#endif
