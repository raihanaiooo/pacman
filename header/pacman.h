#ifndef PACMAN_H
#define PACMAN_H
#define PACMAN_SPEED 10
#include <graphics.h>

typedef struct {
    int x, y;
    int radius;
    int direction;
    int lives;
    int initialX, initialY;  // Posisi awal pacman
} Pacman;

typedef struct Ghost Ghost;

// Deklarasi fungsi untuk menggambar dan menghapus pacman
void drawPacman(Pacman *p);
void clearPacman(Pacman *p);
void movePacman(Pacman *p, int key, int *score);
// int isColliding(Pacman *p, int newX, int newY);

// Deklarasi fungsi untuk reset dan update pacman
void resetPacman(Pacman *p);
void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts, int *score);
int handleGameOver(Pacman *pacman, int *score, Ghost ghosts[], int numGhosts);

#endif
