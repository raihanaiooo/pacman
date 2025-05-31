#include "../header/ghost.h"
#include "../header/ui.h"
#include "../header/pacman.h"
#include "../header/powerup.h"
#include "../header/collision.h"
#include <stdlib.h>

int directionX[4] = {1, -1, 0, 0}; 
int directionY[4] = {0, 0, -1, 1};  

void theGhost(Ghost *gh, int x, int y, int hue) {
    gh->x = x;
    gh->y = y;
    gh->initialX = x;
    gh->initialY = y;
    gh->hue = hue;
    gh->radius = 8;  
    
    gh->lastDirX = 0;  
    gh->lastDirY = 0;
}

void designGhost(Ghost *gh) {
    int x = gh->x;
    int y = gh->y;

    setcolor(gh->hue);
    setfillstyle(SOLID_FILL, gh->hue);
    fillellipse(x, y, gh->radius, gh->radius);  

    // Duri dibawah Ghost
    for (int i = -10; i <= 10; i += 5) {
        int spikeY = y + gh->radius;
        fillellipse(x + i, spikeY, 2, 3);
    }

    // Mata Ghost
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x - 4, y - 5, 2, 2);
    fillellipse(x + 4, y - 5, 2, 2);

    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x - 4, y - 5, 1, 1);
    fillellipse(x + 4, y - 5, 1, 1);
}

void addGhost(GhostNode** head, int x, int y, int color) {
    GhostNode* newGhost = (GhostNode*)malloc(sizeof(GhostNode));
    newGhost->ghost.x = x;
    newGhost->ghost.y = y;
    newGhost->ghost.initialX = x;
    newGhost->ghost.initialY = y;
    newGhost->ghost.radius = 8;
    newGhost->ghost.stepCounter = 0;
    newGhost->ghost.hue = color;
    newGhost->ghost.lastDirX = 0;
    newGhost->ghost.lastDirY = 0;

    newGhost->lifetime = 999999; // Atur waktu hidup lama kalau tidak ingin menghilang
    newGhost->color = color;
    newGhost->next = *head;
    *head = newGhost;
}

