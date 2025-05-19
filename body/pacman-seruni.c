#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include "../header/pacman.h"
#include "../header/ghost.h"
#include "../header/scoring.h"
#include "../header/Revaldi.h"
#include "../header/powerup.h"

/* Modul logic pengurangan nyawa Pacman */

// Prosedur resetPacman: menghapus tampilan pacman lama, mereset posisinya, dan menggambarnya ulang
void resetPacman(Pacman *p) {
    clearPacman(p);               // Menghapus tampilan pacman lama
    p->x = p->initialX;           // Mereset posisi x
    p->y = p->initialY;           // Mereset posisi y
    drawPacman(p);                // Menggambar ulang pacman di posisi awal
}

// Fungsi handle game over
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

// Prosedure respawn pacman 
void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts, int *score) {
    pacman->lives--;
    
    if (pacman->lives > 0) {
    
        resetPacman(pacman);
        
        for (int i = 0; i < numGhosts; i++)
        {
        if (CollisionWithGhost(pacman, &ghosts[i])) {
        
        // Jika Pac-Man kebal, reset posisi Ghost tanpa mengurangi nyawa
        if (kebalActive) {
        printf("🔥 Pac-Man kebal! Ghost kembali ke posisi awal.\n");
        
            // Respawn Ghost ke posisi awal
            resetGhost(&ghosts[i]);
            continue;  // Lewati proses pengurangan nyawa
            }
        }
        resetGhost(&ghosts[i]);
        }
    
   }
   
}