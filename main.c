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
    clock_t lastMoveTime = 0;  // Menyimpan waktu terakhir Pac-Man bergerak
    const int moveDelay = 100; // Delay pergerakan dalam milidetik (0.1 detik)
    int lastKey = 0;           // Variabel untuk menyimpan input terakhir
    clock_t currentTime = clock();

    setTitikDot(); // Inisialisasi titik-titik
    spawnPowerUps();

    Ghost ghosts[MAX_GHOSTS];
    int ghostStepCounter[MAX_GHOSTS] = {0};  // Step counter untuk setiap Ghost
    const int ghostSpeed = 3;  // Ghost hanya bergerak setiap 2 frame Pac-Man
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    // Update initializer pacman: tambahkan initialX dan initialY
    Pacman pacman = {190, 190, 8, 0, 8, 190, 190};  // ADDED: Inisialisasi nyawa Pac-Man menjadi 8
    int score = 0;
    int page = 0;
    int key = 0;
    
    // resetGame(&pacman, ghosts, &score);

    PlaySound("sound/start.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // * puter music
    GameStart(); // Tampilan awal
    PlaySound(NULL, NULL, 0);  // suara ilang pas mulai main

    while (pacman.lives > 0) {
        currentTime = clock();

        // **Pause Handling**
        if (isPaused) {
            drawPauseScreen();     // Tampilkan layar pause
            setvisualpage(page);   // Update tampilan
            while (isPaused) {
                if (kbhit()) {
                    int newKey = getch();
                    if (newKey == 'p' || newKey == 'P') {
                        isPaused = 0; // Resume game
                    }
                }
                delay(100); // Hindari penggunaan CPU tinggi
            }
            continue;  // Langsung lanjut loop utama tanpa update game
        }

        // **Game Rendering**
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
            ghostStepCounter[i]++;  // Tambahkan step counter untuk Ghost ini
        }
         

        // **Input Handling**
        if (kbhit()) {
            int newKey = getch();
            if (newKey == 0 || newKey == 224) {
                int arrowKey = getch();
                if (arrowKey == 80 || arrowKey == 72 || arrowKey == 75 || arrowKey == 77) {
                    key = arrowKey; // Simpan input hanya untuk gerakan
                }
            } else if (newKey == 'p' || newKey == 'P') {
                isPaused = 1; // Pause game
                continue;
            }
        }

        // **Pac-Man Movement**
        if ((clock() - lastMoveTime) * 1000 / CLOCKS_PER_SEC >= moveDelay) {
            movePacman(&pacman, key, &score);
            lastMoveTime = clock(); // Update waktu terakhir
            key = 0; // Reset key setelah digunakan
        }

        drawPacman(&pacman);
        hitungScore(score, 48, 476, 0);
        updatePowerUpState();

        // Cek tabrakan dengan semua Ghost
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (checkCollisionWithGhost(&pacman, &ghosts[i])) {
                pacman.lives--;  // Kurangi nyawa Pac-Man
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
    

        delay(50);
        page = 1 - page;
    }

    closegraph();
    return 0; 
}

