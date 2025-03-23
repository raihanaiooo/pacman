#ifndef PAUSE_H
#define PAUSE_H

#include <stdbool.h>
#include "../header/pacman.h"
#include "../header/ghost.h"
#include "../header/powerup.h"
#include "../header/ui.h"
#include "../header/scoring.h"

/* Import struct, fungsi, dan procedure */
extern void gambarDot();
extern void Map();
extern void drawPowerUps();
/** Variabel global yang menyimpan status permainan (pause/tidak) **/
extern int isPaused;
extern Pacman pacman;
/** Variabel global untuk menyimpan skor pemain **/
extern int score;
extern Ghost ghosts[MAX_GHOSTS];

/* Deklarasi procedure */
/** Procedure untuk mengaktifkan atau menonaktifkan mode pause **/ 
void togglePause();
/** Procedure untuk menggambar layar pause **/
void drawPauseScreen();
/** Procedure untuk menjalankan permainan dalam loop **/
void gameLoop();
/** Procedure untuk menangani input dari pemain **/
void handleInput(char key, Pacman *pacman, Ghost ghosts[]);

#endif