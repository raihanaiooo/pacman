#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>
#include "pacman.h"

#define TILE_SIZE 20
#define MAX_GHOSTS 4  // Jumlah Ghost

typedef struct Ghost {
    int x, y;
    int initialX, initialY;  // Posisi awal ghost
    int radius;              // Sama dengan ukuran Pac-Man
    int hue;                 // Warna Ghost
} Ghost;

void theGhost(Ghost *gh, int x, int y, int hue);
void designGhost(Ghost *gh);
void shiftGhost(Ghost *gh);
void moveGhost(Ghost *gh, Pacman *pac);  // Tambahkan AI Ghost
void chasePacman(Ghost *gh, Pacman *pac);
void runAwayFromPacman(Ghost *gh, Pacman *pac);
void ambushPacman(Ghost *gh, Pacman *pac);
int isColliding(Ghost *gh, int newX, int newY);
int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);

// Fungsi baru untuk reset ghost ke posisi awal
void resetGhost(Ghost *gh);

#endif
