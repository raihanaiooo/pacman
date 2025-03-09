#include <stdio.h>
#include <graphics.h>
#include "header/ui.h"
#include "header/ghost.h"
#include "header/pacman.h"
#include "header/scoring.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // initialize graphics windows

    setTitikDot(); // inisialisasi dot 
    Ghost ghost;
    theGhost(&ghost, 100, 100, RED);  // Buat ghost biru di (100,100)
    initializeDots(); // inisialisasi dot 
    Ghost ghosts[MAX_GHOSTS];
    theGhost(&ghosts[0], 100, 100, RED);
    theGhost(&ghosts[1], 400, 100, WHITE);
    theGhost(&ghosts[2], 100, 300, GREEN);
    theGhost(&ghosts[3], 400, 300, CYAN);

    Pacman pacman = {190,190,8,0};

    int score = 0;
    int page = 0;
    int key = 0;
    // MAIN STRUCTUR 
    while (1) {  // Loop sampai tombol ditekan
        //* ====================================MAP=======================================
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        Map();
        
         //* ====================================dot=======================================
        gambarDot();

        //* ====================================GHOST=======================================
        for (int i = 0; i < MAX_GHOSTS; i++) {
            shiftGhost(&ghosts[i]);
            designGhost(&ghosts[i]);
            pursuePacman(&ghosts[i], &pacman);
            GhostEatingPacman(&ghosts[i], &pacman);  
        }  
        
        gambarDot();
        //* ====================================PACMAN=======================================
        if (kbhit()) { 
            key = getch();
            if (key == 27)
                break;
            if (key == 0 || key == 224)
                key = getch();
            movePacman(&pacman, key);

            scoring(pacman.x, pacman.y, &score); //check dot kemakan
        }
        drawPacman(&pacman);
        hitungScore(score);
        if (GetAsyncKeyState(VK_ESCAPE)) 
            break;

        delay(50);
        page = 1 - page;
    }

    // getch();
    closegraph();
    return 0; 
}


