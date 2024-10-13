#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>

char ** init_plateau();
void afficherPlateau(char **plateau);
int init_joueur();
int init_boite();

typedef struct {
    int x;
    int y;
    char mouvement;
} PositionJoueur;

typedef struct {
    int x;
    int y;
} PositionBoite;

typedef struct {
    int x;
    int y;
} PositionEntre;


#endif