#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int main(){
    Matrice *m = genererMatriceVide("Matrice du joueur");
    afficherMatrice(m);

    return EXIT_SUCCESS;
}

