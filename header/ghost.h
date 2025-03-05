#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>

typedef struct {
    int x, y;
    int hue;    // color
    int dx, dy;
} Ghost;

void theGhost(Ghost *gh, int x, int y, int hue);
void designGhost(Ghost *gh);
void shiftGhost(Ghost *gh, int limitX, int limitY);

#endif
