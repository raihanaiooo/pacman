#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
#include "pacman.h"

#define TILE_SIZE 20
#define MAX_GHOSTS 4  // Jumlah Ghost

#define MAX_ROW 24
#define MAX_COL 32

typedef struct {
    int row, col;  // Posisi dalam grid maze
} Node;

typedef struct Ghost {
    int x, y;
    int initialX, initialY;  // Posisi 
    int radius;              // Ukuran
    int hue;                 // Warna Ghost
    int lastDirX, lastDirY;
    int stepCounter;
} Ghost;

typedef struct GhostNode {
    Ghost ghost;
    int lifetime;
    int color;
    int isScared;         // True jika ghost dalam mode takut
    int scaredTimer;      // Waktu sisa untuk takut
    struct GhostNode* next;
} GhostNode;
;

extern int maze[24][32];

void designGhost(Ghost* gh, int isScared, int scaredTimer); // Pengaturan bentuk dan warna Ghost
void drawGhostWithEffect(GhostNode *node);
void addGhost(GhostNode** head, int x, int y, int color);
void updateGhosts(GhostNode** head);
void drawGhosts(GhostNode* head);
void moveGhost(Ghost *gh, Pacman *pac);                     // Case karakteristik setiap Ghost
void shiftGhost(Ghost *gh);                                 // Karakteristik gerakan acak
void pursuePacman(Ghost *gh, Pacman *pac);                  // Karakteristik mengejar
void escapePacman(Ghost *gh, Pacman *pac);                  // Karakteristik menjauh (Teknik Ancaman)
void blockPacman(Ghost *gh, Pacman *pac);                   // Karakteristik memotong jalur
//void resetGhost(Ghost *gh); (dipindahin ke pacman.h)                             // Posisi Reset
int isColliding(Ghost *gh, int newX, int newY);             // Cek tabrakan dengan dinding
int CollisionWithGhost(Pacman *pacman, GhostNode *node);       // Cek tabrakan dengan Pacman

#endif