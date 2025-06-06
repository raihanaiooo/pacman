#include <graphics.h>
#include "../header/pause.h"
#include "../header/pacman.h"
#include "../header/ghost.h"

/* Variabel global */
int isPaused = 0;
int score = 0;
Pacman pacman;
Ghost ghosts[MAX_GHOSTS];

/** Procedure untuk mengaktifkan atau menonaktifkan mode pause **/
void togglePause() {
    isPaused = !isPaused;
}
/** Procedure untuk menggambar layar pause **/
void drawPauseScreen() {
    /* Mendapatkan dimensi layar */
    int screenWidth = getmaxx();
    int screenHeight = getmaxy();
    
    /* Menentukan ukuran dan posisi kotak pause */
    int boxWidth = 300;
    int boxHeight = 150;
    int boxX1 = (screenWidth - boxWidth) / 2;
    int boxY1 = (screenHeight - boxHeight) / 2;
    int boxX2 = boxX1 + boxWidth;
    int boxY2 = boxY1 + boxHeight;

    /* Menggambar kotak semi-transparan sebagai tampilan pause */
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(boxX1, boxY1, boxX2, boxY2);
    rectangle(boxX1, boxY1, boxX2, boxY2); // Kotak tepi
    
    // Teks pause
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    char teks1[] = "Game Paused";
    char teks2[] = "Press P to resume";
    char teks3[] = "Press Q to quit";
    
    /* Posisi tengah kotak */
    int centerX = (boxX1 + boxX2) / 2;
    int centerY = (boxY1 + boxY2) / 2;

    /* Tampilkan teks di tengah kotak */
    outtextxy(centerX - (textwidth(teks1) / 2) + 60, centerY - (textheight(teks1) / 2) - 10, teks1);
    outtextxy(centerX - (textwidth(teks2) / 2) + 75, centerY + (textheight(teks1) / 2), teks2);
    outtextxy(centerX - (textwidth(teks3) / 2) + 60, centerY + (textheight(teks1) / 2) + 30, teks3);

    setvisualpage(1);
}

/** Fungsi untuk menangani input tombol **/
void handleInput(char key, Pacman *pacman, Ghost ghosts[]) {
    if (key == 'P' || key == 'p') {
        togglePause();
        if (isPaused) {
            drawPauseScreen();
            setvisualpage(1);
            
            while (isPaused) {
                if (kbhit()) {
                    char newKey = getch();
                    if (newKey == 'p' || newKey == 'P') {
                        togglePause(); // Resume game
                        return;
                    } else if (newKey == 'q' || newKey == 'Q') {
                        isPaused = 0;
                        cleardevice();
                        
                        /* Reset semua variabel game */
                        pacman->x = 320;
                        pacman->y = 290;
                        pacman->lives = 3;
                        
                        setTitikDot();
                        spawnPowerUps();
                        
                        /* Tampilkan layar awal kembali */
                        PlaySound("sound/start.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                        GameStart();
                        PlaySound(NULL, NULL, 0);
                    }
                }
                delay(100);
            }
        }
    }
}