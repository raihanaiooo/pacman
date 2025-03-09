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
    theGhost(&ghost, 100, 100, RED);  // Buat ghost merah di (100,100)

    Pacman pacman = {200, 200, 10, 0, 1};  // Pac-Man dengan 3 nyawa
    int score = 0;
    int page = 0;
    int key = 0;

    // MAIN STRUCTURE 
    while (pacman.lives > 0) {  // Game berjalan selama Pac-Man masih punya nyawa
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        map();
        
        //* ====================================DOT=======================================
        drawDots();

        //* ====================================GHOST=======================================
        designGhost(&ghost);
        shiftGhost(&ghost, getmaxx(), getmaxy());

        //* ====================================PACMAN=======================================
        if (kbhit()) { 
            key = getch();
            if (key == 27)
                break;
            if (key == 0 || key == 224)
                key = getch();
            movePacman(&pacman, key);

            checkCollisionWithDots(pacman.x, pacman.y, &score); // Cek dot kemakan
        }

        drawPacman(&pacman);

        // Cek jika Pac-Man bertabrakan dengan Ghost
        if (checkCollisionWithGhost(&pacman, &ghost)) {
            pacman.lives--; // Kurangi nyawa
            pacman.x = 200;  // Reset posisi Pac-Man
            pacman.y = 200;
            printf("Pac-Man terkena Ghost! Nyawa tersisa: %d\n", pacman.lives);
        }

        if (pacman.lives <= 0) {
            printf("Game Over! Skor Akhir: %d\n", score);
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
