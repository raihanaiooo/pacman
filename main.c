#include <stdio.h>
#include <graphics.h>
#include "header/ui.h"
#include "header/ghost.h"

int main() {
    int gd = DETECT, gm;

    initgraph(&gd, &gm, NULL); // initialize graphics windows

    Ghost ghost;
    theGhost(&ghost, 100, 100, RED);  // Buat ghost merah di (100,100)

    int page = 0;
    // MAIN STRUCTUR 
    while (!kbhit()) {  // Loop sampai tombol ditekan
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        map();
        designGhost(&ghost);
        shiftGhost(&ghost, getmaxx(), getmaxy());
        delay(50);
        page = 1 - page;
    }

    getch();
    initgraph(&gd, &gm, NULL); // initialize graphics windows
    
    getch();
    closegraph();
    return 0; 
}


