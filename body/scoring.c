#include <graphics.h>
#include "../header/scoring.h"
#include <stdio.h>

// Array untuk menyimpan status titik (1 = ada, 0 = dimakan atau tidak tersedia)
int dots[ROWS][COLS];

// Fungsi untuk mengecek apakah titik berada di area terlarang (map UI)
int isInsideObstacle(int x, int y) {
    // Daftar area UI (sesuaikan dengan map di ui.c)
    if ((x > 15 && x < 625 && (y < 30 || y > 450)) ||  // Batas atas & bawah
        (x > 295 && x < 345 && y > 15 && y < 100) ||   // Tengah atas
        (x > 295 && x < 345 && y > 380 && y < 465) ||  // Tengah bawah
        (x > 50 && x < 140 && y > 55 && y < 100) ||    // Kiri atas
        (x > 505 && x < 595 && y > 55 && y < 100) ||   // Kanan atas
        (x > 50 && x < 140 && y > 365 && y < 410) ||   // Kiri bawah
        (x > 505 && x < 595 && y > 365 && y < 410)) {  // Kanan bawah
        return 1;  // Titik ada di area terlarang
    }
    return 0;  // Aman untuk titik
}

// Inisialisasi titik-titik dengan pengecekan area UI
void initializeDots() {
    int startX = 50, startY = 50;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int x = startX + j * DOT_SPACING;
            int y = startY + i * DOT_SPACING;
            if (!isInsideObstacle(x, y)) {
                dots[i][j] = 1;  // Hanya buat titik jika tidak bertabrakan dengan UI
            } else {
                dots[i][j] = 0;
            }
        }
    }
}

// Menggambar titik-titik yang belum dimakan
void drawDots() {
    int startX = 50, startY = 50;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (dots[i][j]) {  // Hanya menggambar titik yang belum dimakan
                int x = startX + j * DOT_SPACING;
                int y = startY + i * DOT_SPACING;
                fillellipse(x, y, DOT_RADIUS, DOT_RADIUS);
            }
        }
    }
}

// Mengecek apakah Pac-Man memakan titik
void checkCollisionWithDots(int pacmanX, int pacmanY, int *score) {
    int startX = 50, startY = 50;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int x = startX + j * DOT_SPACING;
            int y = startY + i * DOT_SPACING;
            if (dots[i][j] && abs(pacmanX - x) < DOT_SPACING / 2 && abs(pacmanY - y) < DOT_SPACING / 2) {
                dots[i][j] = 0;  // Titik dimakan
                (*score)++;      // Tambah skor
            }
        }
    }
}
