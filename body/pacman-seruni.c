#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include "../header/pacman.h"
#include "../header/ghost.h"
#include "../header/pacman-lives.h"

// Fungsi untuk mengecek tabrakan antara Pac-Man dan Ghost
extern int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);

// Definisi resetPacman()
void resetPacman(Pacman *p) {
    clearPacman(p);               // Hapus tampilan pacman lama
    p->x = p->initialX;           // Reset posisi x
    p->y = p->initialY;           // Reset posisi y
    drawPacman(p);                // Gambar ulang pacman di posisi awal
}

void updatePacmanAfterCollision(Pacman *pacman, Ghost *ghost) {
    if (checkCollisionWithGhost(pacman, ghost)) {
        pacman->lives--;  // Kurangi nyawa Pacman
        printf("\U0001F480 Pacman terkena hantu! Sisa nyawa: %d\n", pacman->lives);
        if (pacman->lives <= 0) {
            printf("\U0001F480 Game Over! Pacman kehabisan nyawa.\n");
            exit(0);  // Hentikan permainan
        } else {
            resetPacman(pacman);
             // ADDED: Reset posisi ghost ke posisi awal setelah tabrakan
             resetGhost(ghost);
        }
    }
}
