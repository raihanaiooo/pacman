#include <graphics.h>
#include <stdio.h>
#include "../header/game-over-screen.h"

void displayGameOverScreen() {
    cleardevice();
    setcolor(RED);
    
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    char gameOverMsg[] = "GAME OVER!";
    outtextxy(250, 200, gameOverMsg);
    
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    char mainAgainMsg[] = "Main lagi? (Y/N)";
    outtextxy(200, 250, mainAgainMsg);
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
