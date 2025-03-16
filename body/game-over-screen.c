#include <graphics.h>
#include <stdio.h>
#include "game-over-screen.h"

void displayGameOverScreen() {
    cleardevice();
    setcolor(RED);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(250, 200, "GAME OVER!");
    
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(200, 250, "Main lagi? (Y/N)");
}

int getGameOverChoice() {
    char choice;
    while (1) {
        if (kbhit()) {
            choice = getch();
            if (choice == 'Y' || choice == 'y') {
                return 1;  // Main lagi
            } else if (choice == 'N' || choice == 'n') {
                return 0;  // Keluar
            }
        }
    }
}