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
#include "header/pacman-lives.h"

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
                designGhost(&ghosts[i]);  
            }  
            
            //* ====================================PACMAN=======================================
            if (kbhit()) { 
                key = getch();
                if (key == 27)
                    //GamePause();
                if (key == 0 || key == 224)
                    key = getch();
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
    }
    closegraph();
    return 0; 
}
