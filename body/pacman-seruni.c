#include <stdio.h>
#include "../header/pacman.h"
#include "../header/ghost.h"

// Gunakan fungsi dari ghost.c agar tidak duplikasi
extern int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);

void updatePacmanAfterCollision(Pacman *pacman, Ghost *ghost) {
    if (checkCollisionWithGhost(pacman, ghost)) {
        pacman->lives--;  // Kurangi nyawa Pacman
        printf("\U0001F480 Pacman terkena hantu! Sisa nyawa: %d\n", pacman->lives);

        if (pacman->lives <= 0) {
            printf("\U0001F480 Game Over! Pacman kehabisan nyawa.\n");
            exit(0);  // Hentikan permainan
        } else {
            // Reset posisi Pacman setelah terkena
            pacman->x = 200;
            pacman->y = 200;
        }
    }
}
