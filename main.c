// ! =================================== compile ==================================================================================================
// ! g++ main.c body/pacman.c body/powerup.c body/ui.c body/ghost.c body/scoring.c -o pacman.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
// ! ==============================================================================================================================================

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

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    clock_t lastMoveTime = 0;
    const int moveDelay = 100;
    int lastKey = 0;
    clock_t currentTime = clock();

    setTitikDot();
    spawnPowerUps();

    Ghost ghosts[MAX_GHOSTS];
    int ghostStepCounter[MAX_GHOSTS] = {0};
    const int ghostSpeed = 3;
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    Pacman pacman = {190, 190, 8, 0, 8, 190, 190};
    int score = 0;
    int page = 0;
    int key = 0;

    PlaySound("sound/start.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    GameStart();
    PlaySound(NULL, NULL, 0);

    while (pacman.lives > 0) {
        if (isPaused) {
            drawPauseScreen();
            setvisualpage(page);
            while (isPaused) {
                if (kbhit()) {
                    int newKey = getch();
                    if (newKey == 'p' || newKey == 'P') {
                        isPaused = 0;
                    }
                }
                delay(100);
            }
        }

        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        Map();
        drawPowerUps();
        gambarDot();

        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (ghostStepCounter[i] % ghostSpeed == 0) {
                moveGhost(&ghosts[i], &pacman);
            }
            designGhost(&ghosts[i]);
            ghostStepCounter[i]++;
        }

        if (kbhit()) {
            int newKey = getch();
            if (newKey == 0 || newKey == 224) {
                int arrowKey = getch();
                if (arrowKey == 80 || arrowKey == 72 || arrowKey == 75 || arrowKey == 77) {
                    key = arrowKey;
                }
            } else if (newKey == 'p' || newKey == 'P') {
                isPaused = 1;
            }
        }

        if ((currentTime - lastMoveTime) * 1000 / CLOCKS_PER_SEC >= moveDelay) {
            if (key) {
                movePacman(&pacman, key, &score);
                scoring(pacman.x, pacman.y, &score); // Cek dot kemakan
            }
            //!MERGE CONFLICT
            lastMoveTime = currentTime;
        }

        autoMovePacman(&pacman, &score);
        drawPacman(&pacman);
        hitungScore(score, 48, 476, 0);
        updatePowerUpState();

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

        delay(150);
        page = 1 - page;

            drawPacman(&pacman);
            hitungScore(score, 10, 10, 0);
            updatePowerUpState();

            //* ====================================LIVES DISPLAY=======================================
            // ADDED: Panggil fungsi untuk menampilkan jumlah nyawa di layar
            displayLives(&pacman);

            //* ====================================TUMBAK (COLLISION)=======================================
            // ADDED: Panggil fungsi update collision dari pacman-lives (yang juga mengatur reset posisi ghost)
            updatePacmanAfterCollision(&pacman, ghosts, MAX_GHOSTS);

            // ADDED: Jika nyawa habis, tampilkan game over screen
            if(pacman.lives <= 0) {
                displayGameOverScreen();
                if(getGameOverChoice() == 1) {
                    // Reset game: nyawa Pac-Man dan posisi awal
                    pacman.lives = 8;  // Set ulang nyawa ke 8
                    pacman.x = pacman.initialX;
                    pacman.y = pacman.initialY;
                    // Reset semua ghost ke posisi awal
                    for (int i = 0; i < MAX_GHOSTS; i++) {
                        resetGhost(&ghosts[i]);
                    }
                    score = 0; // Opsional: reset score
                    break; // Kembali ke GameStart()
                } else {
                    closegraph();
                    return 0;
                }
            }

            delay(150);
            page = 1 - page;
        }
        closegraph();
        return 0; 
    }
