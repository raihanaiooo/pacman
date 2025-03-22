#include <graphics.h>
#include "../header/pacman.h"
#include "../header/scoring.h"
#include "../header/powerup.h"
#include <stdio.h>

extern int maze[24][32];
#define TILE_SIZE 20

int isColliding(Pacman *p, int newX, int newY) {
    int checkX = newX;
    int checkY = newY;

    switch (p->direction) {
    case 0: checkX += p->radius; break;
    case 1: checkX -= p->radius; break;
    case 2: checkY -= p->radius; break;
    case 3: checkY += p->radius; break;
    }
    int col = checkX / TILE_SIZE;
    int row = checkY / TILE_SIZE;

    if (row < 0 || row >= 25 || col < 0 || col >= 32) {
        return 1;
    }
    return (maze[row][col] == 2);
}

void drawPacman(Pacman *p) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(p->x, p->y, p->radius, p->radius);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW);
    switch (p->direction) {
    case 0: pieslice(p->x, p->y, 30, 330, p->radius); break;
    case 1: pieslice(p->x, p->y, 210, 150, p->radius); break;
    case 2: pieslice(p->x, p->y, 120, 60, p->radius); break;
    case 3: pieslice(p->x, p->y, 300, 240, p->radius); break;
    }
}

void clearPacman(Pacman *p) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(p->x, p->y, p->radius, p->radius);
}

void movePacman(Pacman *p, int key, int *score) {
    // Jika ada input dari pemain, ubah arah Pac-Man
    if (key == 75 || key == 77 || key == 72 || key == 80) {
        switch (key) {
            case 75: p->direction = 1; break; // Kiri
            case 77: p->direction = 0; break; // Kanan
            case 72: p->direction = 2; break; // Atas
            case 80: p->direction = 3; break; // Bawah
        }
    }

    // Lanjutkan gerakan otomatis berdasarkan arah terakhir
    int newX = p->x;
    int newY = p->y;

    switch (p->direction) {
        case 1: newX -= PACMAN_SPEED; break; // Kiri
        case 0: newX += PACMAN_SPEED; break; // Kanan
        case 2: newY -= PACMAN_SPEED; break; // Atas
        case 3: newY += PACMAN_SPEED; break; // Bawah
    }

    // Jika tidak bertabrakan, lakukan pergerakan
    if (!isColliding(p, newX, newY)) {
        clearPacman(p);
        p->x = newX;
        p->y = newY;
        drawPacman(p);
        scoring(p->x, p->y, score);
        checkPowerUpCollision(p->x, p->y);
    }
}


