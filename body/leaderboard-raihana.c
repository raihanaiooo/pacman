#include "../header/leaderboard.h"
#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>

void loadLeaderboard(Leaderboard entries[], int *count) {
    FILE *file = fopen("leaderboard.txt", "r");
    *count = 0; // Inisialisasi jumlah entri yang dibaca menjadi 0

    if (file == NULL) return;

    // Baca nama dan skor dari file selama berhasil dan belum melebihi kapasitas maksimal
    while (fscanf(file, "%s %d", entries[*count].name, &entries[*count].score) == 2) {
        (*count)++; // Tambah jumlah entri yang berhasil dibaca
        if (*count >= MAX_ENTRIES) break;  // Hentikan jika sudah mencapai batas maksimal entri
    }

    fclose(file);
}


void saveLeaderboard(Leaderboard entries[], int count) {
    FILE *file = fopen("leaderboard.txt", "w");
    if (file == NULL) return;

    // Tulis setiap entri nama dan skor ke file, satu per baris
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", entries[i].name, entries[i].score);
    }

    fclose(file);
}

void updateLeaderboard(const char *playerName, int score) {
    Leaderboard entries[MAX_ENTRIES + 1];
    int count;

    loadLeaderboard(entries, &count);

    // Tambahkan entry baru
    if (count < MAX_ENTRIES + 1) {
        strcpy(entries[count].name, playerName);
        entries[count].score = score;
        count++;
    }

    // Urutkan leaderboard berdasarkan skor tertinggi dulu
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (entries[j].score > entries[i].score) {
                Leaderboard temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    // Batasi jumlah entri maksimum
    if (count > MAX_ENTRIES) count = MAX_ENTRIES;

    saveLeaderboard(entries, count);
}

void displayLeaderboard() {
    Leaderboard entries[MAX_ENTRIES];
    int count = 0;

    loadLeaderboard(entries, &count);
    char text1[] = "LEADERBOARD";
    setcolor(YELLOW);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    outtextxy(320, 235, text1); // Atur posisi agar tidak menutupi judul utama

    setcolor(WHITE);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    int y = 270;

    // Loop untuk menampilkan setiap entri leaderboard
    for (int i = 0; i < count; i++) {
        char line[100];
        sprintf(line, "%d. %s - %d", i + 1, entries[i].name, entries[i].score); // Format entri ke dalam string
        outtextxy(320, y, line); // Atur posisi X agar rata tengah
        y += 25; // Geser posisi vertikal untuk entri berikutnya
    }
}