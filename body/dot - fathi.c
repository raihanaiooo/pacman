#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "../header/scoring.h"
#include "../header/ui.h"
#include "../header/powerup.h"

extern int maze[ROWS][COLS]; // ambil peta dari Revaldi.c

// Array buat nyimpen status dot dimakan atau belum
int dots[ROWS][COLS];
Dot *dotHead = NULL;

int dotKosong(int i, int j)
{
    return (
        // kosongin titik
        ((i == 18 && (j == 11 || j == 12)) ||
         (i == 20 && (j == 11 || j == 12))) ||
        (i == 9 && (j >= 0 && j <= 4)) ||
        (i == 9 && (j >= 27 && j <= 31)) ||
        (i == 13 && (j >= 0 && j <= 4)) ||
        (i == 13 && (j >= 27 && j <= 31)) ||
        (i == 11 && (j >= 13 && j <= 18)) ||
        (i == 12 && (j >= 13 && j <= 18)) ||
        ((i >= 18 && i <= 20) && j == 6) ||
        ((i >= 17 && i <= 20) && j == 8) ||
        (i == 21 && j == 13) ||
        (i == 19 && j == 13) ||
        (i == 18 && (j == 19 || (j >= 23 && j <= 24))) ||
        (i == 17 && (j >= 19 && j <= 20)) ||
        (i == 20 && (j == 19 || (j >= 24 && j <= 25))) ||
        (i == 21 && (j >= 19 && j <= 20)) ||
        ((i >= 18 && i <= 29) && j == 21) ||
        (i == 19 && j == 20) ||
        (i == 23 && (j >= 0 && j <= 31)) ||
        (i == 3 && j == 5) || 
        //KORDINAT POWERUPS
         (i == 1 && j == 1) ||
        (i == 1 && j == 30) ||
        (i == 2 && j == 13) ||
        (i == 4 && j == 20) ||
        (i == 7 && j == 10) ||
        (i == 14 && j == 25) ||
        (i == 13 && j == 8) ||
        (i == 17 && j == 3) ||
        (i == 17 && j == 13) ||
        (i == 21 && j == 26) ||
        (i == 22 && j == 1) ||
        (i == 9 && j == 23)||
        (i == 15 && j == 29)||
        (i == 22 && j == 16)||
        (i == 1 && j == 11))
        ;
}

// inisialisasi titik
void setTitikDot()
{
    dotHead = NULL; // Reset linked list
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (maze[i][j] == 0 && !dotKosong(i, j))
            {
                Dot *newDot = (Dot *)malloc(sizeof(Dot));
                newDot->x = j * TILE_SIZE + TILE_SIZE / 2;
                newDot->y = i * TILE_SIZE + TILE_SIZE / 2;
                newDot->next = dotHead;
                dotHead = newDot;
            }
        }
    }
}

// generate titik-titik yang belum dimakan
void gambarDot()
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    Dot *current = dotHead;
    while (current != NULL)
    {
        fillellipse(current->x, current->y, DOT_RADIUS, DOT_RADIUS);
        current = current->next;
    }
}

// pacman memakan dot
void scoring(int pacmanX, int pacmanY, int *score)
{
    Dot **current = &dotHead;
    while (*current != NULL)
    {
        if (abs((*current)->x - pacmanX) < TILE_SIZE / 2 &&
            abs((*current)->y - pacmanY) < TILE_SIZE / 2)
        {

            Dot *temp = *current;
            *current = (*current)->next;
            free(temp);

            *score += doublePointActive ? 2 : 1;
            PlaySound("sound/makan.wav", NULL, SND_FILENAME | SND_ASYNC);
            break;
        }
        current = &((*current)->next);
    }
}

// free memory dot
void freeDot()
{
    Dot *current = dotHead;
    while (current != NULL)
    {
        Dot *temp = current;
        current = current->next;
        free(temp);
    }
    dotHead = NULL;
}