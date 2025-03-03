<<<<<<< HEAD
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
=======
#ifndef PACMAN_H
#define PACMAN_H
#include <graphics.h>

typedef struct {
    int x, y;
    int radius;
    int direction;
} Pacman;

void drawPacman(Pacman *p);

void clearPacman(Pacman *p);

void movePacman(Pacman *p, char key);

int isColliding(Pacman *p, int newX, int newY);

#endif
>>>>>>> f8d98a9f59a1559bb8c934d76cd26fbb4f3c48e2
