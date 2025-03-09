#include <graphics.h>
#include "../header/scoring.h"
#include "../header/ui.h"
#include <stdio.h>

extern int maze[24][32]; // ambil peta dari ui.c

// Array buat nyimpen status dot dimakan atau belum
int dots[24][32];

int dotKosong(int i, int j) {
    return (
        // kosongin titik
        ((i == 18 && (j == 11 || j == 12)) ||  
         (i == 20 && (j == 11 || j == 12))) ||
        (i == 9 && (j >= 0 && j <= 4)) ||
        (i == 9 && (j >= 27 && j <= 31)) ||
        (i == 13 && (j >= 0 && j <= 4)) ||
        (i == 13 && (j >= 27 && j <= 31)) ||
        (i == 11 && (j >= 13 && j <= 18)) ||
        (i == 12 && (j >= 13 && j <= 18)) ||
        ((i >= 18 && i <= 20) && j == 6) ||
        ((i >= 17 && i <= 20) && j == 8) ||
        (i == 21 && j == 13) ||
        (i == 19 && j == 13) ||
        (i == 18 && (j == 19 || (j >= 23 && j <= 24))) ||
        (i == 17 && (j >= 19 && j <= 20)) ||
        (i == 20 && (j == 19 || (j >= 24 && j <= 25))) ||
        (i == 21 && (j >= 19 && j <= 20))||
        ((i >= 18 && i <= 29) && j == 21)||
        (i == 19 && j == 20) 
    );
}

// inisialisasi titik
void setTitikDot() {
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 32; j++) {
            if (maze[i][j] == 0 && !dotKosong(i, j)) { 
                dots[i][j] = 1;  // Tetap ada dot di jalur biasa
            } else {
                dots[i][j] = 0;  // Kosongin titik di dinding
            }
        }
    }
}

// generate titik-titik yang belum dimakan
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

// pacman makan titik
void scoring(int pacmanX, int pacmanY, int *score) {
    int i = pacmanY / 20;
    int j = pacmanX / 20;

    if (i >= 0 && i < 24 && j >= 0 && j < 32 && dots[i][j]) {
        dots[i][j] = 0;  // Titik dimakan
        (*score) += 10;    // Tambah skor
    }
}
