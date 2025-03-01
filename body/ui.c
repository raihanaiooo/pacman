#include <stdio.h>
#include <graphics.h>
//#include "header/ui.h"

void map() {
    // Map luar
    setcolor(YELLOW);
    rectangle(15, 15, 625, 465);

    //kanan kiri atas bawah
    moveto(320, 15);
    linerel(0, 85);
    moveto(320, 465);
    linerel(0, -85);
    rectangle(15, 200, 90, 270);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(20, 205, YELLOW);
    rectangle(550, 200, 625, 270);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(555, 205, YELLOW);
    
    // Yang tengah
    moveto(295, 200);
    linerel(-50, 0);
    linerel(0, 80);
    linerel(150, 0);
    linerel(0, -80);
    linerel(-50, 0);
    
    // kiri atas
    setcolor(YELLOW);
    rectangle(50, 55, 140, 100);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(55, 60, YELLOW);

    // atas kiri
    setcolor(YELLOW);
    rectangle(185, 55, 275, 100);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(190, 60, YELLOW);

    // atas kanan
    setcolor(YELLOW);
    rectangle(360, 55, 450, 100);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(365, 60, YELLOW);

    // kanan atas
    setcolor(YELLOW);
    rectangle(505, 55, 595, 100);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(510, 60, YELLOW);

    // kiri bawah
    setcolor(YELLOW);
    rectangle(50, 365, 140, 410);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(55, 370, YELLOW);

    // bawah kiri
    setcolor(YELLOW);
    rectangle(185, 365, 275, 410);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(190, 370, YELLOW);

    // bawah kanan
    setcolor(YELLOW);
    rectangle(360, 365, 450, 410);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(365, 370, YELLOW);

    // kanan bawah
    setcolor(YELLOW);
    rectangle(505, 365, 595, 410);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(510, 370, YELLOW);

    // Garis atas bawah
    moveto(50,150);
    linerel(545, 0);
    moveto(50, 320);
    linerel(545, 0);

    moveto(162, 150);
    linerel(0, 50);
    moveto(162, 320);
    linerel(0, -50);
    moveto(472, 150);
    linerel(0, 50);
    moveto(472, 320);
    linerel(0, -50);




    // Draw some walls inside the map
    //rectangle(240, 190, 400, 290);
    // rectangle(300, 100, 350, 150);
    // rectangle(100, 200, 150, 250);
    // rectangle(300, 200, 350, 250);
    // rectangle(100, 300, 150, 350);
    // rectangle(200, 300, 250, 350);
    // rectangle(300, 300, 350, 350);

    // Draw the path for PaBcman
    // line(50, 250, 450, 250);
    // line(250, 50, 250, 450);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // initialize graphics windows
     // MAIN STRUCTUR OF INITGRAPH
    
    map();// void initgraph(int *graphicsDriver, int *graphicsMode, char *driverDirectoryPath);
    getch();  // Tunggu input sebelum menutup window
    closegraph();
    return 0; 
}

