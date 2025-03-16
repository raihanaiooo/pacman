// ! =================================== compile ==================================================================================================
// ! g++ main.c body/pacman.c body/powerup.c body/ui.c body/ghost.c body/scoring.c body/pacman-lives.c body/lives-display.c body/game-over-screen.c -o pacman.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
// ! ==============================================================================================================================================

#include <stdio.h>
#include <graphics.h>
#include "header/ui.h"
#include "header/ghost.h"
#include "header/pacman.h"
#include "header/scoring.h"
#include "header/powerup.h"
#include "header/pacman-lives.h"
#include "header/lives-display.h"
#include "header/game-over-screen.h"

void resetGame(Pacman *pacman, Ghost ghosts[], int *score) {
    // Reset kondisi permainan
    pacman->x = 190;
    pacman->y = 190;
    pacman->lives = 8;  
    *score = 0;

    // Reset posisi hantu
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    // Reset power-up dan titik dot
    setTitikDot();
    spawnPowerUps();
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // initialize graphics window

    Pacman pacman = {190, 190, 8, 0, 8};  // Pacman dengan 8 nyawa
    int score = 0;
    int page = 0;
    int key = 0;
    
    Ghost ghosts[MAX_GHOSTS];
    resetGame(&pacman, ghosts, &score);

    // MAIN STRUCTURE 
    while (1) {  // Loop utama untuk restart game setelah Game Over
        GameStart();

        while (pacman.lives > 0) {  // Game berjalan selama Pac-Man masih punya nyawa
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
                if (key == 27) // ESC untuk pause
                    GamePause();
                if (key == 0 || key == 224)
                    key = getch();
                movePacman(&pacman, key);
                scoring(pacman.x, pacman.y, &score); // Cek dot yang dimakan
            }

            drawPacman(&pacman);
            hitungScore(score);
            updatePowerUpState();

            // Cek tabrakan dengan Ghost
            updatePacmanAfterCollision(&pacman, ghosts, MAX_GHOSTS);

            // Tampilkan jumlah nyawa di layar
            displayLives(&pacman);

            delay(150);
            page = 1 - page;
        }

        // Jika Pacman kehabisan nyawa, tampilkan Game Over
        if (handleGameOver(&pacman) == 0) {
            break;  // Keluar dari loop utama jika pemain memilih keluar
        }

        // Jika pemain memilih main lagi, reset game
        resetGame(&pacman, ghosts, &score);
    }

    closegraph();
    return 0;
}
