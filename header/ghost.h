#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>
#include "pacman.h"  // Tambahkan ini supaya tahu struct Pacman

typedef struct {
    int x, y;
    int hue;    // color
    int dx, dy;
} Ghost;

void theGhost(Ghost *gh, int x, int y, int hue);
void designGhost(Ghost *gh);
void shiftGhost(Ghost *gh, int limitX, int limitY);
int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);  // Tambahkan ini!

#endif
