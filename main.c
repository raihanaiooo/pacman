#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <stdlib.h>
#include "header/ui.h"
#include "header/ghost.h"
#include "header/pacman.h"
#include "header/scoring.h"
#include "header/powerup.h"
#include "header/pause.h"

GhostNode* ghostList = NULL; // Linked list Ghost dinamis

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    clock_t lastMoveTime = 0;
    const int moveDelay = 100; // Delay Pac-Man dalam ms (0.1 detik)
    int lastKeyPressed = 0; // Menyimpan arah terakhir
    int score = 0;
    int page = 0; 

    // Inisialisasi titik-titik
    setTitikDot(); 
    spawnPowerUps();

    // Inisialisasi Pac-Man
    Pacman pacman = {320, 290, 8, 0, 3, 320, 290};

    // Inisialisasi Ghost dinamis
    addGhost(&ghostList, 320, 240, RED);
    addGhost(&ghostList, 330, 240, WHITE);
    addGhost(&ghostList, 310, 240, GREEN);
    addGhost(&ghostList, 340, 240, CYAN);
    const int ghostSpeed = 4; // Ghost akan bergerak setiap 4 frame

    // Musik start
    PlaySound("sound/start.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    GameStart();
    PlaySound(NULL, NULL, 0);

    while (pacman.lives > 0) {
        clock_t currentTime = clock();

        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        Map();
        drawPowerUps();
        gambarDot();
        displayLives(&pacman);

        // Perbarui dan gambar Ghost
        updateGhosts(&ghostList);
        GhostNode* node = ghostList;
        while (node != NULL) {
            node->ghost.stepCounter++;
            if (node->ghost.stepCounter % ghostSpeed == 0) {
                moveGhost(&node->ghost, &pacman);
            }
            node = node->next;
        }
        
        drawGhosts(ghostList);

        if ((currentTime - lastMoveTime) * 1000 / CLOCKS_PER_SEC >= moveDelay) {
            movePacman(&pacman, lastKeyPressed, &score);
            lastMoveTime = currentTime;
        }

        drawPacman(&pacman);
        hitungScore(score, 48, 476, 0);
        updatePowerUpState();

        if (kbhit()) {
            int newKey = getch();
            if (newKey == 0 || newKey == 224) {
                newKey = getch();
                lastKeyPressed = newKey; 
            } else {
                handleInput(newKey, &pacman, NULL);
            }
        }

        node = ghostList;
        while (node != NULL) {
            if (!doublePointActive && CollisionWithGhost(&pacman, &node->ghost)) {
                updatePacmanAfterCollision(&pacman, NULL, 0, &score);
                break;
            }
            node = node->next;
        }

        if (pacman.lives == 0) {
            setactivepage(1);
            setvisualpage(1);
            cleardevice();

            int isRestart = handleGameOver(&pacman, &score, NULL, 0);

            if (isRestart) {
                continue;
            } else {
                break;
            }
        }

        if (countDotsAndPowerUps() == 0) {
            setactivepage(1);
            setvisualpage(1);
            cleardevice();

            GameWin();
            hitungScore(score, 320, 300, 1);
            delay(1000);
            getch();

            break;
        }

        delay(50);
        page = 1 - page;
    }

    closegraph();
    return 0;
}
