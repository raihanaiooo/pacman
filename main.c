        // ! ====================================compile=======================================
        // ! g++ main.c body/pacman.c body/powerup.c body/ui.c body/scoring.c -o pacman.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

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
        // drawDots();
        drawPowerUps(); 
        gambarDot();

        //* ====================================GHOST=======================================
        for (int i = 0; i < MAX_GHOSTS; i++) {
            shiftGhost(&ghosts[i]);
            designGhost(&ghosts[i]);
            pursuePacman(&ghosts[i], &pacman);
            GhostEatingPacman(&ghosts[i], &pacman);  
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
            checkPowerUpCollision(pacman.x, pacman.y);
        }

        drawPacman(&pacman);
        hitungScore(score);
        updatePowerUpState();
        // Cek jika Pac-Man bertabrakan dengan Ghost
        if (checkCollisionWithGhost(&pacman, ghosts)) {
            pacman.lives--; // Kurangi nyawa
            pacman.x = 200;  // Reset posisi Pac-Man
            pacman.y = 200;
            printf("Pac-Man terkena Ghost! Nyawa tersisa: %d\n", pacman.lives);
        }

        if (pacman.lives <= 0) {
            printf("Game Over! Skor Akhir: %d\n", score);
            break;
        }

        if (GetAsyncKeyState(VK_ESCAPE)) 
            break;

        delay(50);
        page = 1 - page;
    }

    closegraph();
    return 0; 
    }
}