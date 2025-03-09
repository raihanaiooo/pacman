#include "../header/ghost.h"
#include "../header/ui.h"
#include "../header/pacman.h"
#include <stdlib.h>

// Cek dinding terbentur ghost
int GhWallHit(int x, int y) {
    if (x <= 15 || x >= 625 || y <= 15 || y >= 465) {
        return 1;  // batas luar
    }

    // Kotak-kotak dinding dalam UI
    if ((x > 50 && x < 140 && y > 55 && y < 100) ||  // Kiri atas
        (x > 185 && x < 275 && y > 55 && y < 100) || // Atas kiri
        (x > 360 && x < 450 && y > 55 && y < 100) || // Atas kanan
        (x > 505 && x < 595 && y > 55 && y < 100) || // Kanan atas
        (x > 50 && x < 140 && y > 365 && y < 410) || // Kiri bawah
        (x > 185 && x < 275 && y > 365 && y < 410) ||// Bawah kiri
        (x > 360 && x < 450 && y > 365 && y < 410) ||// Bawah kanan
        (x > 505 && x < 595 && y > 365 && y < 410) ||// Kanan bawah 
        (x > 245 && x < 395 && y > 200 && y < 280) ||// Garis tengah

        // Kotak di kiri & kanan tengah
        (x > 15 && x < 90 && y > 200 && y < 270) ||   // Kiri tengah
        (x > 550 && x < 625 && y > 200 && y < 270) || // Kanan tengah

        // Garis vertikal & horizontal utama
        (x > 295 && x < 345 && y > 15 && y < 100) ||  // Garis vertikal atas
        (x > 295 && x < 345 && y > 365 && y < 465) || // Garis vertikal bawah
        (x > 162 && x < 472 && y > 150 && y < 170) || // Garis horizontal atas
        (x > 162 && x < 472 && y > 320 && y < 340) || // Garis horizontal bawah

        // Dinding "T" Tengah 
        (x > 295 && x < 345 && y > 180 && y < 220) || // Batang vertikal atas
        (x > 295 && x < 345 && y > 260 && y < 300) || // Batang vertikal bawah
        (x > 225 && x < 275 && y > 220 && y < 260) || // Sayap kiri "T"
        (x > 365 && x < 415 && y > 220 && y < 260)) { // Sayap kanan "T"
        return 1;  // Tabrakan dengan dinding dalam
    }

    return 0;  // Gaada tabrakan
}

int GhHit(int x, int y) {
    return GhWallHit(x, y) || 
           GhWallHit(x + 10, y) ||  // Sisi kanan ghost
           GhWallHit(x - 10, y) ||  // Sisi kiri ghost
           GhWallHit(x, y + 10) ||  // Sisi bawah ghost
           GhWallHit(x, y - 10);    // Sisi atas ghost
}

void theGhost(Ghost *gh, int x, int y, int hue) {
    gh->x = x;
    gh->y = y;
    gh->hue = hue;
    
    do {
        gh->dx = (rand() % 7) - 3;  
    } while (gh->dx == 0);

    do {
        gh->dy = (rand() % 7) - 3;  
    } while (gh->dy == 0);
}

void designGhost(Ghost *gh) {
    setcolor(gh->hue);
    setfillstyle(SOLID_FILL, gh->hue);
    fillellipse(gh->x, gh->y, 15, 15);  // Kepala ghost
    rectangle(gh->x - 15, gh->y, gh->x + 15, gh->y + 20);  // Badan ghost
}

void shiftGhost(Ghost *gh, int limitX, int limitY) {
    int newX = gh->x + gh->dx;
    int newY = gh->y + gh->dy;

    if (GhWallHit(newX, newY)) {  
        do {
            gh->dx = (rand() % 7) - 3;
            gh->dy = (rand() % 7) - 3;
        } while (gh->dx == 0 && gh->dy == 0);
    } else {
        gh->x = newX;
        gh->y = newY;
    }

    if (GhHit(newX, newY)) { 
        do {
            gh->dx = (rand() % 7) - 3;
            gh->dy = (rand() % 7) - 3;
        } while (gh->dx == 0 && gh->dy == 0);
    } else {
        gh->x = newX;
        gh->y = newY;
    }
}

// Fungsi untuk mengecek tabrakan antara Pac-Man dan Ghost
int checkCollisionWithGhost(Pacman *p, Ghost *g) {
    int distance = (p->x - g->x) * (p->x - g->x) + (p->y - g->y) * (p->y - g->y);
    int collisionDistance = (p->radius + 15) * (p->radius + 15); // 15 adalah radius ghost
    return distance <= collisionDistance;
}
