#include "../header/powerup.h"
#include "../header/scoring.h"
#include "../header/ui.h"
#include <stdlib.h>
#include <time.h>

PowerUp powerUps[MAX_POWERUPS];  // Menyimpan beberapa Power-Up
int doublePointActive = 0;
clock_t doublePointTimer = 0;
extern int maze[24][32];

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
        if (powerUps[i].active && abs(pacmanX - powerUps[i].x) < 10 && abs(pacmanY - powerUps[i].y) < 10) {
            powerUps[i].active = 0;  // Hapus Power-Up setelah diambil
            doublePointActive = 1;   // Aktifkan efek Power-Up
            doublePointTimer = clock();
            printf("Pac-Man mengambil Power-Up! Efek aktif selama 10 detik.\n");
        }
    }
}

// Fungsi untuk menghapus efek Power-Up setelah 10 detik
void updatePowerUpState() {
    if (doublePointActive) {
        clock_t elapsedTime = (clock() - doublePointTimer) * 1000 / CLOCKS_PER_SEC;
        if (elapsedTime > POWERUP_DURATION) {
            doublePointActive = 0; // Efek Double Point selesai
            printf("Efek Power-Up berakhir, skor kembali normal.\n");
        }
    }
}
