#ifndef UI_H
#define UI_H

#define TILE_SIZE 20 

void Map();

void hitungScore(int score, int x, int y, int isWin);

void GameStart();

int GameOver(int score);

void GameWin();

int countDotsAndPowerUps();


#endif