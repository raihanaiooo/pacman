#ifndef POWERUP_H
#define POWERUP_H

#include <graphics.h>
#include <time.h>

#define MAX_POWERUPS 3   // Jumlah Power-Up dalam game
#define POWERUP_DURATION 10000  // 10 detik dalam milidetik

typedef struct {
    int x, y;        // Posisi Power-Up
    int active;      // 1 jika aktif, 0 jika sudah diambil
} PowerUp;

extern PowerUp powerUps[MAX_POWERUPS];
extern int doublePointActive;
extern clock_t doublePointTimer;

void spawnPowerUps();
void drawPowerUps();
void checkPowerUpCollision(int pacmanX, int pacmanY);
void updatePowerUpState();
// int powerUpKosong(int i, int j);

#endif
