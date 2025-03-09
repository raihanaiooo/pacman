#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>
#include "pacman.h"

#define TILE_SIZE 10
#define MAX_GHOSTS 4  // Jumlah Ghost

typedef struct {
    int x, y;
    int radius;  // Tambahkan ukuran agar sama dengan Pac-Man
    int hue;
} Ghost;

void theGhost(Ghost *gh, int x, int y, int hue);
void designGhost(Ghost *gh);
void shiftGhost(Ghost *gh);
void pursuePacman(Ghost *gh, Pacman *pac);
int GhostEatingPacman(Ghost *gh, Pacman *pac);
int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);  // Tambahkan ini!

#endif
