#include <graphics.h>
#include "../header/pacman.h"
#include "../header/scoring.h"
#include "../header/powerup.h"
#include "../header/collision.h"
#include <stdio.h>

extern int maze[ROWS][COLS];
#define TILE_SIZE 20


/** Prosedur untuk menggambar Pacman di layar **/
void drawPacman(Pacman *p) {
    /* Menggambar Pacman */
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(p->x, p->y, p->radius, p->radius);

    /* Menggambar mulut Pacman */
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW);

    /* Menggambar mulut Pacman dengan bentuk terbuka sesuai arah pergerakannya */
    switch (p->direction) {
    case 0: pieslice(p->x, p->y, 30, 330, p->radius); break;  // Ke kanan
    case 1: pieslice(p->x, p->y, 210, 150, p->radius); break; // Ke kiri
    case 2: pieslice(p->x, p->y, 120, 60, p->radius); break;  // Ke atas
    case 3: pieslice(p->x, p->y, 300, 240, p->radius); break; // Ke bawah
    }
}

/** Prosedur untuk menghapus gambar Pacman dari layar **/
void clearPacman(Pacman *p) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(p->x, p->y, p->radius, p->radius);
}

/** Prosedur untuk menggerakkan Pacman **/
void movePacman(Pacman *p, int key, int *score) {
    /* Jika ada input dari pemain, ubah arah Pac-Man */
    if (key == 75 || key == 77 || key == 72 || key == 80) {
        switch (key) {
            case 75: p->direction = 1; break; // Kiri
            case 77: p->direction = 0; break; // Kanan
            case 72: p->direction = 2; break; // Atas
            case 80: p->direction = 3; break; // Bawah
        }
    }

    /* Lanjutkan gerakan otomatis berdasarkan arah terakhir */
    int newX = p->x;
    int newY = p->y;

    /* Menyesuaikan koordinat Pacman berdasarkan arah gerakannya */    
    switch (p->direction) {
        case 1: newX -= PACMAN_SPEED; break; // Kiri
        case 0: newX += PACMAN_SPEED; break; // Kanan
        case 2: newY -= PACMAN_SPEED; break; // Atas
        case 3: newY += PACMAN_SPEED; break; // Bawah
    }

    /* Teleportasi (hanya dilakukan setelah update newX) */
    if (newX < 0) {
        printf("Teleport ke kanan!\n");
        newX = TILE_SIZE * (COLS - 1);
    } else if (newX >= TILE_SIZE * (COLS - 1)) {
        newX = 0;
        printf("Teleport ke kiri!\n");
    }

    /* Mengecek apakah pergerakan ke koordinat baru menyebabkan tabrakan dengan dinding */
    if (!isColliding(newX, newY, p->radius, p->direction)) {
        /* Jika tidak ada tabrakan, gerakkan Pacman ke koordinat baru */
        clearPacman(p);
        p->x = newX;
        p->y = newY;
        drawPacman(p);
        scoring(p->x, p->y, score);
        checkPowerUpCollision(p->x, p->y);
    }
}


