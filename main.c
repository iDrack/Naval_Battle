// Réalisé par Charles Kempa & Thomas Dignoire.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

int main(){
    srand(time(NULL));
    // Initialisation de toutes les variables
    Navire *armadaJoueur[TAILLE_FLOTTE];
    Navire *armadaAdversaire[TAILLE_FLOTTE];
    int taille_matrice = 10, choix = 0, tour=1, toucheJoueur = 0, joueurTirSpecial = 0;

    // ----- Menu Principal -----

    printf("\nBienvenue dans la bataille navale.\n\n");
    choisirTaille(&taille_matrice); //Choix de la taille du champs de bataille.
    // Initialisation des matrice
    Matrice *matriceAdversaire = genererMatriceVide("Matrice de l'adversaire", taille_matrice);
    Matrice *matriceIntermediaire = genererMatriceVide("Matrice de l'adversaire", taille_matrice);
    Matrice *matriceJoueur = genererMatriceVide("Matrice du joueur", taille_matrice);
    // Laisse le choix au joueur de creer sa flotte ou non.
    while(choix < 1 || choix > 2){
        printf("Voulez-vous créer votre armada ?\n1. Oui\n2. Non\n>");
        scanf("%d",&choix);
        printf("\n");
    }
    if(choix == 1){
        genererArmadaJoueur(matriceJoueur,armadaJoueur); // Quand le joueur veut choisir ses navires.
    }else if(choix==2){
        placementAleatoire(matriceJoueur, armadaJoueur); // Quand le joueur ne place pas lui meme ses navires.
    }
    placementAleatoire(matriceAdversaire, armadaAdversaire); // Generation de la grille de l'adversaire.

    // ---- Fin Menu Principal ----

    // ----- Boucle Principal -----
    // La partie s'arrête une fois qu'un joueur n'a plus de flotte.
    while(nbNaviresCoulees(armadaJoueur) != 5 && nbNaviresCoulees(armadaAdversaire) != 5){
        // Le joueur joue sur les tours impairs car il commence.
        printf("\033[0;36mTour n°%d, \033[0m",tour);
        if(tour % 2 == 1){
            // Durant le tour du joueur, on affiche sa grille, sa flotte ainsi que ses tirs disponibles.
            printf("\033[0;36mjoueur.\033[0m\n\n");
            afficherPlateauDeJeu(matriceJoueur, matriceIntermediaire);
            afficherArmada(armadaJoueur);
            printf("Nombre de navires ennemis restants:\033[0;36m% d\033[0m\n\n",(5-nbNaviresCoulees(armadaAdversaire)));
            // Ici, on demande au joueur le tir qu'il veut faire ainsi que les coordonnées.
            effectuerTir(matriceAdversaire, matriceIntermediaire, armadaJoueur, armadaAdversaire, &toucheJoueur, &joueurTirSpecial);
        }else{
            // Durant le tour de l'IA, on affiche la matrice intermédiaire, une matrice où le joueur peut voir là où il a tiré mais il ne verra pas les bateaux adverses.
            // Puis on fait jouer l'automate.
            printf("\033[0;36mordi.\033[0m\n\n");
            afficherPlateauDeJeu(matriceJoueur, matriceIntermediaire);
        }
        puts("-------------------------------------------------------------------------------------------");
        // On augmente le nombre de tours.
        tour++;
    }

    if(nbNaviresCoulees(armadaAdversaire) == 5){
        // Si l'IA n'a plus de navire, le joueur gagne.
        printf("\n\033[0;33mFélicitation Joueur, vous avez gagné !\033[0m\n");
    } else if(nbNaviresCoulees(armadaJoueur) == 5){
        // Si le joueur n'a plus de navire, l'IA gagne.
        printf("\n\033[0;31mMalheureusement votre flotte a été détruite. Défaite.\033[0m\n");
    }

    printf("Champ de bataille : \n");
    afficherPlateauDeJeu(matriceJoueur, matriceAdversaire);
    printf("Flottes : \n");
    afficherArmada(armadaJoueur);
    afficherArmada(armadaAdversaire);

    // Libération de la mémoire.
    free(matriceJoueur);
    free(matriceAdversaire);

    // --- Fin Boucle principal ---

/*
    // -------- Zone Test --------

    //

    // -------- Zone Test --------
*/

    return EXIT_SUCCESS;
}
