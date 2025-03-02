#ifndef PACMAN_H
#define PACMAN_H
#include <graphics.h>

typedef struct {
    int x, y;
    int radius;
    int direction;
} Pacman;

void drawPacman(Pacman *p);

void clearPacman(Pacman *p);

void movePacman(Pacman *p, char key);

int isColliding(Pacman *p, int newX, int newY);

#endif