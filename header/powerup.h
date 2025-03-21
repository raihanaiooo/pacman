#ifndef POWERUP_H
#define POWERUP_H

#include <time.h>

#define MAX_POWERUPS 5
#define POWERUP_DURATION 5000  // Durasi power-up dalam milidetik (5 detik)

typedef struct {
    int x, y;
    int active;
    int type;  // 1 = Double Score, 2 = Kebal, 3 = Freeze
} PowerUp;

// deklarasi variabel global yg dipakedi powerup.c
extern PowerUp powerUps[MAX_POWERUPS];
extern int doublePointActive;
extern int kebalActive;
extern int freezeActive;
extern clock_t doublePointTimer, kebalTimer, freezeTimer;

void spawnPowerUps();
void drawPowerUps();
void checkPowerUpCollision(int pacmanX, int pacmanY);
void updatePowerUpState();

#endif
