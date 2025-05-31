#ifndef COLLISION_H
#define COLLISION_H

#define TILE_SIZE 20

// Fungsi untuk mengecek apakah terjadi tabrakan (collision) pada posisi baru (newX, newY)
// dengan radius tertentu
int isColliding(int newX, int newY, int radius, int direction);

#endif
