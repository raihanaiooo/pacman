#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include "header/ui.h"
#include "header/ghost.h"
#include "header/pacman.h"
#include "header/scoring.h"
#include "header/powerup.h"
#include "header/pause.h"

//! ====================================COMPILE======================================= 
//? g++ main.c body/pacman.c body/powerup.c body/ui.c body/scoring.c body/ghost.c body/pause.c -o pacman.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm 
//! ================================================================================== 

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    clock_t lastMoveTime = 0;
    const int moveDelay = 100; // Delay Pac-Man dalam ms (0.1 detik)
    int lastKeyPressed = 0; // Menyimpan arah terakhir
    int score = 0;
    int page = 0; 

    // Inisialisasi PowerUp dan Dot
    setTitikDot();
    spawnPowerUps();

    // Inisialisasi Pac-Man
    Pacman pacman = {190, 190, 8, 0, 8, 190, 190};  

    // Inisialisasi Ghosts
    Ghost ghosts[MAX_GHOSTS];
    int ghostStepCounter[MAX_GHOSTS] = {0};  
    const int ghostSpeed = 3;  
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    // Musik Start
    PlaySound("sound/start.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    GameStart(); 
    PlaySound(NULL, NULL, 0);  

    // Game Loop
    while (pacman.lives > 0) {
        clock_t currentTime = clock();

        // **Render Frame**
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        Map();
        drawPowerUps();
        gambarDot();

        // **Ghost Movement**
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (ghostStepCounter[i] % ghostSpeed == 0) {
                moveGhost(&ghosts[i], &pacman);
            }
            designGhost(&ghosts[i]);
            ghostStepCounter[i]++;
        }

        // **Pac-Man Movement**
        if ((currentTime - lastMoveTime) * 1000 / CLOCKS_PER_SEC >= moveDelay) {
            movePacman(&pacman, lastKeyPressed, &score);
            lastMoveTime = currentTime;
        }

        drawPacman(&pacman);
        hitungScore(score, 48, 476, 0);
        updatePowerUpState();

        // **Keyboard Input**
        if (kbhit()) {
            int newKey = getch();
            if (newKey == 0 || newKey == 224) { // Menangkap arrow key
                newKey = getch();
                lastKeyPressed = newKey; 
            } else {
                handleInput(newKey, &pacman, ghosts);
            }
        }

        // **Pause Handler**
        if (isPaused) {
            delay(100);
            continue; 
        }

        // **Cek Collision dengan Ghost**
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (checkCollisionWithGhost(&pacman, &ghosts[i])) {
                pacman.lives--;  
                if (pacman.lives > 0) {
                    pacman.x = 190;
                    pacman.y = 190;
                } else {
                    outtextxy(300, 250, (char*) "Game Over!");
                    delay(2000);
                    closegraph();
                    return 0;
                }
            }
        }

        // **Update Frame**
        delay(10); // Delay lebih kecil agar game lebih smooth
        page = 1 - page;
    }

    closegraph();
    return 0; 
}
