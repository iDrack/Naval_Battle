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

Matrice* genererMatriceVide(char *titre, int taille_matrice){
    // Générer une matrice vide.
    Matrice *m = malloc(sizeof(Matrice));
    m->titre = titre;
    m->taille = taille_matrice;

    m->value = (char **)malloc(m->taille * sizeof(char*)); // Mémoire (lignes).
    // Mémoire (colonnes).
    for(char i = 0; i < m->taille; i++){
        m->value[i] = (char *)malloc(m->taille * sizeof(char));
    }
    // Initialisation.
    for(int i = 0; i < m->taille; i++){
        for(int j = 0; j < m->taille; j++){
            m->value[i][j] = '.';
        }
    }

    return m;
}

void afficherMatrice(Matrice *m){
    printf("\n%s : \n", m->titre);
    printf("\t");
    for(int i = 0; i < m->taille; i++) printf("  %c  ", 65+i);
    printf("\n");
    for(int i = 0; i < m->taille; i++){
        if(i >= 10) printf(" %d  ", i);
        else printf("  %d  ", i);

        for(int j = 0; j < m->taille; j++){
            printf("  %c  ", m->value[i][j]);
        }
        printf("\n");
    }
}

void choisirTaille(int *ptr){
    int taille_matrice;
    printf("Choisissez la taille de la grille de jeu (26 max) : ");
    scanf("%d", &taille_matrice);
    printf("\n");
    while(taille_matrice > 26 || taille_matrice < 0){
        printf("Choisissez une taille conforme de grille (26 max) : ");
        scanf("%d", &taille_matrice);
        printf("\n");
    }

    *ptr = taille_matrice;
}

