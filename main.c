#include "header.h"

int main()
{
    // liste variable ou il faut creer un fichier en .c*
    char **plateau = init_plateau();
    int joueur = init_joueur();
    int boite = init_boite();
    int objectif;
    int fin;

afficherPlateau(plateau);

}
void spawnEmplacement(char plateau[10][10], PositionEntre* entrePos) {//fonction qui fait apparaitre l'emplacement
  int x, y;
  do {
    x = rand() % 6 + 2; 
    y = rand() % 6 + 2; 
  } while (plateau[x][y] != ' ');

  plateau[x][y] = '.';  
  entrePos->x = x;  
  entrePos->y = y;  
}
void spawn(char plateau[10][10], PositionJoueur* joueurPos, PositionBoite* boitePos, PositionEntre* entrePos) {//fonction qui réunis les 3 fonctions qui font apparaitre les objets
    spawnJoueur(plateau, joueurPos);
    spawnBoite(plateau, boitePos);
    spawnEmplacement(plateau, entrePos);
}
void joueurMouvement(char plateau[10][10], PositionJoueur* joueurPos,  PositionEntre* entrePos) {//fonction pour gérer les mouvement du joueur
  printf("Entrez un mouvement : Haut (z), Bas (s), Gauche (q), Droite (d) \n");//demande a l'utilisateur une direction
  scanf(" %c", &joueurPos->mouvement);//récupère la direction et la mets dans la structure
  int deplacement_x = joueurPos->x;
  int deplacement_y = joueurPos->y;//crée des variables qui sont égale a la position du joueur

  if (joueurPos->mouvement == 'z') {//déplace le joueur en fonction du mouvement ATTENTION x-1 est égale a remonter et x+1 est égale a déscendre car le tableau ressemble à :
    deplacement_x--; //                                                                             0     0 1 2 3 4 5 6 7 8 9 en ligne                           
  } else if (joueurPos->mouvement == 's') {//                                                       1                                                                  
    deplacement_x++; //                                                                             2                                                                         
  } else if (joueurPos->mouvement == 'q') {//                                                       3                                                                         
    deplacement_y--; //                                                                             4                                                                         
  } else if (joueurPos->mouvement == 'd') {//                                                       5                                                            
    deplacement_y++; //                                                                             6
  } else {//                                                                                        7
    printf("Mouvement non valide !\n");//                                                           8
    return;//                                                                                       9 en colone
  }

  if (plateau[deplacement_x][deplacement_y] == ' '|| plateau[deplacement_x][deplacement_y] == '.') { //regarde si la case dans laquel on veut aller est vide ou l'emplacement
    plateau[joueurPos->x][joueurPos->y] = ' ';//remplace l'ancienne place du joueur pars du vide
    plateau[deplacement_x][deplacement_y] = 'o';//place le joueur dans la nouvelle case
    joueurPos->x = deplacement_x;//enregistre le nouvelle emplacement dans la structure
    joueurPos->y = deplacement_y;
  }
  if(plateau[entrePos->x][entrePos->y] == ' '){//permet de faire apparaitre l'emplacement a nouveau si il est "macher dessus"
    plateau[entrePos->x][entrePos->y] = '.';
  }
}
void boitemouvement(char plateau[10][10], PositionBoite* boitePos, PositionJoueur* joueurPos, PositionEntre* entrePos) {//fonction qui gère le déplacement de la boite
  int deplacement_x = boitePos->x;//crée des variables qui sont égale a la position de la boite
  int deplacement_y = boitePos->y;

  if (joueurPos->x == boitePos->x - 1 && joueurPos->y == boitePos->y && joueurPos->mouvement == 's') {//si le joueur est au dessus de la boite et appuis sur s
    deplacement_x++;                                                                                  //Fait déplacer la boite et le joueur
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
  else if (joueurPos->x == boitePos->x && joueurPos->y == boitePos->y - 1 && joueurPos->mouvement == 'd') {//si le joueur est a gauche de la boite et appuis sur d
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
  else if (joueurPos->x == boitePos->x && joueurPos->y == boitePos->y + 1 && joueurPos->mouvement == 'q') {//si le joueur est a droite de la boite et appuis sur q
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
  if(boitePos->x == entrePos->x && boitePos->y == entrePos->y ){//si la boite arrive sur l'emplacement
    printf("Bravo vous avez gagnez !\n");
    exit(0);//sors du code
  }

  if ((boitePos->x == 1 && boitePos->y == 1) ||//si la boite ce trouve dans un des 4 coins 
      (boitePos->x == 1 && boitePos->y == 8) || 
      (boitePos->x == 8 && boitePos->y == 1) || 
      (boitePos->x == 8 && boitePos->y == 8)) {
    printf("Vous avez perdu ! La boîte est coincée dans un coin.\n");
    exit(0);//sortir du code
     }
}
int main() {//boucle de jeu principale
  PositionJoueur joueurPos;//appelle les 3 structures
  PositionBoite boitePos;
  PositionEntre entrePos;
  srand(time(NULL));//générateur de nombre aléatoire
  char plateau[10][10];//crée le tableau qui sers de plateau
  startPlateau(plateau);//crée et remplie le tableau
  spawn(plateau, &joueurPos, &boitePos, &entrePos);//fait apparaitre les objets
  afficherPlateau(plateau);//affiche le tableau une première fois

  while (1) {//boucle qui ne ce finit jamais
    system("clear");//retire l'ancien tableau et permet de garder uniquement le tableau actuelle
    printf("Joueur : %d %d \nBoite : %d %d \nEmplacement : %d %d \n", joueurPos.x, joueurPos.y, boitePos.x, boitePos.y, entrePos.x, entrePos.y);//imprime les positions des objets
    afficherPlateau(plateau);//affiche le tableau
    joueurMouvement(plateau, &joueurPos, &entrePos);//gère les mouvement du joueur 
    boitemouvement(plateau, &boitePos, &joueurPos, &entrePos); //gère les mouvements de la boite
    
    }


return 0;
}