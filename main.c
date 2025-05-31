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
    Pacman pacman = {320, 290, 8, 0, 3, 320, 290}; // Pac-Man dengan 3 nyawa
    initPacmanAnimation(&pacman); //animasi mulut pacman
    clock_t lastMoveTime = 0;
    const int moveDelay = 100; // Delay Pac-Man dalam ms (0.1 detik)
    int lastKeyPressed = 0; // Menyimpan arah terakhir
    int score = 0;
    int page = 0; 
    initLives();

    // Inisialisasi titik-titik
    setTitikDot(); 
    spawnPowerUps();

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

    // Game Loop
    while (pacman.lives > 0) {
        clock_t currentTime = clock();

        // Game Rendering
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        Map();
        drawPowerUps();
        gambarDot();
        drawLives(lives);
        displayPowerUpInfo();

        // Ghost Movement
        updateGhosts(&ghostList);
        GhostNode* node = ghostList;
        while (node != NULL) {
            node->ghost.stepCounter++;
            if (node->ghost.stepCounter % ghostSpeed == 0) {
                moveGhost(&node->ghost, &pacman);
            }
            drawGhostWithEffect(node); // Efek visual jika kebalActive
            node = node->next;
        }

        // Pacman Movement
        if ((currentTime - lastMoveTime) * 1000 / CLOCKS_PER_SEC >= moveDelay) {
            movePacman(&pacman, lastKeyPressed, &score);
            lastMoveTime = currentTime;
        }

        drawPacman(&pacman);
        hitungScore(score, 48, 476, 0);
        updatePowerUpState();

        // Input Handling
        if (kbhit()) {
            int newKey = getch();
            if (newKey == 0 || newKey == 224) {
                newKey = getch();
                lastKeyPressed = newKey; 
            } else {
                handleInput(newKey, &pacman, NULL);
            }
        }

        // Kurangi Nyawa Pacman
        GhostNode* currentGhost = ghostList;  // Gunakan pointer sementara untuk iterasi

        while (currentGhost != NULL) {
            if (!doublePointActive && CollisionWithGhost(&pacman, currentGhost)) {
                updatePacmanAfterCollision(&pacman, currentGhost, MAX_GHOSTS, &score);
                removeLife(&lives);  // Hapus satu nyawa dari linked list
                break;
            }
            currentGhost = currentGhost->next;
        }

        // Pac-Man menabrak Ghost
        node = ghostList;
        while (node != NULL) {
            if (CollisionWithGhost(&pacman, node)) {
                updatePacmanAfterCollision(&pacman, node, 0, &score);
                break;
            }
            node = node->next;
        }
        
        // Cek jika nyawa habis
        if (lives == NULL) {
            setactivepage(1);
            setvisualpage(1);
            cleardevice();

            int isRestart = handleGameOver(&pacman, &score, ghostList, MAX_GHOSTS); // pake ghostList linked list
            initLives();  // Restart nyawa

            if (isRestart) {
                initLives();  // Restart nyawa
                continue;     // Restart permainan
            } else {
                break;        // Keluar dari loop utama
            }
        }


        // Kondisi jika semua dots & powerups habis
        if (countDotsAndPowerUps() == 0) {
            setactivepage(1); 
            setvisualpage(1);  
            cleardevice();  //  Pastikan layar bersih sebelum menampilkan kemenangan
        
            GameWin();  //  Tampilkan "You Win"
            hitungScore(score, 320, 300, 1);  // Tampilkan skor akhir di tengah layar
        
            delay(1000);  // Beri jeda sejenak agar pemain bisa melihat layar
            getch();  // Tunggu input sebelum keluar
        
            break;  // Keluar dari loop utama
        }
        
        delay(50);
        page = 1 - page;
    }

    closegraph();
    return 0;
}
