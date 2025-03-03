<<<<<<< HEAD
#include "../header/pacman.h"

Position pacman, food;
bool gameOver;
char map[HEIGHT][WIDTH];

// Fungsi untuk menginisialisasi permainan
void initGame() {
    gameOver = false;

    // Posisi awal Pac-Man
    pacman.x = WIDTH / 2;
    pacman.y = HEIGHT / 2;

    // Posisi awal makanan
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;

    // Membuat peta kosong
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                map[i][j] = '#';  // Tembok
            } else {
                map[i][j] = ' ';
            }
        }
    }
}

// Fungsi untuk menggambar peta
void drawMap() {
    system("cls");  // Membersihkan layar

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == pacman.y && j == pacman.x) {
                printf("P");  // Pac-Man
            } else if (i == food.y && j == food.x) {
                printf("O");  // Makanan
            } else {
                printf("%c", map[i][j]);
            }
        }
        printf("\n");
    }
}

// Fungsi untuk menangani input pemain
void input() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'w': pacman.y--; break;
            case 's': pacman.y++; break;
            case 'a': pacman.x--; break;
            case 'd': pacman.x++; break;
            case 'x': gameOver = true; break;  // Keluar dari permainan
        }
    }
}

// Fungsi untuk menangani logika permainan
void logic() {
    // Cek jika Pac-Man makan makanan
    if (pacman.x == food.x && pacman.y == food.y) {
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
    }

    // Cegah Pac-Man keluar dari batas
    if (pacman.x <= 0 || pacman.x >= WIDTH - 1 || pacman.y <= 0 || pacman.y >= HEIGHT - 1) {
        gameOver = true;
    }
}
=======
#include <graphics.h>
#include "../header/pacman.h"
#include <stdio.h>

int isColliding(Pacman *p, int newX, int newY) {
    int checkX = newX;
    int checkY = newY;

    switch (p->direction)
    {
        case 0: checkX += p->radius; break; // Kanan
        case 1: checkX -= p->radius; break; // Kiri
        case 2: checkY -= p->radius; break; // Atas
        case 3: checkY += p->radius; break; // Bawah
    }
    int color = getpixel(checkX, checkY);  // Ambil warna pixel di posisi baru
    return (color == YELLOW);    // Jika pixel kuning, tabrakan terjadi
}

void drawPacman(Pacman *p) {
    //? Pacmannya
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, BLACK); //! ini buat mulutnya:v
    fillellipse(p->x, p->y, p->radius, p->radius);

    //? Mulutnya
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW); //! awokawok ini buat badannya
    switch (p->direction)
    {
    case 0: //? kanan
        pieslice(p->x,p->y, 30, 330, p->radius);
        break;
    case 1: //? kiri
        pieslice(p->x,p->y, 210, 150, p->radius);
        break;
    case 2: //? atas
        pieslice(p->x,p->y, 120, 60, p->radius);
        break;
    case 3: //? bawah
        pieslice(p->x,p->y, 300, 240, p->radius);
        break;
    
    default:
        break;
    } 
}

void clearPacman(Pacman *p) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(p->x, p->y, p->radius, p->radius);
}

void movePacman(Pacman *p, char key) {
    int newX = p->x;
    int newY = p->y;

    
    switch (key) {
        case 75: newX -= 10; p->direction = 1; break; // Kiri
        case 77: newX += 10; p->direction = 0; break; // Kanan
        case 72: newY -= 10; p->direction = 2; break; // Atas
        case 80: newY += 10; p->direction = 3; break; // Bawah
    }
    if(!isColliding(p, newX, newY)){
        clearPacman(p);
        p->x = newX;
        p->y = newY;
        drawPacman(p);
    }
}
>>>>>>> f8d98a9f59a1559bb8c934d76cd26fbb4f3c48e2
