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
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    
    // Kotak semi-transparan
    bar(90, 90, 310, 210);
    setcolor(WHITE);
    rectangle(90, 90, 310, 210); // Kotak tepi
    
    char teks1[] = "Game Paused";
    char teks2[] = "Press P to resume";
    // Teks pause
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(140, 130, teks1);
    outtextxy(120, 160, teks2);
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
            autoMovePacman(&pacman, &score);
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
