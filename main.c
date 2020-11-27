#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction.h"

int main(){
    srand(time(NULL));
    Navire *armadaJoueur[TAILLE_FLOTTE];
    Navire *armadaAdversaire[TAILLE_FLOTTE];
    int taille_matrice = 10;
    //choisirTaille(&taille_matrice);

    Matrice *matriceAdversaire = genererMatriceVide("Matrice de l'adversaire", taille_matrice);
    Matrice *matriceJoueur = genererMatriceVide("Matrice du joueur", taille_matrice);
    //afficherMatrice(matriceAdversaire);
    //afficherMatrice(matriceJoueur);

    //genererArmadaJoueur(matriceJoueur,armadaJoueur); //Quand le joueur veut choisir ses navires
    placementAleatoire(matriceJoueur, armadaJoueur); //Choix par defaut
    placementAleatoire(matriceAdversaire, armadaAdversaire); //Generation de la grille de l'adversaire

    afficherArmada(armadaJoueur);

    // -------- Zone Test --------

    afficherArmada(armadaAdversaire);
    effectuerTir(matriceAdversaire, armadaJoueur, armadaAdversaire);
    // NOTE :
    // -> cf 'x' et '+' à régler.
    // -> ".. à condition qu'au tour précédent il ait touché un bateau .." --> variable que l'on peut mettre dans le main que le l'on met à jour lorsque je place un "#" sur la grille. :)
    // --> ".. et qu'il n'ait pas utilisé de tir spécial " --> Pareil avec une vraible qu'on gére ici et que l'on met à jour. :)
    // ++ : -> mettre un message lorsque rien touché (easy aussi ^^).

    // -------- Zone Test --------

    return EXIT_SUCCESS;
}
