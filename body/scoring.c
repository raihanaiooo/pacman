#include <graphics.h>
#include "../header/scoring.h"
#include "../header/ui.h"
#include <stdio.h>

extern int maze[24][32]; // ambil peta dari ui.c

// Array untuk menyimpan status titik (1 = ada, 0 = dimakan atau tidak tersedia)
int dots[24][32];

// inisialisasi titik
void setTitikDot() {
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 32; j++) {
            if (maze[i][j] == 0) { 
                // ngosongin titik di rongga huruf "B"
                if (!((i == 18 && (j == 11 || j == 12)) ||  
                      (i == 20 && (j == 11 || j == 12)))) {
                    dots[i][j] = 1;  // Tetap ada dot di jalur biasa
                } else {
                    dots[i][j] = 0;  // Kosongkan titik di area rongga
                }
            } else {
                dots[i][j] = 0;  // Dinding tidak memiliki dot
            }
        }
    }
}


// Menggambar titik-titik yang belum dimakan
void gambarDot() {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 32; j++) {
            if (dots[i][j]) {  // Hanya menggambar titik yang belum dimakan
                int x = j * 20 + 10;
                int y = i * 20 + 10;
                fillellipse(x, y, DOT_RADIUS, DOT_RADIUS);
            }
        }
    }
}

// Mengecek apakah Pac-Man memakan titik
void scoring(int pacmanX, int pacmanY, int *score) {
    int i = pacmanY / 20;
    int j = pacmanX / 20;

    if (i >= 0 && i < 24 && j >= 0 && j < 32 && dots[i][j]) {
        dots[i][j] = 0;  // Titik dimakan
        (*score) += 10;    // Tambah skor
    }
}
