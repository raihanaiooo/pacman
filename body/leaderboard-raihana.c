#include "../header/leaderboard.h"
#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>

void loadLeaderboard(Leaderboard entries[], int *count) {
    FILE *file = fopen("leaderboard.txt", "r");
    *count = 0;

    if (file == NULL) return;

    while (fscanf(file, "%s %d", entries[*count].name, &entries[*count].score) == 2) {
        (*count)++;
        if (*count >= MAX_ENTRIES) break;
    }

    fclose(file);
}

void saveLeaderboard(Leaderboard entries[], int count) {
    FILE *file = fopen("leaderboard.txt", "w");
    if (file == NULL) return;

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", entries[i].name, entries[i].score);
    }

    fclose(file);
}

void updateLeaderboard(const char *playerName, int score) {
    Leaderboard entries[MAX_ENTRIES + 1];
    int count;

    loadLeaderboard(entries, &count);

    // Cek apakah nama sudah ada
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(entries[i].name, playerName) == 0) {
            // Jika nama ditemukan dan skor baru lebih tinggi, update
            if (score > entries[i].score) {
                entries[i].score = score;
            }
            found = 1;
            break;
        }
    }

    // Kalau belum ditemukan, tambahkan entry baru
    if (!found && count < MAX_ENTRIES + 1) {
        strcpy(entries[count].name, playerName);
        entries[count].score = score;
        count++;
    }

    // Urutkan leaderboard (skor tertinggi dulu)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (entries[j].score > entries[i].score) {
                Leaderboard temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    // Batasi jumlah entri
    if (count > MAX_ENTRIES) count = MAX_ENTRIES;

    saveLeaderboard(entries, count);
}


void displayLeaderboard() {
    Leaderboard entries[MAX_ENTRIES];
    int count = 0;

    loadLeaderboard(entries, &count);
    char text1[] = "LEADERBOARD";
    char text2[] = "Press any key to return...";
    cleardevice();
    setbkcolor(BLACK);
    setcolor(YELLOW);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    outtextxy(250, 30, text1);

    setcolor(WHITE);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    int y = 100;

    for (int i = 0; i < count; i++) {
        char line[100];
        sprintf(line, "%d. %s - %d", i + 1, entries[i].name, entries[i].score);
        outtextxy(200, y, line);
        y += 40;
    }

    setcolor(LIGHTGREEN);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
    outtextxy(220, y + 50, text2);
    getch();
}