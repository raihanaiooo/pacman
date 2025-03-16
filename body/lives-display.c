#include <graphics.h>
#include <stdio.h>
#include "header/lives-display.h"

void displayLives(Pacman *pacman) {
    char livesText[20];
    sprintf(livesText, "Lives: %d", pacman->lives);

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(10, 10, livesText); // Tampilkan nyawa di pojok kiri atas

    // Gambar ikon nyawa Pac-Man sebagai lingkaran kecil
    int startX = 100;
    for (int i = 0; i < pacman->lives; i++) {
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(startX + (i * 20), 20, 8, 8);  // Gambar ikon nyawa Pac-Man
    }
}

