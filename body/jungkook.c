#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header/pacman.h"
#include "header/ghost.h"

static time_t lastCollisionTime = 0;

// Fungsi untuk mengecek tabrakan antara Pac-Man dan Ghost
int checkCollisionWithGhost(Pacman *pacman, Ghost *ghost) {
    return (abs(pacman->x - ghost->x) < 10 && abs(pacman->y - ghost->y) < 10);
}

// Fungsi untuk mengurangi nyawa Pac-Man jika bertabrakan dengan Ghost
void updatePacmanAfterCollision(Pacman *pacman, Ghost *ghost) {
    time_t now = time(NULL);

    // Jika ini adalah awal permainan, beri jeda sebelum collision pertama kali
    if (lastCollisionTime == 0) {
        lastCollisionTime = now;
        return;  
    }

    // Pastikan Pac-Man tidak langsung mati sebelum bergerak
    if (checkCollisionWithGhost(pacman, ghost) && now - lastCollisionTime > 1) {  
        pacman->lives--;  
        pacman->x = 200;  
        pacman->y = 200;
        lastCollisionTime = now;
        printf("Pac-Man terkena Ghost! Nyawa tersisa: %d\n", pacman->lives);
    }
}
