#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>
#include "pacman.h"

#define TILE_SIZE 20
#define MAX_GHOSTS 4  // Jumlah Ghost

typedef struct {
    int x, y;
    int radius;  // Sama dengan ukuran Pac-Man
    int hue;     // Warna Ghost
} Ghost;

void theGhost(Ghost *gh, int x, int y, int hue);
void designGhost(Ghost *gh);
void shiftGhost(Ghost *gh);
void moveGhost(Ghost *gh, Pacman *pac);  // Tambahkan AI Ghost
void chasePacman(Ghost *gh, Pacman *pac);
void runAwayFromPacman(Ghost *gh, Pacman *pac);
void ambushPacman(Ghost *gh, Pacman *pac);
int isColliding(Ghost *gh, int newX, int newY);
int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);  // Untuk deteksi tabrakan

// //! by sasa
// moveBlinky(Ghost *gh, Pacman *pac); //* Ngejar pacman
// movePinky(Ghost *gh, Pacman *pac); //* Memprediksi posisi Pac-Man ke depan beberapa langkah.
// moveInky(Ghost *gh, Pacman *pac); //* Menggunakan strategi lebih kompleks, bisa dengan random atau kalkulasi tertentu.
// moveClyde(Ghost *gh, Pacman *pac); //* Bergerak acak, tapi menjauhi Pac-Man jika terlalu dekat. 

#endif
