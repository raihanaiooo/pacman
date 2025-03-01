#include "ghost.h"

void theGhost(Ghost *gh, int x, int y, int hue) {
    gh->x = x;
    gh->y = y;
    gh->hue = hue;
    // Buat dx dan dy menjadi angka acak antara -3 dan 3, tetapi tidak 0
    do {
        gh->dx = (rand() % 7) - 3;  // Hasil antara -3 hingga 3
    } while (gh->dx == 0);

    do {
        gh->dy = (rand() % 7) - 3;  // Hasil antara -3 hingga 3
    } while (gh->dy == 0);
}


void designGhost(Ghost *gh) {
    setcolor(gh->hue);
    setfillstyle(SOLID_FILL, gh->hue);
    fillellipse(gh->x, gh->y, 15, 15);  // Kepala ghost
    rectangle(gh->x - 15, gh->y, gh->x + 15, gh->y + 20);  // Badan ghost
}

void shiftGhost(Ghost *gh, int limitX, int limitY) {
    gh->x += gh->dx;
    gh->y += gh->dy;

    // Jika menyentuh batas kanan atau kiri, balik arah horizontal
    if (gh->x <= 20 || gh->x >= limitX - 20) {
        gh->dx = (rand() % 7) - 3;  // Pilih arah baru secara acak
    }
    
    // Jika menyentuh batas atas atau bawah, balik arah vertikal
    if (gh->y <= 20 || gh->y >= limitY - 20) {
        gh->dy = (rand() % 7) - 3;  // Pilih arah baru secara acak
    }
}
