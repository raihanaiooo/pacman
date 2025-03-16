#include <stdio.h>
#include <graphics.h>
#include "header/ui.h"
#include "header/ghost.h"
#include "header/pacman.h"
#include "header/scoring.h"
#include "header/powerup.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    setTitikDot();
    spawnPowerUps();
    Ghost ghosts[MAX_GHOSTS];
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    Pacman pacman = {100, 100, 8, 0, 12};  // Pac-Man dengan 12 nyawa
    int score = 0;
    int page = 0;
    int key = 0;

    GameStart();

    while (1) {  // Game loop utama
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        Map();

        drawPowerUps();
        gambarDot();

        for (int i = 0; i < MAX_GHOSTS; i++) {
            shiftGhost(&ghosts[i]);
            designGhost(&ghosts[i]);
            pursuePacman(&ghosts[i], &pacman);
        }

        if (kbhit()) { 
            key = getch();
            if (key == 27)
                GamePause();
            if (key == 0 || key == 224)
                key = getch();
            movePacman(&pacman, key);

            scoring(pacman.x, pacman.y, &score);
            checkPowerUpCollision(pacman.x, pacman.y);
        }

        drawPacman(&pacman);
        hitungScore(score);
        updatePowerUpState();
    

        // Cek tabrakan dengan semua Ghosts
        for (int i = 0; i < MAX_GHOSTS; i++) {
            updatePacmanAfterCollision(&pacman, &ghosts[i]);
        }

        // Cek jika Pac-Man kehabisan nyawa
        if (pacman.lives <= 0) {
            printf("Game Over! Skor Akhir: %d\n", score);
            exit(0);
        }

        // Cek jika semua titik sudah dimakan
        if (allDotsEaten()) {
            printf("Selamat! Anda menang dengan skor: %d\n", score);
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
