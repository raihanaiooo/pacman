#ifndef PACMAN_H
#define PACMAN_H
#define PACMAN_SPEED 5
#include <graphics.h>

typedef struct {
    int x, y;
    int radius;
    int direction;
    int lives;
} Pacman;

void drawPacman(Pacman *p);

void clearPacman(Pacman *p);

void movePacman(Pacman *p, char key, int *score);

void autoMovePacman(Pacman *p, int *score); // tambahan FATHI

int isColliding(Pacman *p, int newX, int newY);

#endif
