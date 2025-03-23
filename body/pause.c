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

    char teks1[] = "Game Paused";
    char teks2[] = "Press P to Resume";

    // Kotak hitam semi-transparan di tengah
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(boxX1, boxY1, boxX2, boxY2);
    rectangle(boxX1, boxY1, boxX2, boxY2);

    // Set text style
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);

    // Set text justify ke tengah-tengah
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    // Tulis teks tepat di tengah kotak
    outtextxy(screenWidth / 2, screenHeight / 2 - 20, teks1);
    outtextxy(screenWidth / 2, screenHeight / 2 + 20, teks2);

    // Update tampilan
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
