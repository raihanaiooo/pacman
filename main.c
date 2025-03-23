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

// ! COMPILE
// ! g++ main.c body/pacman.c body/pacman-seruni.c body/powerup.c body/ui.c body/ghost.c body/scoring.c body/pause.c -o pacman.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    clock_t lastMoveTime = 0;  // Menyimpan waktu terakhir Pac-Man bergerak
    const int moveDelay = 100; // Delay pergerakan dalam milidetik (0.1 detik)
    int lastKey = 0;           // Variabel untuk menyimpan input terakhir
    clock_t currentTime = clock();

    // Inisialisasi titik-titik
    setTitikDot(); 
    spawnPowerUps();

    // Inisialisasi Pac-Man
    Pacman pacman = {320, 290, 8, 0, 3, 320, 290}; // Pac-Man dengan 3 nyawa
    int score = 0;
    int page = 0;
    int key = 0;
    int isPaused = 0;
    
    //Inisialisasi Ghost
    Ghost ghosts[MAX_GHOSTS];
    int ghostStepCounter[MAX_GHOSTS] = {0};  // Step counter untuk setiap Ghost
    const int ghostSpeed = 3;  // Ghost hanya bergerak setiap 2 frame Pac-Man
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    // Musik start
    PlaySound("sound/start.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // * puter music
    GameStart(); // Tampilan awal
    PlaySound(NULL, NULL, 0);  // suara ilang pas mulai main

    // Game Loop
    while (pacman.lives > 0) {
        clock_t currentTime = clock();

        // **Pause Handler**
        if (isPaused) {
            delay(100);
            continue; 
        }

        // **Game Rendering**
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        Map();
        drawPowerUps();
        gambarDot();
        displayLives(&pacman);

        // Ghost Movement
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (ghostStepCounter[i] % ghostSpeed == 0) {
                moveGhost(&ghosts[i], &pacman);
            }
            designGhost(&ghosts[i]);
            ghostStepCounter[i]++;  // Tambahkan step counter untuk Ghost ini
        }
         
        // **Pac-Man Movement**
        if ((currentTime - lastMoveTime) * 1000 / CLOCKS_PER_SEC >= moveDelay) {
            if (key) {
                movePacman(&pacman, key, &score);
            } else {
                autoMovePacman(&pacman, &score);
            }
            lastMoveTime = currentTime;
        }

        drawPacman(&pacman);
        hitungScore(score, 48, 476, 0);
        updatePowerUpState();

        // **Input Handling**
        if (kbhit()) {
            int newKey = getch();
            if (newKey == 0 || newKey == 224) {
                int arrowKey = getch();
                if (arrowKey == 80 || arrowKey == 72 || arrowKey == 75 || arrowKey == 77) {
                    key = arrowKey; // Simpan input hanya untuk gerakan
                }
            } else {
                handleInput(newKey, &pacman, ghosts);
            }
        }


        if (GetAsyncKeyState(VK_ESCAPE)) break;

        // Cek tabrakan dengan Ghost
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (!doublePointActive && checkCollisionWithGhost(&pacman, &ghosts[i])) {
                updatePacmanAfterCollision(&pacman, ghosts, MAX_GHOSTS, &score);
                break;
            }
        }
        
        // Kondisi jika Pac-Man habis
        if (pacman.lives == 0) {
            setactivepage(1);
            setvisualpage(1);
            cleardevice();

            int isRestart = handleGameOver(&pacman, &score, ghosts, MAX_GHOSTS);
            if (isRestart) {
                continue; // Restart permainan
            } else {
                break; // Keluar dari loop utama
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

