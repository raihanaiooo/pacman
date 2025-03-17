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
    for (int i = 0; i < 50; i++) {
        setcolor(COLOR(50, 50, 50)); // Warna abu-abu gelap
        rectangle(90 + i, 90 + i, 310 - i, 210 - i);
    }
    
    floodfill(200, 150, WHITE); // Isi dengan warna hitam
    char teks1[] = "Game Paused";
    char teks2[] = "Press P to resume";
    // Teks pause
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(140, 130, teks1);
    outtextxy(120, 160, teks2);
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
