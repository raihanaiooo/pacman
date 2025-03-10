#include "../header/ghost.h"
#include "../header/ui.h"
#include "../header/pacman.h"
#include <stdlib.h>

extern int maze[24][32];

void theGhost(Ghost *gh, int x, int y, int hue) {
    gh->x = x;
    gh->y = y;
    gh->radius = 8; // Sama dengan Pac-Man
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

int isColliding(Ghost *gh, int newX, int newY) {
    int col = newX / TILE_SIZE;
    int row = newY / TILE_SIZE;

    // Cek apakah keluar dari batas array
    if (row < 0 || row >= 24 || col < 0 || col >= 32) {
        return 1;  // Jika di luar batas, anggap tabrakan
    }

    // Cek apakah lokasi baru adalah dinding (2)
    return (maze[row][col] == 2);
}

void shiftGhost(Ghost *gh) {
    int row = gh->y / TILE_SIZE;
    int col = gh->x / TILE_SIZE;

    int possibleDirections[4][2];  // Menyimpan arah yang mungkin
    int directionCount = 0;

    // Cek 4 arah dan tambahkan ke array jika tidak ada tabrakan
    if (row > 0 && !isColliding(gh, gh->x, gh->y - TILE_SIZE)) {  // Atas
        possibleDirections[directionCount][0] = -1;
        possibleDirections[directionCount][1] = 0;
        directionCount++;
    }
    if (row < 23 && !isColliding(gh, gh->x, gh->y + TILE_SIZE)) {  // Bawah
        possibleDirections[directionCount][0] = 1;
        possibleDirections[directionCount][1] = 0;
        directionCount++;
    }
    if (col > 0 && !isColliding(gh, gh->x - TILE_SIZE, gh->y)) {  // Kiri
        possibleDirections[directionCount][0] = 0;
        possibleDirections[directionCount][1] = -1;
        directionCount++;
    }
    if (col < 31 && !isColliding(gh, gh->x + TILE_SIZE, gh->y)) {  // Kanan
        possibleDirections[directionCount][0] = 0;
        possibleDirections[directionCount][1] = 1;
        directionCount++;
    }

    // Jika ada arah yang valid, pilih salah satu secara random
    if (directionCount > 0) {
        int randomIndex = rand() % directionCount;
        int newRow = row + possibleDirections[randomIndex][0];
        int newCol = col + possibleDirections[randomIndex][1];

        // Pastikan Ghost tetap berada di jalur
        if (!isColliding(gh, newCol * TILE_SIZE, newRow * TILE_SIZE)) {
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


}

// Fungsi untuk mengecek tabrakan antara Pac-Man dan Ghost
int checkCollisionWithGhost(Pacman *p, Ghost *g) {
    int distance = (p->x - g->x) * (p->x - g->x) + (p->y - g->y) * (p->y - g->y);
    int collisionDistance = (p->radius + 15) * (p->radius + 15); // 15 adalah radius ghost
    return distance <= collisionDistance;
}
