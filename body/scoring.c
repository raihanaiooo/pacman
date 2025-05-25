#include <stdio.h>
#include <graphics.h>
#include <windows.h>  
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")  
#include "../header/scoring.h"
#include "../header/ui.h"
#include "../header/powerup.h"

extern int maze[ROWS][COLS]; // ambil peta dari Revaldi.c

// Array buat nyimpen status dot dimakan atau belum
int dots[ROWS][COLS];

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
        (i == 19 && j == 20) ||
        (i == 23 && (j >= 0 && j <= 31)) 
    );
}

// inisialisasi titik
void setTitikDot() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
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

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
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
    int row = pacmanY / TILE_SIZE;
    int col = pacmanX / TILE_SIZE;

    if (dots[row][col] == 1) {  // Jika ada dot di posisi Pac-Man
        dots[row][col] = 0;  // Hilangkan dot dari layar
        *score += doublePointActive ? 2 : 1;  // Tambah skor (doubled jika power-up aktif)

        PlaySound("sound/makan.wav", NULL, SND_FILENAME | SND_ASYNC);

    }
}