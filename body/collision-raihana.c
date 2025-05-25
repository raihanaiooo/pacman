#include "../header/collision.h"

// Maze dideklarasikan di tempat lain (misalnya maze.c)
extern int maze[24][32];

int isColliding(int newX, int newY, int radius, int direction) {
    int checkX = newX;
    int checkY = newY;

    // Hanya hitung arah jika direction valid (0–3), Ghost bisa pakai -1
    if (direction != -1) {
        switch (direction) {
            case 0: checkX += radius; break; // kanan
            case 1: checkX -= radius; break; // kiri
            case 2: checkY -= radius; break; // atas
            case 3: checkY += radius; break; // bawah
        }
    }

    int col = checkX / TILE_SIZE;
    int row = checkY / TILE_SIZE;

    if (row < 0 || row >= 24 || col < 0 || col >= 32) {
        return 1;
    }

    return (maze[row][col] == 2);
}
