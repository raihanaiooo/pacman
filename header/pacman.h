#ifndef PACMAN_H
#define PACMAN_H

#include <graphics.h>

#define PACMAN_SPEED 10

// Struktur untuk frame animasi mulut (menggunakan circular linked list)
typedef struct Frame {
    int start_angle;
    int end_angle;           // Sudut bukaan mulut
    struct Frame *next;      // Pointer ke frame berikutnya
} Frame;

// Tipe fungsi untuk clear dan draw entitas apa pun
typedef void (*ClearFunc)(void *);
typedef void (*DrawFunc)(void *);

// Struktur Pacman
typedef struct {
    int x, y;                // Posisi saat ini
    int radius;              // Ukuran radius kepala pacman
    int direction;           // Arah gerak pacman (misalnya 0 = kanan, 1 = kiri, dst.)
    int lives;               // Nyawa pacman
    int initialX, initialY;  // Posisi awal pacman

    Frame *frameHead;        // Head linked list animasi mulut
    Frame *currentFrame;     // Frame mulut saat ini
} Pacman;

// Forward declaration untuk Ghost (struktur didefinisikan di ghost.h)
typedef struct Ghost Ghost;
typedef struct GhostNode GhostNode;

// ==== FUNGSI-FUNGSI PACMAN ====

// Gambar pacman di posisi saat ini
void drawPacman(Pacman *p);

// Hapus gambar pacman dari layar
void clearPacman(Pacman *p);

// Gerakkan pacman berdasarkan input key
void movePacman(Pacman *p, int key, int *score);


// Reset posisi dan status pacman
void resetPacman(Pacman *p);

// Reset ghost ke posisi awal (digunakan saat collision)
void resetGhost(GhostNode* node);

// Update status pacman setelah collision dengan ghost
void updatePacmanAfterCollision(Pacman *pacman, GhostNode *node, int numGhosts, int *score);

// Tangani kondisi game over, kembalikan 1 jika game over
int handleGameOver(Pacman *pacman, int *score, GhostNode *node, int numGhosts);

// ==== RESET GENERIC UNTUK PACMAN ATAU GHOST ====

// Fungsi generik untuk reset posisi entitas (Pacman atau Ghost)
void resetEntity(void *ent,
                 ClearFunc clearF,
                 DrawFunc drawF,
                 int *xPtr, int *yPtr,
                 int initX, int initY);

// Fungsi untuk clear Ghost (digunakan dalam resetEntity)
void clearGhost(void *gh);

// ==== ANIMASI MULUT PACMAN ====

// Inisialisasi linked list frame animasi mulut pacman
void initPacmanAnimation(Pacman *p);

// Perbarui frame animasi ke frame berikutnya
void updatePacmanFrame(Pacman *p);

// Gambar pacman dengan animasi (menggunakan current frame)
void drawPacmanAnimated(Pacman *p, Frame *current);

#endif // PACMAN_H
