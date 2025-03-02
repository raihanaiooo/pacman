#include <stdio.h>
#include <graphics.h>
#include "header/ui.h"


int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // initialize graphics windows
    
    map();
    getch();
    closegraph();
    return 0; 
}

