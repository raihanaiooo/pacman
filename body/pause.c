#include <graphics.h>
#include "../header/pause.h"

int isPaused = 0;
int score = 0;
Pacman pacman;
Ghost ghosts[MAX_GHOSTS];

void togglePause() {
    isPaused = !isPaused;
}

void drawPauseScreen() {
    int screenWidth = getmaxx();
    int screenHeight = getmaxy();
    
    int boxWidth = 300;
    int boxHeight = 150;
    int boxX1 = (screenWidth - boxWidth) / 2;
    int boxY1 = (screenHeight - boxHeight) / 2;
    int boxX2 = boxX1 + boxWidth;
    int boxY2 = boxY1 + boxHeight;

    // Kotak semi-transparan
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(boxX1, boxY1, boxX2, boxY2);
    rectangle(boxX1, boxY1, boxX2, boxY2); // Kotak tepi
    
    // Teks pause
    char teks1[] = "Game Paused";
    char teks2[] = "Press P to resume";

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    
    int teks1Width = textwidth(teks1);
    int teks1Height = textheight(teks1);
    int teks2Width = textwidth(teks2);
    int teks2Height = textheight(teks2);

    int textX1 = boxX1 + (boxWidth - teks1Width) / 2;
    int textX2 = boxX1 + (boxWidth - teks2Width) / 2;
    int textY1 = boxY1 + (boxHeight / 3) - (teks1Height / 2);
    int textY2 = boxY1 + (2 * boxHeight / 3) - (teks2Height / 2);

    setcolor(WHITE);
    outtextxy(textX1, textY1, teks1);
    outtextxy(textX2, textY2, teks2);

    setvisualpage(getactivepage());
}



void gameLoop() {
    while (1) {
        // Tetap gambar map meskipun game di-pause
        Map();
        drawPowerUps();
        gambarDot();

        for (int i = 0; i < MAX_GHOSTS; i++) {
            designGhost(&ghosts[i]);
        }

        drawPacman(&pacman);
        
        if (!isPaused) {
            movePacman(&pacman, ' ', &score);
            for (int i = 0; i < MAX_GHOSTS; i++) {
                moveGhost(&ghosts[i], &pacman);
            }
        } else {
            drawPauseScreen();
        }

        if (kbhit()) {
            char key = getch();
            handleInput(key);
        }
        delay(100);
    }
}

void handleInput(char key) {
    if (key == 'P' || key == 'p') {
        togglePause();
    }
}
