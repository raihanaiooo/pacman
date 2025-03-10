#include "../header/ghost.h"
#include "../header/ui.h"
#include "../header/pacman.h"
#include <stdlib.h>

extern int maze[24][32];

void theGhost(Ghost *gh, int x, int y, int hue) {
    gh->x = x;
    gh->y = y;
    gh->radius = 10; // Sama dengan Pac-Man
    gh->hue = hue;
}

// Cek apakah ghost memakan pacman
int GhostEatingPacman(Ghost *gh, Pacman *pac) {
    int dx = gh->x - pac->x;
    int dy = gh->y - pac->y;
    int distance = dx * dx + dy * dy;
    int minDistance = (gh->radius + pac->radius) * (gh->radius + pac->radius);

    return (distance < minDistance);
}

void shiftGhost(Ghost *gh) {
    int row = gh->y / TILE_SIZE;
    int col = gh->x / TILE_SIZE;

    int possibleDirections[4][2];  // Menyimpan arah yang mungkin
    int directionCount = 0;

    // Mengecek arah 
        if (row > 0 && maze[row - 1][col] == 0) {  // Atas
        possibleDirections[directionCount][0] = -1;
        possibleDirections[directionCount][1] = 0;
        directionCount++;
    }
    if (row < 23 && maze[row + 1][col] == 0) {  // Bawah
        possibleDirections[directionCount][0] = 1;
        possibleDirections[directionCount][1] = 0;
        directionCount++;
    }
    if (col > 0 && maze[row][col - 1] == 0) {  // Kiri
        possibleDirections[directionCount][0] = 0;
        possibleDirections[directionCount][1] = -1;
        directionCount++;
    }
    if (col < 31 && maze[row][col + 1] == 0) {  // Kanan
        possibleDirections[directionCount][0] = 0;
        possibleDirections[directionCount][1] = 1;
        directionCount++;
    }

    // Jika ada arah yang valid, memilih salah satu secara random
    if (directionCount > 0) {
        int randomIndex = rand() % directionCount;
        int newRow = row + possibleDirections[randomIndex][0];
        int newCol = col + possibleDirections[randomIndex][1];

        // Memastikan arah baru masih berada di dalam jalan
        if (maze[newRow][newCol] == 0) {
            gh->x = newCol * TILE_SIZE;
            gh->y = newRow * TILE_SIZE;
        }
    }
}

void pursuePacman(Ghost *gh, Pacman *pac) {
    int rowG = gh->y / TILE_SIZE;
    int colG = gh->x / TILE_SIZE;
    int rowP = pac->y / TILE_SIZE;
    int colP = pac->x / TILE_SIZE;

    if (rowG < rowP && maze[rowG + 1][colG] == 0) gh->y += TILE_SIZE;
    else if (rowG > rowP && maze[rowG - 1][colG] == 0) gh->y -= TILE_SIZE;
    else if (colG < colP && maze[rowG][colG + 1] == 0) gh->x += TILE_SIZE;
    else if (colG > colP && maze[rowG][colG - 1] == 0) gh->x -= TILE_SIZE;
}

void designGhost(Ghost *gh) {
    int x = gh->x;
    int y = gh->y;

    setcolor(gh->hue);
    setfillstyle(SOLID_FILL, gh->hue);
    fillellipse(x, y, gh->radius, gh->radius);  // Setengah lingkaran

    for (int i = -10; i <=10; i += 5) {
        int spikeY = y + gh->radius;
        fillellipse(x + i, spikeY, 2, 3);
    }

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x - 4, y - 5, 2, 2);
    fillellipse(x + 4, y - 5, 2, 2);

    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x - 4, y - 5, 1, 1);
    fillellipse(x + 4, y - 5, 1, 1);

    // if (GhHit(newX, newY)) { 
    //     do {
    //         gh->dx = (rand() % 7) - 3;
    //         gh->dy = (rand() % 7) - 3;
    //     } while (gh->dx == 0 && gh->dy == 0);
    // } else {
    //     gh->x = newX;
    //     gh->y = newY;
    // }
}

// Fungsi untuk mengecek tabrakan antara Pac-Man dan Ghost
int checkCollisionWithGhost(Pacman *p, Ghost *g) {
    int distance = (p->x - g->x) * (p->x - g->x) + (p->y - g->y) * (p->y - g->y);
    int collisionDistance = (p->radius + 15) * (p->radius + 15); // 15 adalah radius ghost
    return distance <= collisionDistance;
}
