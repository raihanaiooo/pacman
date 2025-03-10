#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include "header/ui.h"
#include "header/ghost.h"
#include "header/pacman.h"
#include "header/scoring.h"
#include "header/powerup.h"

// ! COMPILE
// ! g++ main.c body/pacman.c body/pacman-seruni.c body/powerup.c body/ui.c body/ghost.c body/scoring.c -o pacman.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    clock_t lastMoveTime = 0;  // Menyimpan waktu terakhir Pac-Man bergerak
    const int moveDelay = 100; // Delay pergerakan dalam milidetik (0.1 detik)
    int lastKey = 0;           // Variabel untuk menyimpan input terakhir
    clock_t currentTime = clock();

    setTitikDot(); // Inisialisasi titik-titik
    spawnPowerUps();

<<<<<<< HEAD
    Ghost ghosts[MAX_GHOSTS];
    int ghostStepCounter[MAX_GHOSTS] = {0};  // Step counter untuk setiap Ghost
    const int ghostSpeed = 3;  // Ghost hanya bergerak setiap 2 frame Pac-Man
    theGhost(&ghosts[0], 320, 240, RED);
    theGhost(&ghosts[1], 330, 240, WHITE);
    theGhost(&ghosts[2], 310, 240, GREEN);
    theGhost(&ghosts[3], 340, 240, CYAN);

    Pacman pacman = {190, 190, 8, 0, 3}; // Pac-Man dengan 3 nyawa
=======
    Pacman pacman = {200, 200, 10, 0, 2};  // Pac-Man dengan 3 nyawa
>>>>>>> ae7106c (Menyimpan perubahan lokal sebelum pull)
    int score = 0;
    int page = 0;
    int key = 0;

    PlaySound("sound/start.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // * puter music
    GameStart(); // Tampilan awal
    PlaySound(NULL, NULL, 0);  // suara ilang pas mulai main
    while (pacman.lives > 0)
    {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        Map();

        drawPowerUps();
        gambarDot();

        

        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (ghostStepCounter[i] % ghostSpeed == 0) {
                moveGhost(&ghosts[i], &pacman);
            }
            designGhost(&ghosts[i]);
            ghostStepCounter[i]++;  // Tambahkan step counter untuk Ghost ini
        }
         

        // for (int i = 0; i < MAX_GHOSTS; i++) {
        //     shiftGhost(&ghosts[i]);
        //     designGhost(&ghosts[i]);
        //     if (!doublePointActive) {
        //         pursuePacman(&ghosts[i], &pacman); // Hantu mengejar Pac-Man jika tidak dalam power-up
        //     }
        // }

        clock_t currentTime = clock();

        // Tangkap input keyboard jika ada
        if (kbhit()) {
            int newKey = getch();
            if (newKey == 0 || newKey == 224) newKey = getch();  // Tangkap arrow keys
            key = newKey;  // Simpan input terakhir
        }
        
        // Pastikan Pac-Man hanya bisa bergerak setiap interval waktu tertentu
        if ((currentTime - lastMoveTime) * 1000 / CLOCKS_PER_SEC >= moveDelay) {
            if (key) {
                movePacman(&pacman, key, &score);
            } else {
                autoMovePacman(&pacman, &score);
            }
            lastMoveTime = currentTime;  // Update waktu terakhir pergerakan
        }
        
        
        autoMovePacman(&pacman, &score);
        drawPacman(&pacman);
        hitungScore(score);
        updatePowerUpState();

        // for (int i = 0; i < MAX_GHOSTS; i++) {
        //     if (!doublePointActive && checkCollisionWithGhost(&pacman, &ghosts[i])) {
        //         pacman.lives--;
        //         pacman.x = 200;
        //         pacman.y = 200;
        //     }
        // }

        // if (pacman.lives <= 0) {
        //     printf("Game Over! Skor Akhir: %d\n", score);
        //     GameOver();
        //     break;
        // }

        if (GetAsyncKeyState(VK_ESCAPE))
            break;

        delay(50);
        page = 1 - page;
    }

    closegraph();
    return 0;
}
