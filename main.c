#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction.h"

int main(){
    Navire *armadaJoueur[TAILLE_FLOTTE];
    Navire *armadaAdversaire[TAILLE_FLOTTE];
    int taille_matrice = 10;
    //choisirTaille(&taille_matrice);

    Matrice *matriceAdversaire = genererMatriceVide("Matrice de l'adversaire", taille_matrice);
    Matrice *matriceJoueur = genererMatriceVide("Matrice du joueur", taille_matrice);
    afficherMatrice(matriceJoueur);
    printf("\n");

    /*
    genererArmadaJoueur(matriceJoueur,armadaJoueur);
    afficherArmada(armadaJoueur);
    */

    printf("Test placement aleatoire : \n");
    placementAleatoire(matriceJoueur, armadaJoueur);

    return EXIT_SUCCESS;
}

