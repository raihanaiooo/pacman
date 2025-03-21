#ifndef PACMAN_H
#define PACMAN_H
#define PACMAN_SPEED 5
#include <graphics.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int x, y;
    int radius;
    int direction;
    int lives;
    int initialX, initialY;  // Posisi awal pacman
} Pacman;

void drawPacman(Pacman *p);
void clearPacman(Pacman *p);
void movePacman(Pacman *p, char key, int *score);
void autoMovePacman(Pacman *p, int *score);
int isColliding(Pacman *p, int newX, int newY);

// Deklarasi resetPacman()
void resetPacman(Pacman *p);

#ifdef __cplusplus
}
#endif

#endif
