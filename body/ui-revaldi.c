#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include "../header/ui.h"
#include "../header/leaderboard.h"
#include "../header/scoring.h"
#include "../header/powerup.h"

#define TILE_SIZE 20
#define ROWS 24
#define COLS 32

Life *lives = NULL; // Pointer ke nyawa

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
    {2,2,2,2,2,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,2,2,2,2},
    {2,2,2,2,2,2,0,2,0,2,2,0,2,2,2,0,0,2,2,2,0,2,2,0,2,0,2,2,2,2,2,2},
    {0,0,0,0,0,0,0,0,0,2,2,0,2,0,0,0,0,0,0,2,0,2,2,0,0,0,0,0,0,0,0,0}, //TENGAHHH
    {2,2,2,2,2,2,0,2,0,2,2,0,2,0,0,0,0,0,0,2,0,2,2,0,2,0,2,2,2,2,2,2},
    {2,2,2,2,2,2,0,2,0,2,2,0,2,2,2,2,2,2,2,2,0,2,2,0,2,0,2,2,2,2,2,2},
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
    char leaderboardHint[] = "PRESS 'L' TO SHOW/HIDE LEADERBOARD";
    char guideHint[] = "PRESS 'G' FOR GUIDE";
    int leaderboardVisible = 0;

    while (1) {
        cleardevice();
        settextstyle(GOTHIC_FONT, HORIZ_DIR, 7);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        setcolor(YELLOW);
        outtextxy(320, 100, title);

        settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
        outtextxy(320, 145, author);

        settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
        setcolor(LIGHTCYAN);
        outtextxy(320, 195, leaderboardHint);

        if (leaderboardVisible) {
            displayLeaderboard();
        }

        setcolor(WHITE);
        outtextxy(320, 420, instruction);

        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        setcolor(WHITE);
        outtextxy(320, 450, guideHint);

        // Cek input
        if (kbhit()) {
            char key = getch();
            if (key == 32) break; // Space untuk mulai
            if (key == 'l' || key == 'L') leaderboardVisible = !leaderboardVisible; // Tampilkan leaderboard
            if (key == 'g' || key == 'G') GuideScreen();  // Tampilkan panduan
        }
        delay(100);
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
    char name[50] = "";
    int nameIndex = 0;

    cleardevice();

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(RED);
    outtextxy(320, 100, gameOverText);

    sprintf(finalScoreText, "FINAL SCORE: %d", score);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(320, 150, finalScoreText);

    // Input nama pemain
    setcolor(LIGHTCYAN);
    char text[] = "ENTER YOUR NAME";
    outtextxy(320, 200, text);

    while (1) {
        setcolor(WHITE);
        settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
        // outtextxy(320, 230, "                         ");  // clear line
        outtextxy(320, 230, name);

        if (kbhit()) {
            char ch = getch();
            if (ch == 13) break;  // ENTER untuk konfirmasi nama
            else if (ch == 8 && nameIndex > 0) {
                nameIndex--;
                name[nameIndex] = '\0';
            }
            else if (nameIndex < 20 && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
                name[nameIndex++] = ch;
                name[nameIndex] = '\0';
            }
        }
        delay(100);
    }

    // Simpan ke leaderboard
    updateLeaderboard(name, score);

    // Tampilkan instruksi lanjut
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

void GuideScreen() {
    cleardevice();
    setbkcolor(BLACK);

    char title[] = "HOW TO PLAY";
    char satu[]= "1. Gunakan ARROW KEY untuk menggerakkan Pac-Man.";
    char dua[]= "2. Makan semua DOT (titik putih) untuk menang.";
    char tiga[]= "3. Hindari Ghost! Jika tertangkap, nyawa berkurang.";
    char empat[]= "4. Ambil POWER-UP untuk efek spesial:";
    char powerUp1[] = "- Double Score: Skor dobel sementara";
    char powerUp2[] = "- Kebal: Pac-Man kebal dari Ghost";
    char powerUp3[] = "- Freeze: Ghost berhenti bergerak sementara";
    char lima[] = "5. Tekan 'P' untuk pause, 'Q' untuk keluar.";
    char kembali[] = "Tekan SPACE untuk kembali ke menu";

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    setcolor(YELLOW);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(320, 60, title);

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);

    int y = 120;
    outtextxy(320, y, satu);
    y += 35;
    outtextxy(320, y, dua);
    y += 35;
    outtextxy(320, y, tiga);
    y += 35;
    outtextxy(320, y, empat);
    y += 30;
    setcolor(YELLOW);
    outtextxy(340, y, powerUp1);
    y += 25;
    setcolor(RED);
    outtextxy(340, y, powerUp2);
    y += 25;
    setcolor(BLUE);
    outtextxy(340, y, powerUp3);
    y += 35;
    setcolor(WHITE);
    outtextxy(320, y, lima);

    y += 50;
    setcolor(YELLOW);
    outtextxy(320, y, kembali);

    // Tunggu sampai user menekan SPACE
    while (1) {
        if (kbhit() && getch() == 32) break;
        delay(50);
    }
    cleardevice();
}

Life* createLife(int x, int y) {
    Life *newLife = (Life *)malloc(sizeof(Life));
    newLife->x = x;
    newLife->y = y;
    newLife->next = NULL;
    return newLife;
}

void addLife(Life **head, int x, int y) {
    Life *newLife = createLife(x, y);
    newLife->next = *head;
    *head = newLife;
}

void removeLife(Life **head) {
    if (*head == NULL) return;
    Life *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void drawLives(Life *head) {
    Life *current = head;
    while (current != NULL) {
        int x = current->x;
        int y = current->y;
        // Warna hati
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        // Gambar dua lingkaran atas hati
        fillellipse(x - 5, y - 5, 5, 5); // Lingkaran kiri
        fillellipse(x + 5, y - 5, 5, 5); // Lingkaran kanan
        // Gambar segitiga bawah hati
        int points[] = {x - 10, y - 5, x + 10, y - 5, x, y + 10, x - 10, y - 5};
        fillpoly(4, points);

        current = current->next;
    }
}

void initLives() {
    // Tambahkan 3 nyawa di posisi tertentu (misalnya, di pojok kiri atas layar)
    addLife(&lives, 295, 25);  // Nyawa pertama
    addLife(&lives, 320, 25);  // Nyawa kedua
    addLife(&lives, 345, 25);  // Nyawa ketiga
}

void displayPowerUpInfo() {
    if (activePowerUpType > 0 && powerUpCountdown > 0) {
        char infoText[50];
        char countdownText[20];

        // Tentukan nama power-up berdasarkan jenisnya
        switch (activePowerUpType) {
            case 1: sprintf(infoText, "Power-Up: Double Score"); break;
            case 2: sprintf(infoText, "Power-Up: Kebal"); break;
            case 3: sprintf(infoText, "Power-Up: Freeze"); break;
            default: sprintf(infoText, "Power-Up: Unknown"); break;
        }

        // Tampilkan waktu sisa
        sprintf(countdownText, "Time Left: %d s", powerUpCountdown);

        // Gambar teks di layar
        setcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(200, 476, infoText);        // Info power-up
        outtextxy(400, 476, countdownText);  // Countdown
    }
}