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
