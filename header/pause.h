#ifndef PAUSE_H
#define PAUSE_H

#include <stdbool.h>
#include "../header/pacman.h"
#include "../header/ghost.h"
#include "../header/powerup.h"
#include "../header/ui.h"
#include "../header/scoring.h"

extern void gambarDot();
extern void Map();
extern void drawPowerUps();
extern int isPaused;
extern Pacman pacman;
extern int score;
extern Ghost ghosts[MAX_GHOSTS];

void togglePause();
void drawPauseScreen();
void gameLoop();
void handleInput(char key);

#endif