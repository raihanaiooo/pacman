#include <stdio.h>
#include <graphics.h>
#include "header/ui.h"
#include "header/ghost.h"
#include "header/pacman.h"
#include "header/scoring.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // initialize graphics windows

    initializeDots(); // inisialisasi dot 
    Ghost ghost;
    theGhost(&ghost, 100, 100, RED);  // Buat ghost biru di (100,100)

    Pacman pacman = {200,200,10,0};

    int score = 0;
    int page = 0;
    int key = 0;
    // MAIN STRUCTUR 
    while (1) {  // Loop sampai tombol ditekan
        //* ====================================MAP=======================================
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        map();
        
         //* ====================================dot=======================================
        drawDots();

        //* ====================================GHOST=======================================
        designGhost(&ghost);
        shiftGhost(&ghost, getmaxx(), getmaxy());
        
        drawDots();
        //* ====================================PACMAN=======================================
        if (kbhit()) { 
            key = getch();
            if (key == 27)
                break;
            if (key == 0 || key == 224)
                key = getch();
            movePacman(&pacman, key);

            checkCollisionWithDots(pacman.x, pacman.y, &score); //check dot kemakan
        }
        drawPacman(&pacman);
        if (GetAsyncKeyState(VK_ESCAPE)) 
            break;

        delay(50);
        page = 1 - page;
    }

    // getch();
    closegraph();
    return 0; 
}


