#include <stdio.h>
#include <graphics.h>
//#include "header/ui.h"


int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // initialize graphics windows
    // MAIN STRUCTUR OF INITGRAPH
    
    map();// void initgraph(int *graphicsDriver, int *graphicsMode, char *driverDirectoryPath);
    getch();  // Tunggu input sebelum menutup window
    closegraph();
    return 0; 
}

