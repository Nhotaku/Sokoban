#include "header.h"

int main()
{
    // liste variable ou il faut creer un fichier en .c*
    char **plateau = init_plateau();
    int joueur = init_joueur;
    int boite = init_boite;
    int objectif;
    int fin;

afficherPlateau(plateau);

}
void spawnEmplacement(char plateau[10][10], PositionEntre* entrePos) {
  int x, y;
  do {
    x = rand() % 6 + 2; 
    y = rand() % 6 + 2; 
  } while (plateau[x][y] != ' ');

  plateau[x][y] = '.';  
  entrePos->x = x;  
  entrePos->y = y;  
}
void spawn(char plateau[10][10], PositionJoueur* joueurPos, PositionBoite* boitePos, PositionEntre* entrePos) {
    spawnJoueur(plateau, joueurPos);
    spawnBoite(plateau, boitePos);
    spawnEmplacement(plateau, entrePos);
}
void joueurMouvement(char plateau[10][10], PositionJoueur* joueurPos,  PositionEntre* entrePos) {
  printf("Entrez un mouvement : Haut (z), Bas (s), Gauche (q), Droite (d) \n");
  scanf(" %c", &joueurPos->mouvement);
  int deplacement_x = joueurPos->x;
  int deplacement_y = joueurPos->y;

  if (joueurPos->mouvement == 'z') {x-1
    deplacement_x--; //                                                                                                    
  } else if (joueurPos->mouvement == 's') {                                                                                                                       
    deplacement_x++; //                                                                                                                                                      
  } else if (joueurPos->mouvement == 'q') {                                                                                                                                
    deplacement_y--; //                                                                                                                                                      
  } else if (joueurPos->mouvement == 'd') {                                                                                                                   
    deplacement_y++; //                                                                             
  } else {//                                                                                        
    printf("Mouvement non valide !\n");//                                                           
    return;//                                                                                      
  }

  if (plateau[deplacement_x][deplacement_y] == ' '|| plateau[deplacement_x][deplacement_y] == '.') {
    plateau[joueurPos->x][joueurPos->y] = ' ';
    plateau[deplacement_x][deplacement_y] = 'o';
    joueurPos->x = deplacement_x;
    joueurPos->y = deplacement_y;
  }
  if(plateau[entrePos->x][entrePos->y] == ' '){
    plateau[entrePos->x][entrePos->y] = '.';
  }
}
void boitemouvement(char plateau[10][10], PositionBoite* boitePos, PositionJoueur* joueurPos, PositionEntre* entrePos) {
  int deplacement_x = boitePos->x;
  int deplacement_y = boitePos->y;

  if (joueurPos->x == boitePos->x - 1 && joueurPos->y == boitePos->y && joueurPos->mouvement == 's') {
    deplacement_x++;                                                                                  
    if (plateau[deplacement_x][deplacement_y] == ' ' || '.') {
      plateau[boitePos->x][boitePos->y] = ' ';
      plateau[deplacement_x][deplacement_y] = 'X';
      boitePos->x = deplacement_x;
      plateau[joueurPos->x][joueurPos->y] = ' ';
      joueurPos->x++; 
      plateau[joueurPos->x][joueurPos->y] = 'o';
    } else {
      printf("Impossible de bouger la boîte vers le bas !\n");
    }
  }
  else if (joueurPos->x == boitePos->x + 1 && joueurPos->y == boitePos->y && joueurPos->mouvement == 'z') { //si le joueur est en dessous de la boite et appuis sur z
    deplacement_x--;
    if (plateau[deplacement_x][deplacement_y] == ' ' || '.') {
      plateau[boitePos->x][boitePos->y] = ' ';
      plateau[deplacement_x][deplacement_y] = 'X';
      boitePos->x = deplacement_x;
      plateau[joueurPos->x][joueurPos->y] = ' ';
      joueurPos->x--;
      plateau[joueurPos->x][joueurPos->y] = 'o';
    } else {
      printf("Impossible de bouger la boîte vers le haut !\n");
    }
  }
  else if (joueurPos->x == boitePos->x && joueurPos->y == boitePos->y - 1 && joueurPos->mouvement == 'd') {
    deplacement_y++;
    if (plateau[deplacement_x][deplacement_y] == ' ' || '.') {
      plateau[boitePos->x][boitePos->y] = ' ';
      plateau[deplacement_x][deplacement_y] = 'X';
      boitePos->y = deplacement_y;
      plateau[joueurPos->x][joueurPos->y] = ' ';
      joueurPos->y++;
      plateau[joueurPos->x][joueurPos->y] = 'o';
    } else {
      printf("Impossible de bouger la boîte vers la droite !\n");
    }
  }
  else if (joueurPos->x == boitePos->x && joueurPos->y == boitePos->y + 1 && joueurPos->mouvement == 'q') {
    deplacement_y--;
    if (plateau[deplacement_x][deplacement_y] == ' ' || '.') {
      plateau[boitePos->x][boitePos->y] = ' ';
      plateau[deplacement_x][deplacement_y] = 'X';
      boitePos->y = deplacement_y;
      plateau[joueurPos->x][joueurPos->y] = ' ';
      joueurPos->y--;
      plateau[joueurPos->x][joueurPos->y] = 'o';
    } else {
      printf("Impossible de bouger la boîte vers la gauche !\n");
    }
  } 
  if(boitePos->x == entrePos->x && boitePos->y == entrePos->y ){
    printf("Bravo, vous avez gagnez !\n");
    exit(0);//sors du code
  }

  if ((boitePos->x == 1 && boitePos->y == 1) || 
      (boitePos->x == 1 && boitePos->y == 8) || 
      (boitePos->x == 8 && boitePos->y == 1) || 
      (boitePos->x == 8 && boitePos->y == 8)) {
    printf("Vous avez perdu! La boîte est coincée.\n");
    exit(0);//sortir du code
     }
}
int main() {
  PositionJoueur joueurPos;
  PositionBoite boitePos;
  PositionEntre entrePos;
  srand(time(NULL));
  char plateau[10][10];
  startPlateau(plateau);
  spawn(plateau, &joueurPos, &boitePos, &entrePos);
  afficherPlateau(plateau);

  while (1) {/
    system("clear");
    printf("Joueur : %d %d \nBoite : %d %d \nEmplacement : %d %d \n", joueurPos.x, joueurPos.y, boitePos.x, boitePos.y, entrePos.x, entrePos.y);//imprime les positions des objets
    afficherPlateau(plateau);//affiche le tableau
    joueurMouvement(plateau, &joueurPos, &entrePos);//gère les mouvement du joueur 
    boitemouvement(plateau, &boitePos, &joueurPos, &entrePos); 
    
    }


return 0;
}
