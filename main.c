#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int main(){
    int taille_matrice = 10;
    choisirTaille(&taille_matrice);

    Matrice *matriceAdversaire = genererMatriceVide("Matrice de l'adversaire", taille_matrice);
    Matrice *matriceJoueur = genererMatriceVide("Matrice du joueur", taille_matrice);

    afficherMatrice(matriceAdversaire);
    afficherMatrice(matriceJoueur);

    return EXIT_SUCCESS;
}

