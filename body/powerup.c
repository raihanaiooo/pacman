#include "../header/powerup.h"
#include "../header/scoring.h"
#include "../header/ui.h"
#include <stdlib.h>
#include <time.h>

PowerUp powerUps[MAX_POWERUPS];  // Menyimpan beberapa Power-Up
int doublePointActive = 0;
clock_t doublePointTimer = 0;
extern int maze[24][32];

#define POWERUP_DURATION 10000  // Efek Double Score bertahan 5 detik

// Fungsi untuk menempatkan beberapa Power-Up di lokasi acak
void spawnPowerUps() {
    srand(time(NULL));
    for (int i = 0; i < MAX_POWERUPS; i++) {
        int row, col;
        int attempts = 0;

        do {
            row = rand() % ROWS;
            col = rand() % COLS;
            attempts++;

            if (attempts > 500) {  // Jika lebih dari 500 percobaan, hentikan pencarian
                printf("Gagal menemukan lokasi Power-Up setelah %d percobaan.\n", attempts);
                return;
            }

        } while (maze[row][col] != 0);  // Hanya spawn di area jalan (tidak menimpa dinding)

        // Jika Power-Up spawn di atas dot, hapus dot tersebut
        if (dots[row][col] == 1) {
            dots[row][col] = 0;  // Dot dihapus
            printf("Power-Up muncul di atas dot, dot dihapus di (%d, %d)\n", row, col);
        }

        powerUps[i].x = col * TILE_SIZE + TILE_SIZE / 2;
        powerUps[i].y = row * TILE_SIZE + TILE_SIZE / 2;
        powerUps[i].type = 1;  // ✅ Hanya Double Score
        powerUps[i].active = 1;  // Power-Up aktif
    }
}

// Fungsi untuk menggambar Power-Up yang masih ada di layar
void drawPowerUps() {
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (powerUps[i].active) {
            setcolor(RED);
            setfillstyle(SOLID_FILL, RED);
            fillellipse(powerUps[i].x, powerUps[i].y, 5, 5);
        }
    }
}

// Mengecek apakah Pac-Man mengambil salah satu Power-Up
void checkPowerUpCollision(int pacmanX, int pacmanY) {
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (powerUps[i].active) {  // Hanya cek power-up yang aktif
            int powerUpX = powerUps[i].x;
            int powerUpY = powerUps[i].y;

            // Jika Pac-Man berada di posisi power-up
            if (abs(pacmanX - powerUpX) < TILE_SIZE / 2 && abs(pacmanY - powerUpY) < TILE_SIZE / 2) {
                activatePowerUp(powerUps[i].type);  // Aktifkan efek Power-Up
                powerUps[i].active = 0;  // Power-Up dimatikan setelah dimakan
                printf("Power-Up dimakan di posisi (%d, %d)\n", pacmanX, pacmanY);
            }
        }
    }
}

// Fungsi untuk mengaktifkan efek Power-Up
void activatePowerUp(int type) {
    if (type == 1) {  // ✅ Double Score
        doublePointActive = 1;
        doublePointTimer = clock();  // Mulai hitung mundur
        printf("Double Score Aktif!\n");
    }
}

// Fungsi untuk menghapus efek Power-Up setelah durasi habis
void updatePowerUpState() {
    if (doublePointActive) {
        clock_t elapsedTime = (clock() - doublePointTimer) * 1000 / CLOCKS_PER_SEC;
        if (elapsedTime > POWERUP_DURATION) {
            doublePointActive = 0;
            printf("Efek Double Score berakhir.\n");
        }
    }
}
