#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "pacman-lives.h"

void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts) {
    for (int i = 0; i < numGhosts; i++) {
        if (checkCollisionWithGhost(pacman, &ghosts[i])) {
            pacman->lives--;  
            printf("💀 Pacman terkena hantu! Sisa nyawa: %d\n", pacman->lives);

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
    outtextxy(250, 200, "Game Over!");
    
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 3);
    outtextxy(180, 250, "Main lagi? (Y/N)");

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
