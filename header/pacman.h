#ifndef PACMAN_H
#define PACMAN_H

#include <graphics.h>

typedef struct Ghost Ghost;  // Forward declaration

typedef struct {
    int x, y;
    int radius;
    int direction;
    int lives;
} Pacman;

void drawPacman(Pacman *p);
void clearPacman(Pacman *p);
void movePacman(Pacman *p, char key);
int isColliding(Pacman *p, int newX, int newY);

int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);
void updatePacmanAfterCollision(Pacman *pacman, Ghost *ghost);

#endif
