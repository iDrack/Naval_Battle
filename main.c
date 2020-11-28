#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction.h"

int main(){
    srand(time(NULL));
    Navire *armadaJoueur[TAILLE_FLOTTE];
    Navire *armadaAdversaire[TAILLE_FLOTTE];
    int taille_matrice = 10, choix=0;

    // ----- Menu Principal -----
    
    printf("\nBienvenue dans la bataille navale.\n\n");
    choisirTaille(&taille_matrice);
    Matrice *matriceAdversaire = genererMatriceVide("Matrice de l'adversaire", taille_matrice);
    Matrice *matriceJoueur = genererMatriceVide("Matrice du joueur", taille_matrice);
    while(choix<1 || choix>2){
        printf("Voulez-vous créer votre armada ?\n1. Oui\n2. Non\n>");
        scanf("%d",&choix);
        printf("\n");
    }
    if(choix==1){
        genererArmadaJoueur(matriceJoueur,armadaJoueur); //Quand le joueur veut choisir ses navires
    }else if(choix==2){
        placementAleatoire(matriceJoueur, armadaJoueur); //Quand le joueur ne place pas lui meme ses navires
    }
    placementAleatoire(matriceAdversaire, armadaAdversaire); //Generation de la grille de l'adversaire
    afficherMatrice(matriceAdversaire);
    puts("");
    afficherMatrice(matriceJoueur);
    afficherArmada(armadaJoueur);
    
    // ---- Fin Menu Principal ----

/*
    // -------- Zone Test --------

    int toucheJoueur; // Variable � mettre � 0 de base !
    int joueurTirSpecial; // Idem, � mettre � 0.

    // -> ".. � condition qu'au tour pr�c�dent il ait touch� un bateau .." --> variable toucheJoueur = 1
    // --> ".. et qu'il n'ait pas utilis� de tir sp�cial " --> variable joueurTirSpecial = 0
    // Imaginons que le joueur a touch� au dernier tour jouer, alors toucheJoueur = 1.
    toucheJoueur = 1;
    // Imaginons qu'il n'a pas utilis� de tir sp�cial au dernier tour jouer, alors joueurTirSpecial = 0;
    joueurTirSpecial = 0;

    printf("Avant : toucheJoueur : %d && joueurTirSpecial : %d \n", toucheJoueur, joueurTirSpecial);

    //afficherArmada(armadaAdversaire);
    effectuerTir(matriceAdversaire, armadaJoueur, armadaAdversaire, &toucheJoueur, &joueurTirSpecial);

    printf("Apres : toucheJoueur : %d && joueurTirSpecial : %d \n", toucheJoueur, joueurTirSpecial);
    // NOTE :
    // -> cf 'x' et '+' � r�gler.

    // -------- Zone Test --------
*/
    return EXIT_SUCCESS;
}
