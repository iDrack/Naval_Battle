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
    printf("Imaginons un tir en 3,4 ! Voyons le retour du tableau : \n");
    int choixTir = 3;
    int **tab = fonctionTir(3, 4, choixTir, 1, matriceJoueur);
    int tmp_taille = 0;
    if(choixTir == 0){
        tmp_taille = 1;
    } else if(choixTir == 1){
        tmp_taille = matriceJoueur->taille;
    } else if(choixTir == 4) {
        tmp_taille = 9;
    } else {
        tmp_taille = 5;
    }
    for(int i = 0; i < tmp_taille; i++){
        printf("[%d][0] = %d [%d][1] = %d \n", i, tab[i][0], i, tab[i][1]);
    }
    // -------- Zone Test --------

    return EXIT_SUCCESS;
}
