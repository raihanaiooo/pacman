#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "../header/pacman-lives.h"

void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts) {
    for (int i = 0; i < numGhosts; i++) {
        if (checkCollisionWithGhost(pacman, &ghosts[i])) {
            pacman->lives--;  
            printf("💀 Pacman terkena hantu! Sisa nyawa: %d\n", pacman->lives);

            // ADDED: Reset posisi semua ghost ke posisi awal setelah tabrakan
            for (int j = 0; j < numGhosts; j++) {
                resetGhost(&ghosts[j]);
            }
            
            if (pacman->lives <= 0) {
                if (handleGameOver(pacman) == 0) {
                    exit(0);
                } else {
                    pacman->lives = 8;
                    pacman->x = 190;
                    pacman->y = 190;
                }
            } else {
                pacman->x = 190;
                pacman->y = 190;
            }
            break;
        }
    }
}

int handleGameOver(Pacman *pacman) {
    cleardevice();
    setcolor(RED);
    settextstyle(3, HORIZ_DIR, 5);
    char gameOverMsg[] = "Game Over!";
    outtextxy(250, 200, gameOverMsg);
    
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 3);
    char mainAgainMsg[] = "Main lagi? (Y/N)";
    outtextxy(180, 250, mainAgainMsg);

    while (1) {
        char key = getch();
        if (key == 'Y' || key == 'y') {
            return 1;  // Restart game
        } else if (key == 'N' || key == 'n') {
            closegraph();
            return 0;  // Keluar game
        }
    }
}
