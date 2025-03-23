#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include "../header/ui.h"
#include "../header/scoring.h"

#define TILE_SIZE 20

int maze[24][32] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,2,2,2,2,0,2,2,2,2,0,2,0,0,2,2,0,0,2,0,2,2,2,2,0,2,2,2,2,0,2},
    {2,0,2,2,2,2,0,2,2,2,2,0,2,2,0,2,2,0,2,2,0,2,2,2,2,0,2,2,2,2,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,2,2,2,2,0,2,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,2,0,2,2,2,2,0,2},
    {2,0,2,2,2,2,0,2,0,2,2,2,2,2,0,2,2,0,2,2,2,2,2,0,2,0,2,2,2,2,0,2},
    {2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,2,2,2},
    {0,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0},
    {2,2,2,2,2,2,0,2,0,2,2,0,2,2,2,0,0,2,2,2,0,2,2,0,2,0,2,2,2,2,2,2},
    {0,0,0,0,0,0,0,0,0,2,2,0,2,0,0,0,0,0,0,2,0,2,2,0,0,0,0,0,0,0,0,0}, //TENGAHHH
    {2,2,2,2,2,2,0,2,0,2,2,0,2,0,0,0,0,0,0,2,0,2,2,0,2,0,2,2,2,2,2,2},
    {0,0,0,0,0,2,0,2,0,2,2,0,2,2,2,2,2,2,2,2,0,2,2,0,2,0,2,0,0,0,0,0},
    {2,2,2,2,2,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,0,0,0,0,0,0,2},
    {2,0,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,0,2},
    {2,0,0,0,2,0,2,2,0,0,2,2,2,0,0,2,2,0,2,0,0,2,0,2,2,2,0,2,0,0,0,2},
    {2,2,2,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,2,0,0,0,0,2,0,2,0,2,2,2},
    {2,0,0,0,2,0,0,2,0,0,2,2,2,0,0,2,2,0,2,2,0,0,0,2,2,2,0,2,0,0,0,2},
    {2,0,2,2,2,0,0,2,0,0,2,0,0,2,0,2,2,0,2,0,2,0,0,2,0,0,0,2,2,2,0,2},
    {2,0,0,0,0,0,2,2,2,0,2,2,2,0,0,0,0,0,2,0,0,2,0,2,2,2,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
};

// Fungsi untuk menggambar map berdasarkan array
void Map() {
    int i, j;
    for (i = 0; i < 24; i++) {  // Baris
        for (j = 0; j < 32; j++) {  // Kolom
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            if (maze[i][j] == 2) {  // Dinding
                setcolor(BLUE);
                setfillstyle(SOLID_FILL, BLUE);
                bar(x, y, x + TILE_SIZE, y + TILE_SIZE);
            }else if (maze[i][j] == 0) {  // Jalan
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                bar(x, y, x + TILE_SIZE, y + TILE_SIZE);
            }
        }
    }
}
        //* ====================================hitung score======================================= FATHI
void hitungScore(int score, int x, int y, int isWin) {
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    char totalScore[30];

    if (isWin) {
        sprintf(totalScore, "FINAL SCORE: %d", score);
    } else {
        sprintf(totalScore, "SCORE: %d", score);
    }

    outtextxy(x, y, totalScore);  // Cetak di lokasi yang benar
}

void GameStart() {
    char start[] = "PRESS SPACE TO PLAY THE GAME!";
    char pacman[] = "PAC-MAN";
    char author[] = "1B - Kelompok 2";

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 7);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(YELLOW);
    outtextxy(320, 150, pacman);

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(YELLOW);
    outtextxy(320, 200, author);
    
    while (1) { // Loop terus berjalan
        settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        setcolor(WHITE);
        outtextxy(320, 380, start);
        delay(500);

        setcolor(BLACK);
        outtextxy(320, 380, start);
        delay(500);

        if (kbhit()){
            char key = getch();
            if (key == 32) break;
        }
    }

    cleardevice(); // Clear the screen
}

void GameWin() {
    char win[] = "SELAMAT TELAH MENAMATKAN PAC-MAN!";
    cleardevice();  // Bersihkan layar
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(YELLOW);
    outtextxy(320, 240, win);

    PlaySound("sound/pacman_AwvgsBv.wav", NULL, SND_FILENAME | SND_ASYNC);
    delay(3000);  // Biarkan layar menampilkan pesan kemenangan selama 3 detik
}

int countDotsAndPowerUps() {
    int count = 0;
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 32; j++) {
            if (dots[i][j] == 1) {  // Pastikan menghitung dari array dots
                count++;
            }
        }
    }
    return count;
}

int GameOver(int score) {
    char gameOverText[] = "GAME OVER!";
    char finalScoreText[30];
    char playAgainText[] = "PRESS 'R' TO PLAY AGAIN OR 'Q' TO QUIT";

    // Bersihkan layar
    cleardevice();

    // Tampilkan teks "GAME OVER"
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(RED);
    outtextxy(320, 150, gameOverText);

    // Tampilkan skor akhir
    sprintf(finalScoreText, "FINAL SCORE: %d", score);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(320, 200, finalScoreText);

    // Tampilkan pilihan untuk bermain lagi atau keluar
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
    setcolor(YELLOW);
    outtextxy(320, 300, playAgainText);

    // Tunggu input dari pemain
    while (1) {
        if (kbhit()) {
            char key = getch();
            if (key == 'r' || key == 'R') {
                return 1; // Restart
            } else if (key == 'q' || key == 'Q') {
                return 0; // Quit
            }
        }
        delay(100);
    }
}

void displayLives(Pacman *pacman) {
    int startX = 295;
    for (int i = 0; i < pacman->lives; i++) {
        int x = startX + (i * 25); // Jarak antar love agak longgar biar rapi
        int y = 20;
        int size = 8;

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        fillellipse(x - size / 2, y, size / 2, size / 2);
        fillellipse(x + size / 2, y, size / 2, size / 2);

        // Bagian bawah (segitiga)
        int points[] = {
            x - size, y,
            x + size, y,
            x, y + size + 4
        };
        fillpoly(3, points);
    }
}