#include <stdio.h>
#include <graphics.h>

int main() {
    int gd = DETECT, gm;
    int x1 = 200, y1 = 200; 
    int x2 = 300, y2 = 300; 
    
    initgraph(&gd, &gm, NULL); // initialize graphics windows
    // MAIN STRUCTUR OF INITGRAPH
    // void initgraph(int *graphicsDriver, int *graphicsMode, char *driverDirectoryPath);

    setcolor(BLUE);
    line(x1,y1,x2,y2);

    getch();  // Tunggu input sebelum menutup window
    closegraph();

    return 0;
}
