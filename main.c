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

    setTitikDot(); // Inisialisasi titik-titik
    spawnPowerUps();

    Ghost ghosts[MAX_GHOSTS];
    int ghostStepCounter[MAX_GHOSTS] = {0};  // Step counter untuk setiap Ghost
    const int ghostSpeed = 3;  // Ghost hanya bergerak setiap 2 frame Pac-Man
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    Pacman pacman = {190, 190, 8, 0, 3}; // Pac-Man dengan 3 nyawa
    int score = 0;
    int page = 0;
    int key = 0;
    int isPaused = 0;

    PlaySound("sound/start.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // * puter music
    GameStart(); // Tampilan awal
    PlaySound(NULL, NULL, 0);  // suara ilang pas mulai main

    while (pacman.lives > 0) {
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
         

        for (int i = 0; i < MAX_GHOSTS; i++) {
            shiftGhost(&ghosts[i]);
            designGhost(&ghosts[i]);
            if (!doublePointActive) {
                pursuePacman(&ghosts[i], &pacman); // Hantu mengejar Pac-Man jika tidak dalam power-up
            }
        }

        clock_t currentTime = clock();

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

        if (GetAsyncKeyState(VK_ESCAPE)) break;
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (!doublePointActive && checkCollisionWithGhost(&pacman, &ghosts[i])) {
                pacman.lives--;
                pacman.x = 200;
                pacman.y = 200;
            }
        }

        if (pacman.lives <= 0) {
            int playAgain = GameOver(score); // Panggil fungsi GameOver dan simpan hasilnya
            if (playAgain) {
                // Reset permainan jika pemain memilih untuk bermain lagi
                pacman.lives = 3;
                pacman.x = 190;
                pacman.y = 190;
                score = 0;
                key = 0;
                setTitikDot(); // Reset titik-titik
                spawnPowerUps(); // Reset power-ups
                continue; // Kembali ke awal loop utama
            } else {
                break; // Keluar dari loop utama jika pemain memilih untuk keluar
            }
        }

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
        
        if (GetAsyncKeyState(VK_ESCAPE))
            break;

        delay(50);
        page = 1 - page;
    }

    closegraph();
    return 0;
    }

