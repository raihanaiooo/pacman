#ifndef PACMAN_LIVES_H
#define PACMAN_LIVES_H

#include "ghost.h"
#include "pacman.h"

void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts);
int handleGameOver(Pacman *pacman);

#endif
