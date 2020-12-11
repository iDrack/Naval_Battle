// Réalisé par Charles Kempa & Thomas Dignoire.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

int main(){
    srand(time(NULL));
    // Initialisation de toutes les variables
    Navire *armadaJoueur[TAILLE_FLOTTE], *armadaAdversaire[TAILLE_FLOTTE];
    // Il faut générer les matrices au moins une fois.
    Matrice *matriceAdversaire = genererMatriceVide("Matrice de l'adversaire", 10); // Matrice de l'IA.
    Matrice *matriceIntermediaire = genererMatriceVide("Matrice de l'adversaire", 10); // Matrice Brouillard pour le joueur.
    Matrice *matriceJoueur = genererMatriceVide("Matrice du joueur", 10); // Matrice du joueur.
    // Pareil pour les flottes.
    placementAleatoire(matriceJoueur, armadaJoueur);
    placementAleatoire(matriceAdversaire, armadaAdversaire);
    int taille_matrice = 10, choix = 0, choix2 = 0, tour, toucheJoueur = 0, joueurTirSpecial = 0;
    IA ordinateur;

    // Initialisation de l'IA :
    initialiserIA(matriceAdversaire, &ordinateur, 10);

    // ----- Menu Principal -----
    printf("Ennemis en approche !\nÀ vos postes !\n\n");
    while(choix2 < 1 || choix2 > 2){
        printf("Voulez-vous charger une partie ?\n1. Oui\n2. Non\n>");
        scanf("%d",&choix2);
        printf("\n");
    }

    if(choix2 == 1){
        choix2 = charger(&tour, matriceJoueur, matriceAdversaire, matriceIntermediaire, ordinateur.matScanner,armadaJoueur, armadaAdversaire);
    }

    if(choix2 == 2){
        tour = 1;
        choisirTaille(&taille_matrice); //Choix de la taille du champs de bataille.
        // Initialisation des matrices.
        matriceAdversaire = genererMatriceVide("Matrice de l'adversaire", taille_matrice); // Matrice de l'IA.
        matriceIntermediaire = genererMatriceVide("Matrice de l'adversaire", taille_matrice); // Matrice Brouillard pour le joueur.
        matriceJoueur = genererMatriceVide("Matrice du joueur", taille_matrice); // Matrice du joueur.
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
    }

    // Initialisation de l'IA :
    initialiserIA(matriceAdversaire, &ordinateur, taille_matrice);

    // ---- Fin Menu Principal ----

    // ----- Boucle Principal -----

    // La partie s'arrête une fois qu'un joueur n'a plus de flotte.
    while(nbNaviresCoulees(armadaJoueur) != 5 && nbNaviresCoulees(armadaAdversaire) != 5){
        // Le joueur joue sur les tours impaires et commence donc la partie.
        printf("\033[0;36mTour n°%d, \033[0m",tour);
        if(tour % 2 == 1){
            // Durant le tour du joueur, on affiche sa grille, sa flotte ainsi que ses tirs disponibles.
            printf("\033[0;36mà vous de jouer.\033[0m\n\n");
            afficherPlateauDeJeu(matriceJoueur, matriceIntermediaire);
            printf("Votre armada : \n");
            afficherArmada(armadaJoueur);
            printf("Nombre de navires ennemis restants :\033[0;36m %d\033[0m\n\n",(5-nbNaviresCoulees(armadaAdversaire)));
            // Ici, on demande au joueur le tir qu'il veut faire ainsi que les coordonnées.
            effectuerTir(matriceAdversaire, matriceIntermediaire, matriceJoueur, ordinateur.matScanner, armadaJoueur, armadaAdversaire, &toucheJoueur, &joueurTirSpecial, tour);
        }else{
            // Durant le tour de l'IA, on affiche la matrice intermédiaire, une matrice où le joueur peut voir là où il a tiré mais il ne verra pas les bateaux adverses.
            // Puis on fait jouer l'automate.
            printf("\033[0;36mvotre adversaire a joué.\033[0m\n\n");
            tourDeNotreIA(&ordinateur, matriceJoueur, armadaJoueur, armadaAdversaire);
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

    // Affichage des statstiques :
    printf("Champ de bataille : \n");
    afficherPlateauDeJeu(matriceJoueur, matriceAdversaire);
    printf("Flottes : \n");
    printf("Votre armada : \n");
    afficherArmada(armadaJoueur);
    puts("-------------------------------------------------------------------------------------------");
    printf("\nArmada adverse : \n");
    afficherArmada(armadaAdversaire);

    // --- Fin Boucle principal ---

    // On libére toute la mémoire prise.
    free(matriceAdversaire);
    free(matriceIntermediaire);
    free(matriceJoueur);
    free(ordinateur.matScanner);

    return EXIT_SUCCESS;
}

