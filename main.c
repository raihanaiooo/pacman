#include <stdio.h>
#include <graphics.h>
#include "ghost.h"

int main() {
    int gd = DETECT, gm;

    // void initgraph(int *graphicsDriver, int *graphicsMode, char *driverDirectoryPath);
    initgraph(&gd, &gm, NULL); // initialize graphics windows

    Ghost ghost;
    theGhost(&ghost, 100, 100, RED);  // Buat ghost merah di (100,100)

    // MAIN STRUCTUR 
    while (!kbhit()) {  // Loop sampai tombol ditekan
        cleardevice();
        designGhost(&ghost);
        shiftGhost(&ghost, getmaxx(), getmaxy());
        delay(50);
    }

    getch();
    closegraph();

    return 0;
}
