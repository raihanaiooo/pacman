#ifndef PACMAN_H
#define PACMAN_H
#define PACMAN_SPEED 10
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

// Forward declaration untuk tipe Ghost
typedef struct Ghost Ghost;

void drawPacman(Pacman *p);
void clearPacman(Pacman *p);
void movePacman(Pacman *p, char key, int *score);
void autoMovePacman(Pacman *p, int *score);
int isColliding(Pacman *p, int newX, int newY);

// Deklarasi fungsi untuk reset dan update pacman
void resetPacman(Pacman *p);
void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts, int *score);
#ifdef __cplusplus
}
#endif

#endif
