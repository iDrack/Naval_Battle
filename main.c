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

    printf("\n");

    /*
    // ---------- ZONE TEST ----------
    printf("Creation d'un navire de type DESTROYER. \n");
    NavireType le_type = DESTROYER;
    int la_taille = getTailleNavire(le_type);
    printf("Placement du navire en : \n");
    int posX[la_taille], posY[la_taille];
    for(int i = 0; i < la_taille; i++){
        posX[i] = (i+2); printf(" X%d ", posX[i]);
        posY[i] = 2; printf(" Y%d ", posY[i]);
    }
    printf("\n");
    placementNavire(matriceJoueur, le_type, posX, posY);
    afficherMatrice(matriceJoueur);

    // ---------- ZONE TEST ----------
    */

    return EXIT_SUCCESS;
}

