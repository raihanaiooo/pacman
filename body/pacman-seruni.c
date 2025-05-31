#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include "../header/pacman.h"
#include "../header/ghost.h"
#include "../header/scoring.h"
#include "../header/ui.h"
#include "../header/powerup.h"

#include "../header/pacman.h"
 
// ADDED: Bangun circular linked list frame mulut Pac‑Man
void initPacmanAnimation(Pacman *p) {
int angles[][2] = {{30,330},{45,315},{60,300},{75,285}};
Frame *head = NULL, *prev = NULL;
for (int i = 0; i < 4; i++) {
    Frame *f = (Frame*)malloc(sizeof(Frame));
    f->start_angle = angles[i][0];
    f->end_angle   = angles[i][1];
    f->next = NULL;
    if (!head) head = f;
    if (prev) prev->next = f;
    prev = f;
 }
 prev->next = head;

// simpan head &current di struct Pacman 
p->frameHead    = head;
p->currentFrame = head;
}



// generic helper: hapus, reset pos, gambar ulang 
void resetEntity(void *ent, ClearFunc clearF, DrawFunc drawF,int *xPtr, int *yPtr,int initX, int initY) {
    clearF(ent); // hapus tampilan lama 
    *xPtr = initX; // reset x ke posisi awal 
    *yPtr = initY; // reset y ke posisi awal 
    drawF(ent); // menggambar ulang di posisi awal 
}

// menghapus ghost dengan menggambar lingkaran hitam di posisi lama 
void clearGhost(void *gh_void) {
    Ghost *gh = (Ghost *)gh_void; 
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(gh->x, gh->y, gh->radius, gh->radius);
}

// Prosedur resetPacman: menghapus tampilan pacman lama, mereset posisinya, dan menggambarnya ulang
void resetPacman(Pacman *p) {
    resetEntity(p,
                (ClearFunc)clearPacman, 
                (DrawFunc)drawPacman,
                &p->x, &p->y,p->initialX, p->initialY); // alamat koordinat pacman
}

void resetGhost(GhostNode *node) {
    Ghost *gh = &node->ghost;

    resetEntity(gh,
                (ClearFunc)clearGhost,
                (DrawFunc)drawGhostWithEffect,
                &gh->x, &gh->y,
                gh->initialX, gh->initialY);

    node->isScared = 0;
    node->scaredTimer = 0;
}

// Fungsi handle game over
int handleGameOver(Pacman *pacman, int *score, GhostNode *node, int numGhosts) {
    int playAgain = GameOver(*score);
    if (playAgain) {
        // Reset seluruh game state
        resetPacman(pacman);

        Ghost *g = &node->ghost;

        for (int i = 0; i < numGhosts; i++) {
            resetGhost(node);
        }
        *score = 0;
        pacman->lives = 3;
        setTitikDot();     // Reset dots
        spawnPowerUps();   // Reset power-ups
        return 1; // Main lagi
    } else {
        closegraph();
        exit(0);
    }
}

// Prosedure respawn pacman 
void updatePacmanAfterCollision(Pacman *pacman, GhostNode *node, int numGhosts, int *score) {
    pacman->lives--; // mengurangi nyawa 
    
    if (pacman->lives > 0) {
    
        resetPacman(pacman);
        
        for (int i = 0; i < numGhosts; i++){
            CollisionWithGhost(pacman, node);  
        }
   
    }
}