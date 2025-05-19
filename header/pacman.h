#ifndef PACMAN_H
#define PACMAN_H
#define PACMAN_SPEED 10
#include <graphics.h>

// struktur frame untuk animasi mulut (menggunakan circular linked list)
typedef struct Frame {
    int start_angle; 
    int end_angle; //sudut mulut 
    struct Frame *next; // pointer ke frame selanjutnya 
} Frame; 

// tipe fungsi unutk clear dan draw apa pun 
typedef void (*ClearFunc)(void *); // buat ngehapus/ clear gambar entitas apapun, void* bakal di casting ke tipe pacman* atau ghost*
typedef void (*DrawFunc)(void *); // buat menggambar/ draw ~//~ 

typedef struct {
    int x, y;
    int radius;
    int direction;
    int lives;
    int initialX, initialY;  // Posisi awal pacman
// pointer animasi mulut 
    Frame *frameHead;
    Frame *currentFrame;
} Pacman;

typedef struct Ghost Ghost;

// Deklarasi fungsi untuk menggambar dan menghapus pacman
void drawPacman(Pacman *p);
void clearPacman(Pacman *p);
void movePacman(Pacman *p, int key, int *score);
// int isColliding(Pacman *p, int newX, int newY);

// Deklarasi fungsi untuk reset dan update pacman dan reset ghost 
void resetPacman(Pacman *p);
void resetGhost(Ghost *gh); // dari ghost.h di pindahin kesini
void updatePacmanAfterCollision(Pacman *pacman, Ghost ghosts[], int numGhosts, int *score);
int handleGameOver(Pacman *pacman, int *score, Ghost ghosts[], int numGhosts);

// generic reset : hapus gambar lama, reset posisi, gambar ulang 
void resetEntity(void *ent,
                ClearFunc clearF, 
                DrawFunc drawF, 
                int *xPtr, int *yPtr, int initX, int initY);
// ent     : pointer ke struct entitas (Pacman* atau Ghost*)
// clearF  : fungsi untuk menghapus gambar lama
// drawF   : fungsi untuk menggambar ulang di posisi awal
// xPtr,yPtr : pointer ke koordinat x,y dalam struct entitas
// initX,initY : nilai posisi awal yang akan dipulihkan

// clear ghost harus dipanggil oleh generic 
void clearGhost(void *gh);

// prototipe fungsi animasi mulut 
// inisialisasi linked list frame, perlu di panggil sekali di awla game 
//void initPacmanAnimation(int radius);

// update pointer frame (pindah ke frame berikutnya tiap frameDelay ms)
void updatePacmanFrame(Pacman *p);

// gambar pacman dengan frame mulut sesuai list saat ini 
void drawPacmanAnimated(Pacman *p, Frame *current);

// deklarasi fungsi animasi mulut 
void initPacmanAnimation(Pacman *p);


#endif