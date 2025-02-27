#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#define WIDTH 20
#define HEIGHT 10

// Struktur untuk menyimpan posisi Pac-Man
typedef struct {
    int x, y;
} Position;

// Variabel global
extern Position pacman;
extern Position food;
extern bool gameOver;
extern char map[HEIGHT][WIDTH];

// Deklarasi fungsi
void initGame();
void drawMap();
void input();
void logic();

#endif
