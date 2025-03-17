        // ! =================================== compile ==================================================================================================
        // ! g++ main.c body/pacman.c body/pacman-seruni.c body/powerup.c body/ui.c body/ghost.c body/scoring.c -o pacman.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
        // ! ==============================================================================================================================================

#include <stdio.h>
#include <graphics.h>
#include "header/ui.h"
#include "header/ghost.h"
#include "header/pacman.h"
#include "header/scoring.h"
#include "header/powerup.h"

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

    Pacman pacman = {190, 190, 8, 0, 1};  // Pac-Man dengan 3 nyawa
    int score = 0;
    int page = 0;
    int key = 0;

    // MAIN STRUCTURE 
    while (pacman.lives > 0) {  // Game berjalan selama Pac-Man masih punya nyawa
    // MAIN STRUCTUR 
    GameStart();

    while (1) {  // Loop sampai tombol ditekan
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
                GamePause();
            if (key == 0 || key == 224)
                key = getch();
            movePacman(&pacman, key);

            scoring(pacman.x, pacman.y, &score); // Cek dot kemakan
        }

        drawPacman(&pacman);
        hitungScore(score);
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
    

        delay(150);
        page = 1 - page;
    }

    closegraph();
    return 0; 
    }
}