void updateGhosts(GhostNode** head) {
    GhostNode* current = *head;
    GhostNode* prev = NULL;

    while (current != NULL) {
        current->lifetime--;
        if (current->lifetime <= 0) {
            // Hapus ghost
            GhostNode* toDelete = current;
            if (prev == NULL) {
                *head = current->next;
                current = *head;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            free(toDelete);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void drawGhosts(GhostNode* head) {
    GhostNode* current = head;
    while (current != NULL) {
        designGhost(&(current->ghost));
        current = current->next;
    }
}

int isColliding(Ghost *gh, int newX, int newY) {
    return isColliding(newX, newY, gh->radius, -1);
}


void moveGhost(Ghost *gh, Pacman *pac) {
    if (freezeActive) return;

    switch (gh->hue) {
        case GREEN:  // Pie - Bergerak acak tapi tetap di jalur
            shiftGhost(gh);
            break;
        case RED:  // Liberty - Mengejar Pac-Man
            pursuePacman(gh, pac);
            break;
        case WHITE:  // Faith - Memotong jalur Pac-Man
            blockPacman(gh, pac);
            break;
        case CYAN:  // Rai - Menjauh jika terlalu dekat dengan Pac-Man
            escapePacman(gh, pac);
            break;
        default:
            shiftGhost(gh); 
            break;
    }
}

void shiftGhost(Ghost *gh) {
    if (freezeActive) return;

    int row = gh->y / TILE_SIZE;
    int col = gh->x / TILE_SIZE;

    int possibleDirections[4][2];  
    int directionCount = 0;

    if (row > 0 && !isColliding(gh->x, gh->y - TILE_SIZE, 0, -1)) {  // Atas
        possibleDirections[directionCount][0] = 0;
        possibleDirections[directionCount][1] = -1;
        directionCount++;
    }
    if (row < 23 && !isColliding(gh->x, gh->y + TILE_SIZE, 0, -1)) {  // Bawah
        possibleDirections[directionCount][0] = 0;
        possibleDirections[directionCount][1] = 1;
        directionCount++;
    }
    if (col > 0 && !isColliding(gh->x - TILE_SIZE, gh->y, 0, -1)) {  // Kiri
        possibleDirections[directionCount][0] = -1;
        possibleDirections[directionCount][1] = 0;
        directionCount++;
    }
    if (col < 31 && !isColliding(gh->x + TILE_SIZE, gh->y, 0, -1)) {  // Kanan
        possibleDirections[directionCount][0] = 1;
        possibleDirections[directionCount][1] = 0;
        directionCount++;
    }

    if (directionCount > 1) {
        for (int i = 0; i < directionCount; i++) {
            if (possibleDirections[i][0] == -gh->lastDirX && possibleDirections[i][1] == -gh->lastDirY) {
                possibleDirections[i][0] = possibleDirections[directionCount - 1][0];
                possibleDirections[i][1] = possibleDirections[directionCount - 1][1];
                directionCount--;
                break;
            }
        }
    }

    int randomIndex = rand() % directionCount;
    gh->lastDirX = possibleDirections[randomIndex][0];
    gh->lastDirY = possibleDirections[randomIndex][1];
    gh->x += gh->lastDirX * TILE_SIZE;
    gh->y += gh->lastDirY * TILE_SIZE;
}

void pursuePacman(Ghost *gh, Pacman *pac) { // Breadth-First Search (BFS)
    int visited[MAX_ROW][MAX_COL] = {0};  // Matrix untuk menandai jalan yang sudah dilalui
    int parent[MAX_ROW][MAX_COL][2];      // Matrix untuk menyimpan asal langkah dari jalan sebelumnya

    std::queue<Node> q;  // Queue untuk BFS
    int startRow = gh->y / TILE_SIZE;
    int startCol = gh->x / TILE_SIZE;
    int targetRow = pac->y / TILE_SIZE;
    int targetCol = pac->x / TILE_SIZE;

    visited[startRow][startCol] = 1;
    q.push({startRow, startCol});
    parent[startRow][startCol][0] = -1;  // Menandakan titik awal
    parent[startRow][startCol][1] = -1;

    // Arah dalam [row, col] untuk bergerak ke kanan, kiri, atas, bawah
    int dX[4] = {1, -1, 0, 0};
    int dY[4] = {0, 0, -1, 1};

    // BFS untuk mencari Pac-Man
    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // Jika target ditemukan, hentikan pencarian
        if (current.row == targetRow && current.col == targetCol) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dY[i];
            int newCol = current.col + dX[i];

            if (newRow >= 0 && newRow < MAX_ROW && newCol >= 0 && newCol < MAX_COL &&
                !visited[newRow][newCol] && maze[newRow][newCol] != 2) {  // Periksa apakah jalan valid dan bukan dinding
                visited[newRow][newCol] = 1;
                q.push({newRow, newCol});
                parent[newRow][newCol][0] = current.row;  // Simpan asal langkah
                parent[newRow][newCol][1] = current.col;
            }
        }
    }

    // Menemukan langkah pertama dari jalur terpendek
    int nextRow = targetRow;
    int nextCol = targetCol;

    // Menelusuri jalur mundur hingga mencapai langkah pertama
    while (parent[nextRow][nextCol][0] != startRow || parent[nextRow][nextCol][1] != startCol) {
        int tempRow = parent[nextRow][nextCol][0];
        int tempCol = parent[nextRow][nextCol][1];
        nextRow = tempRow;
        nextCol = tempCol;
    }

    // Ubah koordinat Ghost ke langkah pertama dari jalur BFS
    gh->x = nextCol * TILE_SIZE;
    gh->y = nextRow * TILE_SIZE;
}

void blockPacman(Ghost *gh, Pacman *pac) {
    int targetX = pac->x + (directionX[pac->direction] * 4 * TILE_SIZE);
    int targetY = pac->y + (directionY[pac->direction] * 4 * TILE_SIZE);

    int dx = targetX - gh->x;
    int dy = targetY - gh->y;

    if (abs(dx) > abs(dy)) {
        if (!isColliding(gh->x + (dx > 0 ? TILE_SIZE : -TILE_SIZE), gh->y, 0, -1)) {
            gh->x += (dx > 0 ? TILE_SIZE : -TILE_SIZE);
        } else if (!isColliding(gh->x, gh->y + (dy > 0 ? TILE_SIZE : -TILE_SIZE), 0, -1)) {
            gh->y += (dy > 0 ? TILE_SIZE : -TILE_SIZE);
        }
    } else {
        if (!isColliding(gh->x, gh->y + (dy > 0 ? TILE_SIZE : -TILE_SIZE), 0, -1)) {
            gh->y += (dy > 0 ? TILE_SIZE : -TILE_SIZE);
        } else if (!isColliding(gh->x + (dx > 0 ? TILE_SIZE : -TILE_SIZE), gh->y, 0, -1)) {
            gh->x += (dx > 0 ? TILE_SIZE : -TILE_SIZE);
        }
    }
}

void escapePacman(Ghost *gh, Pacman *pac) {
    int dx = pac->x - gh->x;
    int dy = pac->y - gh->y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance < 8 * TILE_SIZE) {
        int possibleDirections[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        int validDirections[4];
        int validCount = 0;

        for (int i = 0; i < 4; i++) {
            int newX = gh->x + possibleDirections[i][0] * TILE_SIZE;
            int newY = gh->y + possibleDirections[i][1] * TILE_SIZE;
            if (!isColliding(newX, newY, 0, -1)) {
                validDirections[validCount++] = i;  
            }
        }

        if (validCount > 0) {
            int randomIndex = rand() % validCount;
            gh->x += possibleDirections[validDirections[randomIndex]][0] * TILE_SIZE;
            gh->y += possibleDirections[validDirections[randomIndex]][1] * TILE_SIZE;
        } else {
            shiftGhost(gh); 
        }
    } else {
        shiftGhost(gh);  
    }
}


// Fungsi untuk mengecek tabrakan antara Pac-Man dan Ghost
int CollisionWithGhost(Pacman *p, Ghost *g) {
    int dx = p->x - g->x;
    int dy = p->y - g->y;
    int distanceSquared = dx * dx + dy * dy;
    int collisionDistance = (p->radius + g->radius) * (p->radius + g->radius);

    if (distanceSquared <= collisionDistance) {
        if (kebalActive) {
            printf("⚡ Pac-Man kebal! Ghost akan kembali ke posisi awal.\n");
            resetGhost(g);  // Ghost respawn ke posisi awal
            return 0;  // Jangan hitung tabrakan sebagai kerugian bagi Pac-Man
        }
        return 1;  // Tabrakan normal
    }
    
    return 0;  // True jika tabrakan
}

// prosedur reset ghost 
// void resetGhost(Ghost *gh) {
// gh->x = gh->initialX;
// gh->y = gh->initialY;
// } (DIHAPUS)
