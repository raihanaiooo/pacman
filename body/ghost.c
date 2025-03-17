#include "../header/ghost.h"
#include "../header/ui.h"
#include "../header/pacman.h"
#include <stdlib.h>

extern int maze[24][32];

void theGhost(Ghost *gh, int x, int y, int hue) {
    gh->x = x;
    gh->y = y;
    gh->hue = hue;
    gh->radius = 8;
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

void moveGhost(Ghost *gh, Pacman *pac) {
    switch (gh->hue) {
        case RED:  // Blinky (Merah) - Mengejar Pac-Man
            chasePacman(gh, pac);
            break;
        case WHITE:  // Pinky (Pink) - Memotong jalur Pac-Man
            ambushPacman(gh, pac);
            break;
        case GREEN:  // Inky (Biru) - Bergerak acak tapi tetap di jalur
            shiftGhost(gh);
            break;
        case CYAN:  // Clyde (Oranye) - Menjauh jika terlalu dekat dengan Pac-Man
            runAwayFromPacman(gh, pac);
            break;
        default:
            shiftGhost(gh);  // Default ke pergerakan acak
            break;
    }
}

void shiftGhost(Ghost *gh) {
    int row = gh->y / TILE_SIZE;
    int col = gh->x / TILE_SIZE;

    int possibleDirections[4][2];
    int directionCount = 0;

    // Cek 4 arah yang bisa ditempuh (tidak menabrak dinding)
    if (!isColliding(gh, gh->x, gh->y - TILE_SIZE)) { // Atas
        possibleDirections[directionCount][0] = -1;
        possibleDirections[directionCount][1] = 0;
        directionCount++;
    }
    if (!isColliding(gh, gh->x, gh->y + TILE_SIZE)) { // Bawah
        possibleDirections[directionCount][0] = 1;
        possibleDirections[directionCount][1] = 0;
        directionCount++;
    }
    if (!isColliding(gh, gh->x - TILE_SIZE, gh->y)) { // Kiri
        possibleDirections[directionCount][0] = 0;
        possibleDirections[directionCount][1] = -1;
        directionCount++;
    }
    if (!isColliding(gh, gh->x + TILE_SIZE, gh->y)) { // Kanan
        possibleDirections[directionCount][0] = 0;
        possibleDirections[directionCount][1] = 1;
        directionCount++;
    }

    // Jika tidak ada arah yang valid, tetap diam
    if (directionCount == 0) {
        printf("Ghost terjebak!\n");
        return;
    }

    // Jika ada arah yang valid, pilih secara random
    int randomIndex = rand() % directionCount;
    int newRow = row + possibleDirections[randomIndex][0];
    int newCol = col + possibleDirections[randomIndex][1];

    // Pastikan Ghost tetap di jalur
    if (!isColliding(gh, newCol * TILE_SIZE, newRow * TILE_SIZE)) {
        gh->x = newCol * TILE_SIZE;
        gh->y = newRow * TILE_SIZE;
    }
}

void chasePacman(Ghost *gh, Pacman *pac) {
    int rowG = gh->y / TILE_SIZE;
    int colG = gh->x / TILE_SIZE;
    int rowP = pac->y / TILE_SIZE;
    int colP = pac->x / TILE_SIZE;

    if (rowG < rowP && !isColliding(gh, gh->x, gh->y + TILE_SIZE)) gh->y += TILE_SIZE;
    else if (rowG > rowP && !isColliding(gh, gh->x, gh->y - TILE_SIZE)) gh->y -= TILE_SIZE;
    else if (colG < colP && !isColliding(gh, gh->x + TILE_SIZE, gh->y)) gh->x += TILE_SIZE;
    else if (colG > colP && !isColliding(gh, gh->x - TILE_SIZE, gh->y)) gh->x -= TILE_SIZE;
}

void runAwayFromPacman(Ghost *gh, Pacman *pac) {
    int rowG = gh->y / TILE_SIZE;
    int colG = gh->x / TILE_SIZE;
    int rowP = pac->y / TILE_SIZE;
    int colP = pac->x / TILE_SIZE;

    if (rowG < rowP && !isColliding(gh, gh->x, gh->y - TILE_SIZE)) gh->y -= TILE_SIZE;
    else if (rowG > rowP && !isColliding(gh, gh->x, gh->y + TILE_SIZE)) gh->y += TILE_SIZE;
    else if (colG < colP && !isColliding(gh, gh->x - TILE_SIZE, gh->y)) gh->x -= TILE_SIZE;
    else if (colG > colP && !isColliding(gh, gh->x + TILE_SIZE, gh->y)) gh->x += TILE_SIZE;
}

void ambushPacman(Ghost *gh, Pacman *pac) {
    int rowP = pac->y / TILE_SIZE;
    int colP = pac->x / TILE_SIZE;
    int targetRow = rowP;
    int targetCol = colP;

    // Prediksi posisi Pac-Man ke depan 4 tile berdasarkan arahnya
    switch (pac->direction) {
        case 0: targetCol += 4; break; // Kanan
        case 1: targetCol -= 4; break; // Kiri
        case 2: targetRow -= 4; break; // Atas
        case 3: targetRow += 4; break; // Bawah
    }

    // Pastikan targetRow dan targetCol tidak keluar dari batas peta
    if (targetRow < 0) targetRow = 0;
    if (targetRow >= 24) targetRow = 23;
    if (targetCol < 0) targetCol = 0;
    if (targetCol >= 32) targetCol = 31;

    // Gerakkan Ghost menuju posisi prediksi
    int rowG = gh->y / TILE_SIZE;
    int colG = gh->x / TILE_SIZE;

    if (rowG < targetRow && !isColliding(gh, gh->x, gh->y + TILE_SIZE)) gh->y += TILE_SIZE;
    else if (rowG > targetRow && !isColliding(gh, gh->x, gh->y - TILE_SIZE)) gh->y -= TILE_SIZE;
    else if (colG < targetCol && !isColliding(gh, gh->x + TILE_SIZE, gh->y)) gh->x += TILE_SIZE;
    else if (colG > targetCol && !isColliding(gh, gh->x - TILE_SIZE, gh->y)) gh->x -= TILE_SIZE;
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
    int dx = p->x - g->x;
    int dy = p->y - g->y;
    int distanceSquared = dx * dx + dy * dy;
    int collisionDistance = (p->radius + g->radius) * (p->radius + g->radius);

    return (distanceSquared <= collisionDistance);  // True jika tabrakan
}


