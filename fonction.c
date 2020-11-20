#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

Navire *genererNavire(NavireType nt, Matrice *m){
    Navire *n = malloc(sizeof(Navire));
    n->nom = nt;
    n->etat = ATTENTE;
    n->matrice = m;

    switch (nt){
        case PORTEAVION:
            n->taille = 5;
            break;
        case CROISER:
            n->taille = 4;
            break;
        case DESTROYER:
            n->taille = 3;
            break;
        case SOUSMARIN:
            n->taille = 3;
            break;
        case TORPILLEUR:
            n->taille = 2;
            break;

        default:
            break;
    }

    return n;
}

Matrice* genererMatriceVide(char *titre){
    // Générer une matrice vide.
    Matrice *m = malloc(sizeof(Matrice));
    m->titre = titre;
    m->taille = TAILLE;
    for(int i = 0; i < m->taille; i++){
        for(int j = 0; j < m->taille; j++){
            m->value[i][j] = '.';
        }
    }

    return m;
}

void afficherMatrice(Matrice *m){
    printf("%s : \n", m->titre);
    printf("\t");
    for(int i = 0; i < m->taille; i++) printf("%c \t", 65+i);
    printf("\n");
    for(int i = 0; i < m->taille*(m->taille-1); i++) printf("_");
    printf("\n   | \n");
    for(int i = 0; i < m->taille; i++){
        printf(" %d | \t", i);
        for(int j = 0; j < m->taille; j++){
            printf("%c \t", m->value[i][j]);
        }
        printf("\n   | \n");
    }
}

