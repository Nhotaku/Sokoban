#include "header.h"


void spawnJoueur(char plateau[10][10], PositionJoueur* joueurPos) {
  int x, y;
  do {
    x = rand() % 6 + 2; 
    y = rand() % 6 + 2; 
  } while (plateau[x][y] != ' ');

  plateau[x][y] = 'o';
  joueurPos->x = x;  
  joueurPos->y = y;  
}0