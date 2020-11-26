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

    genererArmadaJoueur(matriceJoueur,armadaJoueur); //Quand le joueur veut choisir ses navires
    //placementAleatoire(matriceJoueur, armadaJoueur); //Choix par defaut
    placementAleatoire(matriceAdversaire, armadaAdversaire); //Generation de la grille de l'adversaire

    afficherArmada(armadaJoueur);

    // -------- Zone Test --------

    effectuerTir(matriceAdversaire, armadaJoueur, armadaAdversaire);

    // -------- Zone Test --------
    */
    return EXIT_SUCCESS;
}
