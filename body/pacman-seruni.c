#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include "../header/pacman.h"
#include "../header/ghost.h"

// Gunakan fungsi dari ghost.c agar tidak duplikasi
// Fungsi untuk mengecek tabrakan antara Pac-Man dan Ghost
extern int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost);

/* --- Fungsi dari pacman-seruni.c --- */

// Fungsi resetPacman: menghapus tampilan pacman lama, mereset posisinya, dan menggambarnya ulang.
void resetPacman(Pacman *p) {
    clearPacman(p);               // Hapus tampilan pacman lama
    p->x = p->initialX;           // Reset posisi x
    p->y = p->initialY;           // Reset posisi y
    drawPacman(p);                // Gambar ulang pacman di posisi awal
}

/* --- Fungsi updatePacmanAfterCollision --- */

void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts) {
    for (int i = 0; i < numGhosts; i++) {
        if (checkCollisionWithGhost(pacman, &ghosts[i])) {
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

/* --- Fungsi updatePacmanAfterCollision --- */

void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts) {
    for (int i = 0; i < numGhosts; i++) {
        if (checkCollisionWithGhost(pacman, &ghosts[i])) {
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
}


