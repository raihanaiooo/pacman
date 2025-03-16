#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>
#include "pacman.h"

typedef struct Pacman Pacman;  // Forward declaration

#ifndef TILE_SIZE
#define TILE_SIZE 8  
#endif

#define MAX_GHOSTS 4  

typedef struct {
    int x, y;
    int radius;
    int hue;
} Ghost;

void theGhost(Ghost *gh, int x, int y, int hue);
void designGhost(Ghost *gh);
void shiftGhost(Ghost *gh);
void pursuePacman(Ghost *gh, Pacman *pac);
int GhostEatingPacman(Ghost *gh, Pacman *pac);
int isColliding(Ghost *gh, int newX, int newY);
int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);

#endif
