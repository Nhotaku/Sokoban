#include "header.h"

char **init_plateau()
{
    char **plateau;
    int x;
    int y;

    x = 0;
	plateau[x] = malloc(10 * sizeof(char));

	while(x < 10)
	{
		plateau[y] = malloc(10 * sizeof(char)); 
		y = 0;

		while(y < 10)
		{
			plateau[x][y] = ' ';
			y++;
		}

		x++;
	}

  for (int i = 0; i < 10; i++) { 
    for (int j = 0; j < 10; j++) {
      if(i == 0 || i == 9){
        plateau[i][j]= '#';
      }
      else if(j == 0 || j == 9){
        plateau[i][j]= '#';
      }
      else {
        plateau[i][j] = ' ';
      }
    }
  }
	return plateau;
}

void afficherPlateau(char **plateau) { 
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", plateau[i][j]);
    }
  }
}
