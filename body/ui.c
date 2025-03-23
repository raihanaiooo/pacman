#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include "../header/ui.h"
#include "../header/scoring.h"

#define TILE_SIZE 20
#define ROWS 24
#define COLS 32
// Deklarasi Array Labirin
int maze[ROWS][COLS] = {
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

// Prosedur untuk menggambar map
void Map() {
    int i, j;
    for (i = 0; i < ROWS; i++) {  // Baris
        for (j = 0; j < COLS; j++) {  // Kolom
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

// Prosedur untuk menghitung skor  ~Fathi
void hitungScore(int score, int x, int y, int isWin) {
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    char scoreText[30];
    sprintf(scoreText, isWin ? "FINAL SCORE: %d" : "SCORE: %d", score);
    outtextxy(x, y, scoreText);
}

// Prosedur untuk menampilkan tampilan awal
void GameStart() {
    char title[] = "PAC-MAN";
    char author[] = "1B - GROUP 2";
    char instruction[] = "PRESS SPACE TO PLAY THE GAME!";

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 7);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(YELLOW);
    outtextxy(320, 150, title);

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    outtextxy(320, 200, author);

    while (1) {
        setcolor(WHITE);
        outtextxy(320, 380, instruction);
        delay(500);

        setcolor(BLACK);
        outtextxy(320, 380, instruction);
        delay(500);

        if (kbhit()) {
            char key = getch();
            if (key == 32) break;  // Space key
        }
    }
    cleardevice();
}

// Prosedur untuk menampilkan kemenangan
void GameWin() {
    char win[] = "CONGRATULATIONS! YOU HAVE WIN THE GAME!";
    cleardevice();  // Bersihkan layar
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(YELLOW);
    outtextxy(320, 240, win);

    PlaySound("sound/pacman_AwvgsBv.wav", NULL, SND_FILENAME | SND_ASYNC);
    delay(3000);  // Biarkan layar menampilkan pesan kemenangan selama 3 detik
}

// Fungsi untuk menghitung dots
int countDotsAndPowerUps() {
    int count = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (dots[i][j] == 1) count++;  // dots[] assumed declared elsewhere
        }
    }
    return count;
}

// Prosedur untuk menampilkan game over
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

    while (1) {
        if (kbhit()) {
            char key = getch();
            if (key == 'r' || key == 'R') return 1;  // Restart
            if (key == 'q' || key == 'Q') return 0;  // Quit
        }
        delay(100);
    }
}

// Prosedur untuk menampilkan nyawa ke layar
void displayLives(Pacman *pacman) {
    int startX = 295;
    int y = 20;
    int size = 8;

    for (int i = 0; i < pacman->lives; i++) {
        int x = startX + (i * 25);

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        fillellipse(x - size / 2, y, size / 2, size / 2);
        fillellipse(x + size / 2, y, size / 2, size / 2);

        int heartPoints[] = {
            x - size, y,
            x + size, y,
            x, y + size + 4
        };
        fillpoly(3, heartPoints);
    }
}
