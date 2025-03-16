#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include "../header/ui.h"

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
    void hitungScore(int score) {
        setcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        char totalScore[20];
        sprintf(totalScore, "Score: %d", score);
        outtextxy(40, getmaxy() - 5, totalScore); // Pojok kiri bawah
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
    PlaySound(NULL, NULL, 0);
    cleardevice(); // Clear the screen
}

void GamePause() {
    // Menampilkan teks pause di halaman yang sedang ditampilkan
    int page =  0;
    setvisualpage(page);
    setactivepage(1 - page);  // Gunakan halaman yang tidak terlihat
    char pause[] = "PAUSED - Press SPACE to continue";

    setcolor(WHITE);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    outtextxy(200, 200, pause);

    while (1) { 
        if (kbhit()) { 
            char key = getch(); 
            if (key == 32){ // Jika SPACE ditekan, keluar dari pause
                setvisualpage(page);
                setactivepage(page);
            }
        }
    }
}