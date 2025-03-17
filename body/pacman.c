#include <graphics.h>
#include "../header/pacman.h"
#include "../header/powerup.h"
#include "../header/scoring.h"
#include <stdio.h>
extern int maze[24][32];
#define TILE_SIZE 20

int isColliding(Pacman *p, int newX, int newY) {
    int checkX = newX;
    int checkY = newY;

    switch (p->direction)
    {
        case 0: checkX += p->radius; break; // Kanan
        case 1: checkX -= p->radius; break; // Kiri
        case 2: checkY -= p->radius; break; // Atas
        case 3: checkY += p->radius; break; // Bawah
    }
    int col = checkX / TILE_SIZE;
    int row = checkY / TILE_SIZE;

    if (row < 0 || row >= 24 || col < 0 || col >= 32 )
    {
        return 1;
    }
    return(maze[row][col] == 2);
    
}

void drawPacman(Pacman *p) {
    //? Pacmannya
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, BLACK); //! ini buat mulutnya:v
    fillellipse(p->x, p->y, p->radius, p->radius);

    //? Mulutnya
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW); //! awokawok ini buat badannya
    switch (p->direction)
    {
    case 0: //? kanan
        pieslice(p->x,p->y, 30, 330, p->radius);
        break;
    case 1: //? kiri
        pieslice(p->x,p->y, 210, 150, p->radius);
        break;
    case 2: //? atas
        pieslice(p->x,p->y, 120, 60, p->radius);
        break;
    case 3: //? bawah
        pieslice(p->x,p->y, 300, 240, p->radius);
        break;
    
    default:
        break;
    } 
}

void clearPacman(Pacman *p) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(p->x, p->y, p->radius, p->radius);
}

void movePacman(Pacman *p, char key, int *score, bool isAuto) {
    int newX = p->x;
    int newY = p->y;

    if (isAuto) {
        // Gerakan otomatis berdasarkan arah Pacman saat ini
        switch (p->direction) {
            case 1: newX -= PACMAN_SPEED; break;
            case 0: newX += PACMAN_SPEED; break;
            case 2: newY -= PACMAN_SPEED; break;
            case 3: newY += PACMAN_SPEED; break;
        }
    } else {
        // Gerakan manual berdasarkan input pengguna
        switch (key) {
            case 75: newX -= 10; p->direction = 1; break; // Kiri
            case 77: newX += 10; p->direction = 0; break; // Kanan
            case 72: newY -= 10; p->direction = 2; break; // Atas
            case 80: newY += 10; p->direction = 3; break; // Bawah
        }
    }

    if (!isColliding(p, newX, newY)) {
        clearPacman(p);
        p->x = newX;
        p->y = newY;
        drawPacman(p);
        
        if (isAuto) {
            scoring(p->x, p->y, score);
            checkPowerUpCollision(p->x, p->y);
        }
    }
}

// void movePacman(Pacman *p, char key) {
//     int newX = p->x;
//     int newY = p->y;

    
//     switch (key) {
//         case 75: newX -= 10; p->direction = 1; break; // Kiri
//         case 77: newX += 10; p->direction = 0; break; // Kanan
//         case 72: newY -= 10; p->direction = 2; break; // Atas
//         case 80: newY += 10; p->direction = 3; break; // Bawah
//     }
//     if(!isColliding(p, newX, newY)){
//         clearPacman(p);
//         p->x = newX;
//         p->y = newY;
//         drawPacman(p);
//     }
    
// }

// void autoMovePacman(Pacman *p, int *score) {
//     int newX = p->x;
//     int newY = p->y;

//     switch (p->direction) {
//         case 1: newX -= PACMAN_SPEED; break;
//         case 0: newX += PACMAN_SPEED; break;
//         case 2: newY -= PACMAN_SPEED; break;
//         case 3: newY += PACMAN_SPEED; break;
//     }

//     if (!isColliding(p, newX, newY)) {
//         clearPacman(p);
//         p->x = newX;
//         p->y = newY;
//         drawPacman(p);
//         scoring(p->x, p->y, score);
//         checkPowerUpCollision(p->x, p->y);
//     }
// }