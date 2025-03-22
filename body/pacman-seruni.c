#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include "../header/pacman.h"
#include "../header/ghost.h"
#include "../header/lives-display.h"
#include "../header/scoring.h"
#include "../header/ui.h"

/* --- Fungsi dari pacman-seruni.c --- */

// Fungsi resetPacman: menghapus tampilan pacman lama, mereset posisinya, dan menggambarnya ulang.
void resetPacman(Pacman *p) {
    clearPacman(p);               // Hapus tampilan pacman lama
    p->x = p->initialX;           // Reset posisi x
    p->y = p->initialY;           // Reset posisi y
    drawPacman(p);                // Gambar ulang pacman di posisi awal
}

/* --- Fungsi updatePacmanAfterCollision --- */

void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts, int *score) {
    for (int i = 0; i < numGhosts; i++) {
        if (checkCollisionWithGhost(pacman, &ghosts[i])) {
            pacman->lives--;  
            printf("💀 Pacman terkena hantu! Sisa nyawa: %d\n", pacman->lives);

            // Reset posisi semua ghost ke posisi awal setelah tabrakan
            for (int j = 0; j < numGhosts; j++) {
                resetGhost(&ghosts[j]);
            }
            
            if (pacman->lives <= 0) {
                GameOver(*score);
                resetPacman(pacman);
                // resetPowerUps();
                // resetLives(pacman);
                score = 0;
            } else {
                resetPacman(pacman);
            }
            break;
        }
    }
}