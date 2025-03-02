#include <graphics.h>
#include "../header/pacman.h"
#include <conio.h>

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
    clearPacman(p);

    switch (key)
    {
        case 75: 
            p->x -= 10;
            p->direction = 1;
        break; // Left arrow
        case 77: 
            p->x += 10; 
            p->direction = 0; 
        break; // Right arrow
        case 72: 
            p->y -= 10; 
            p->direction = 2; 
        break; // Up arrow
        case 80: 
            p->y += 10; 
            p->direction = 3; 
        break; // Down arrow
    }

    drawPacman(p);
}