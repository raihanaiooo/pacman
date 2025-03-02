#include <stdio.h>
#include <graphics.h>
#include "header/pacman.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // initialize graphics windows
    
        initGame();
        while (!gameOver) {
            drawMap();
            input();
            logic();
        }

        printf("Game Over!\n");
        
    getch();
    closegraph();

    return 0;
}