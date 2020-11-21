#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int getTailleNavire(NavireType nt){
    switch(nt){
        case PORTEAVION:
            return 5;
            break;
        case CROISER:
            return 4;
            break;
        case DESTROYER:
            return 3;
            break;
        case SOUSMARIN:
            return 3;
            break;
        case TORPILLEUR:
            return 2;
            break;
    }

    return -1;
}

Navire *genererNavire(NavireType nt, Matrice *m){
    Navire *n = malloc(sizeof(Navire));
    n->nom = nt;
    n->etat = ATTENTE;
    n->matrice = m; // Pointeur de la matrice afin de connaitre la grille/matrice d'origine.

    n->taille = getTailleNavire(nt);

    n->posX = (int*)malloc(n->taille * sizeof(int));
    n->posY = (int*)malloc(n->taille * sizeof(int));

    return n;
}

void placementNavire(Matrice *m, NavireType nt, int *posX, int *posY){
    Navire *notre_navire = genererNavire(nt, m);
    for(int i = 0; i < notre_navire->taille; i++){
        notre_navire->posX[i] = posX[i];
        notre_navire->posY[i] = posY[i];
        m->value[posY[i]][posX[i]] = 'O';
    }

    /*
     // ---------- ZONE TEST ----------
    printf("\n Verif navire aloué : \n");
    printf("Etat : %d \n", notre_navire->etat);
    printf("A la matrice : '%s' \n", notre_navire->matrice->titre);
    printf("Type : %d \n", notre_navire->nom);
    printf("Taille : %d \n", notre_navire->taille);
    printf("De X%d a X%d \n", notre_navire->posX[0], notre_navire->posX[notre_navire->taille - 1]);
    printf("De Y%d a Y%d \n\n", notre_navire->posY[0], notre_navire->posY[notre_navire->taille - 1]);
    */
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
    printf("     ");
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


