#include <graphics.h>
#include "../header/pacman.h"
#include <stdio.h>

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
    int color = getpixel(checkX, checkY);  // Ambil warna pixel di posisi baru
    return (color == YELLOW);    // Jika pixel kuning, tabrakan terjadi
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

void movePacman(Pacman *p, char key) {
    int newX = p->x;
    int newY = p->y;

    
    switch (key) {
        case 75: newX -= 10; p->direction = 1; break; // Kiri
        case 77: newX += 10; p->direction = 0; break; // Kanan
        case 72: newY -= 10; p->direction = 2; break; // Atas
        case 80: newY += 10; p->direction = 3; break; // Bawah
    }
    if(!isColliding(p, newX, newY)){
        clearPacman(p);
        p->x = newX;
        p->y = newY;
        drawPacman(p);
    }
}