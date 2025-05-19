#include "../header/powerup.h"
#include "../header/scoring.h"
#include "../header/Revaldi.h"
#include <stdlib.h>
#include <time.h>

PowerUp powerUps[MAX_POWERUPS];  // Menyimpan beberapa Power-Up
extern int maze[24][32];
int doublePointActive = 0;
int kebalActive = 0;
int freezeActive = 0;
int activePowerUpType = 0;
int powerUpCountdown = 0;
clock_t doublePointTimer = 0;
clock_t kebalTimer = 0;
clock_t freezeTimer = 0;

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
      powerUps[i].type = (rand() % 3) + 1;  // 1 = Double Score, 2 = Kebal, 3 = Freeze
      powerUps[i].active = 1;  // Power-Up aktif
  }
}


// Fungsi untuk menggambar Power-Up yang masih ada di layar
#include <graphics.h>  // Pastikan untuk menggambar menggunakan graphics.h

void drawPowerUps() {
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (powerUps[i].active) {
            // Pilih warna berdasarkan jenis Power-Up
            switch (powerUps[i].type) {
                case 1: setcolor(YELLOW); setfillstyle(SOLID_FILL, YELLOW); break;  // ✅ Double Score → Kuning
                case 2: setcolor(RED); setfillstyle(SOLID_FILL, RED); break;        // ✅ Kebal → Merah
                case 3: setcolor(LIGHTBLUE); setfillstyle(SOLID_FILL, LIGHTBLUE); break; // ✅ Freeze → Biru Muda
                default: setcolor(WHITE); setfillstyle(SOLID_FILL, WHITE); break;  // Default → Putih
            }

            // Gambar power-up sebagai lingkaran kecil
            fillellipse(powerUps[i].x, powerUps[i].y, 5, 5);
        }
    }
}


// Mengecek apakah Pac-Man mengambil salah satu Power-Up
void checkPowerUpCollision(int pacmanX, int pacmanY) {
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (powerUps[i].active) {
            int powerUpX = powerUps[i].x;
            int powerUpY = powerUps[i].y;

            if (abs(pacmanX - powerUpX) < TILE_SIZE / 2 && abs(pacmanY - powerUpY) < TILE_SIZE / 2) {
                // Aktifkan efek sesuai tipe Power-Up
                activePowerUpType = powerUps[i].type;
                powerUpCountdown = POWERUP_DURATION / 1000; // Set countdown dalam detik

                if (powerUps[i].type == 1) {
                    doublePointActive = 1;
                    doublePointTimer = clock();
                    printf("Double Score Aktif!\n");
                } else if (powerUps[i].type == 2) {
                    kebalActive = 1;
                    kebalTimer = clock();
                    PlaySound("sound/eatghost.wav", NULL, SND_FILENAME | SND_ASYNC);
                    printf("Pac-Man sekarang kebal terhadap Ghost!\n");
                } else if (powerUps[i].type == 3) {
                    freezeActive = 1;
                    freezeTimer = clock();
                    printf("Ghost sekarang beku!\n");
                }

                powerUps[i].active = 0;  // Hapus Power-Up dari layar setelah dimakan
            }
        }
    }
}



// Fungsi untuk menghapus efek Power-Up setelah 10 detik
void updatePowerUpState() {
    clock_t elapsedTime;

    if (doublePointActive) {
        elapsedTime = (clock() - doublePointTimer) * 1000 / CLOCKS_PER_SEC;
        if (elapsedTime > POWERUP_DURATION) {
            doublePointActive = 0;
            activePowerUpType = 0; // Nonaktifkan power-up
            printf("Efek Double Score berakhir.\n");
        }
    }

    if (kebalActive) {
        elapsedTime = (clock() - kebalTimer) * 1000 / CLOCKS_PER_SEC;
        if (elapsedTime > POWERUP_DURATION) {
            kebalActive = 0;
            activePowerUpType = 0; // Nonaktifkan power-up
            printf("Efek Kebal berakhir.\n");
        }
    }

    if (freezeActive) {
        elapsedTime = (clock() - freezeTimer) * 1000 / CLOCKS_PER_SEC;
        if (elapsedTime > POWERUP_DURATION) {
            freezeActive = 0;
            activePowerUpType = 0; // Nonaktifkan power-up
            printf("Efek Freeze berakhir.\n");
        }
    }

    // Kurangi countdown setiap detik
    static clock_t lastUpdate = 0;
    if ((clock() - lastUpdate) * 1000 / CLOCKS_PER_SEC >= 1000) {
        if (powerUpCountdown > 0) {
            powerUpCountdown--;
        }
        lastUpdate = clock();
    }
}