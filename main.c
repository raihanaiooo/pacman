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
#include "header/lives-display.h"
#include "header/game-over-screen.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // initialize graphics windows

    setTitikDot(); // inisialisasi dot 
    spawnPowerUps();

    Ghost ghosts[MAX_GHOSTS];
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    // Update initializer pacman: tambahkan initialX dan initialY
    Pacman pacman = {190, 190, 8, 0, 8, 190, 190};  // ADDED: Inisialisasi nyawa Pac-Man menjadi 8
    int score = 0;
    int page = 0;
    int key = 0;

    // MAIN STRUCTURE 
    while (1) {  // Selama game berjalan (pengecekan game over dilakukan di update collision)
        GameStart();

        while (1) {  // Loop utama game
            //* ====================================MAP=======================================
            setactivepage(page);
            setvisualpage(1 - page);
            cleardevice();
            Map();

            //* ====================================DOT=======================================
            gambarDot();

            //* ====================================GHOST=======================================
            for (int i = 0; i < MAX_GHOSTS; i++) {
                moveGhost(&ghosts[i], &pacman);
<<<<<<< HEAD
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
=======
                designGhost(&ghosts[i]);  
            }  
            
            //* ====================================PACMAN=======================================
            if (kbhit()) { 
                key = getch();
                if (key == 27)
                    //GamePause();
                if (key == 0 || key == 224)
                    key = getch();
>>>>>>> seruni
                movePacman(&pacman, key, &score);
                scoring(pacman.x, pacman.y, &score); // Cek dot kemakan
            }

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
<<<<<<< HEAD

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
=======
>>>>>>> seruni
    }
    closegraph();
    return 0; 
}
