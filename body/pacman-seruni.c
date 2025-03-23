#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include "../header/pacman.h"
#include "../header/ghost.h"
#include "../header/scoring.h"
#include "../header/ui.h"
#include "../header/powerup.h"

/* --- Fungsi dari pacman-seruni.c --- */

// Fungsi resetPacman: menghapus tampilan pacman lama, mereset posisinya, dan menggambarnya ulang.
void resetPacman(Pacman *p) {
    clearPacman(p);               // Hapus tampilan pacman lama
    p->x = p->initialX;           // Reset posisi x
    p->y = p->initialY;           // Reset posisi y
    drawPacman(p);                // Gambar ulang pacman di posisi awal
}

int handleGameOver(Pacman *pacman, int *score, Ghost ghosts[], int numGhosts) {
    int playAgain = GameOver(*score);
    if (playAgain) {
        // Reset seluruh game state
        resetPacman(pacman);
        for (int i = 0; i < numGhosts; i++) {
            resetGhost(&ghosts[i]);
        }
        *score = 0;
        pacman->lives = 3;
        setTitikDot();     // Reset dots
        spawnPowerUps();   // Reset power-ups
        return 1; // Main lagi
    } else {
        closegraph();
        exit(0);
    }
}

/* --- Fungsi updatePacmanAfterCollision --- */
void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts, int *score) {
    pacman->lives--;

void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts) {
    for (int i = 0; i < numGhosts; i++) {
        if (checkCollisionWithGhost(pacman, &ghosts[i])) {

            // Jika Pac-Man kebal, reset posisi Ghost tanpa mengurangi nyawa. pacman kebal dan ga ngurangin nyawa
            if (kebalActive) {
                printf("🔥 Pac-Man kebal! Ghost kembali ke posisi awal.\n");

                // Respawn Ghost ke posisi awal
                resetGhost(&ghosts[i]);
                continue;  // Lewati proses pengurangan nyawa
            }


            pacman->lives--;  
            printf("💀 Pacman terkena hantu! Sisa nyawa: %d\n", pacman->lives);

            // Reset posisi semua ghost ke posisi awal setelah tabrakan
            for (int j = 0; j < numGhosts; j++) {
                resetGhost(&ghosts[j]);
            }
            
            if (pacman->lives <= 0) {
                if (handleGameOver(pacman) == 0) {
                    exit(0);
                } else {
                    pacman->lives = 8;
                    pacman->x = pacman->initialX;
                    pacman->y = pacman->initialY;
                }
            } else {
                pacman->x = pacman->initialX;
                pacman->y = pacman->initialY;
            }
            break;
        }
    }
    // Jika nyawa habis, biarkan loop utama yang urus GameOver
}

