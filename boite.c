#include "header.h"


void spawnBoite(char plateau[10][10], PositionBoite* boitePos) {
  int x, y;
  do {
    x = rand() % 6 + 2; 
    y = rand() % 6 + 2; 
  } while (plateau[x][y] != ' ');

  plateau[x][y] = 'X';  
  boitePos->x = x;  
  boitePos->y = y;  
}