#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

int getTailleNavire(NavireType nt){
    /*
        Permet d'obtenir la taille d'un Navire.
        Param. :
            nt : le type de notre navire, type : NavireType.
        Retourn :
            Retourne la taille, un entier.
    */
    switch(nt){
        case PORTEAVION:
            return 5;
            break;
        case CROISER:
            return 4;
            break;
        case DESTROYER:
            return 3;
            break;
        case SOUSMARIN:
            return 3;
            break;
        case TORPILLEUR:
            return 2;
            break;
    }
    return -1;
}

TirType getTypeTirSpecial(NavireType nt){
    /*
        Permet d'obtenir le type de tir spéciale d'un navire.
        Param. :
            nt : le type de notre navire, type : NavireType.
        Retourn :
            Retourne le type, un enum.
    */
    switch(nt){
        case PORTEAVION:
            return BOMBARDEMENT;
            break;
        case CROISER:
            return CANONS;
            break;
        case SOUSMARIN:
            return BARAGE;
            break;
        default:
            return NORMAL;
            break;
    }
}

Navire *genererNavire(NavireType nt, Matrice *m){
    /*
        Génére un navire selon le type souhaitée pour la matrice passée en paramètre.
        Param. :
            nt : type de navire voulue, type : NavireType.
            m : pointeur de la matrice que l'on veut modifier, type : pointeur de Matrice.
        Return :
            Navire venant d'être généree, type : Pointeur de Navire.
    */
    Navire *n = malloc(sizeof(Navire));
    n->nom = nt;
    n->etat = OK;
    n->matrice = m; // Pointeur de la matrice afin de connaitre la grille/matrice d'origine.

    n->taille = getTailleNavire(nt);

    n->posX = (int*)malloc(n->taille * sizeof(int));
    n->posY = (int*)malloc(n->taille * sizeof(int));

    n->armementPrincipale = getTypeTirSpecial(nt);
    if(nt == CROISER){
        n->armementSecondaire = CANONS;
    } else {
        n->armementSecondaire = NORMAL;
    }

    return n;
}

void placementNavire(Matrice *m, Navire *n, int x, int y, Orientation o){
    /*
        Permet de placer un navire selon des coordonées et une orientation sur la matrice voulu.
        Param. :
            m : matrice que l'on veut modifier, type : pointeur de Matrice.
            n : navire a placer, type : pointeur de Navire.
            x : coordonee de l'axe des abcisses, type : int.
            y : coordonne de l'axe des ordonnees, type : int.
            o : orientation voulu du navire, type : Orientation.
    */
    int posX[n->taille], posY[n->taille];
    //Calcule des coordonnés en fonction de l'orientation
    if(o == H){
        for(int i = 0; i < n->taille; i++){
            posX[i] = x+i;
            posY[i] = y;
        }
    } else if(o == V){
        for(int i = 0; i < n->taille; i++){
            posX[i] = x;
            posY[i] = y+i;
        }
    }
    //Ajout des coordonnées dans le navire et affichage sur la matrice
    for(int i = 0; i < n->taille; i++){
        n->posY[i] = posX[i];
        n->posX[i] = posY[i];
        m->value[posY[i]][posX[i]] = 'O';
    }
}

Matrice* genererMatriceVide(char *titre, int taille_matrice){
    /*
        Permet de générer une matrice vide.
        Param :
            titre : nom que l'on veut donner a la matrice, type: chaine de caractere.
            taille_matrice : taille de la matrice, type : int.
        Return:
            Matrice venant d'etre generer, type: pointeur vers Matrice.
    */
    Matrice *m = malloc(sizeof(Matrice));
    m->titre = titre;
    m->taille = taille_matrice;

    m->value = (char **)malloc(m->taille * sizeof(char*)); // Mémoire (lignes).
    // Mémoire (colonnes).
    for(char i = 0; i < m->taille; i++){
        m->value[i] = (char *)malloc(m->taille * sizeof(char));
    }
    // Initialisation.
    for(int i = 0; i < m->taille; i++){
        for(int j = 0; j < m->taille; j++){
            m->value[i][j] = '.';
        }
    }

    return m;
}

void afficherMatrice(Matrice *m){
    /*
        Permet d'afficher dans la sortie standard la matrice passée en paramètre.
        Param. :
            m : pointeur de la matrice que l'on veut afficher, type : pointeur de Matrice.
    */
    printf("%s : \n", (m->titre));
    printf("     ");
    for(int i = 0; i < m->taille; i++) printf("%c ", 65+i);
    printf("[y] \n");
    for(int i = 0; i < m->taille; i++){
        if(i+1 >= 10) printf(" %d  ", i+1);
        else printf("  %d  ", i+1);

        for(int j = 0; j < m->taille; j++){
            if(m->value[i][j]=='O')printf("\033[0;32m%c \033[0m",m->value[i][j]);
            else if(m->value[i][j]=='.')printf("\033[0;34m%c \033[0m",m->value[i][j]);
            else if(m->value[i][j]=='#')printf("\033[0;31m%c \033[0m",m->value[i][j]);
            else printf("%c ", m->value[i][j]);
        }
        printf("\n");
    }
    printf(" [x] \n\n");
}

void choisirTaille(int *ptr){
    /*
        Permet de deternimer la taille d'une matrice.
        Param. :
            ptr : pointeur de la taille de matrice que l'on veut modifier, type: pointeur d'int.
    */
    int taille_matrice;
    printf("Choisissez la taille de la grille de jeu (10 mini, 26 max) : ");
    scanf("%d", &taille_matrice);
    printf("\n");
    while(taille_matrice > 26 || taille_matrice < 10){
        printf("Choisissez une taille conforme de grille (10 mini, 26 max) : ");
        scanf("%d", &taille_matrice);
        printf("\n");
    }

    *ptr = taille_matrice;
}

void afficherNavirePos(Navire *n){
    /*
        Permet d'afficher les coordonees de tout un navire.
        Param. :
            n : navire dont on veut afficher les coordonnees, type: pointeur de Navire.
    */
    printf("\nPosition : ");
    for(int i=0;i<n->taille;i++){
        if((n->posX[i]+1)>9){
            printf("%d%c  ",n->posX[i]+1,n->posY[i]+65);
        }else {
            printf(" %d%c  ",n->posX[i]+1,n->posY[i]+65);
        }
    }
}

void afficherNavireArmement(Navire *n){
    /*
        Permet d'afficher l'armement disponible d'un navire.
        Param. :
            n : navire dont on veut afficher l'armement, type: pointeur de Navire.
    */
    printf("Armement disponible : ");
    switch(n->nom){
        case PORTEAVION:
            if(n->armementPrincipale == BOMBARDEMENT){
                printf("Bombardement (carre de 3x3) et Tir normal. ");
            } else {
                if(n->armementPrincipale == INDISPONIBLE){
                    printf("Aucune. ");
                } else {
                    printf("Tir normal. ");
                }
            }
            break;
        case CROISER:
            if(n->armementPrincipale == CANONS){
                printf("Batterie de canon (en 'x'");
                if(n->armementSecondaire == CANONS){
                    printf(" et en '+') et Tir normal. ");
                } else {
                    printf(") et Tir normal. ");
                }
            } else if(n->armementSecondaire == CANONS) {
                printf("Batterie de canon (en '+') et Tir normal. ");
            } else {
                if(n->armementPrincipale == INDISPONIBLE){
                    printf("Aucune. ");
                } else {
                    printf("Tir normal. ");
                }
            }
            break;
        case DESTROYER:
            if(n->armementPrincipale == INDISPONIBLE){
                printf("Aucune. ");
            } else {
                printf("Tir normal. ");
            }
            break;
        case SOUSMARIN:
            if(n->armementPrincipale == BARAGE){
                printf("Tir de barage (ligne ou colonne) et Tir normal. ");
            } else {
                if(n->armementPrincipale == INDISPONIBLE){
                    printf("Aucune. ");
                } else {
                    printf("Tir normal. ");
                }
            }
            break;
        case TORPILLEUR:
            if(n->armementPrincipale == INDISPONIBLE){
                printf("Aucune. ");
            } else {
                printf("Tir normal. ");
            }
            break;
        default:
            printf("Aucune armement disponible. ");
            break;
    }
}

void afficherArmada(Navire **armada){
    /*
        Permet d'afficher l'armada (soit tous les navires).
        Param. :
            armada : tableau de pointeur de navire, type: tableau de pointeur de navire.
    */
    //puts("Votre armada : ");
    char* st;
    char* st2;
    for(int i = 0; i < TAILLE_FLOTTE; i++){
        NavireType nt = armada[i]->nom;
        switch(nt){
            case PORTEAVION:
                st = "Porte-avion";
                break;
            case CROISER:
                st = "Croiser  ";
                break;
            case DESTROYER:
                st = "Destroyer";
                break;
            case SOUSMARIN:
                st = "Sous-marin";
                break;
            case TORPILLEUR:
                st = "Torpilleur";
                break;
            default:
                st = "";
                break;
        }

        Etat et = armada[i]->etat;
        switch(et){
            case OK:
                st2 = "OK";
                break;
            case TOUCHE:
                st2 = "TOUCHÉ";
                break;
            case COULE:
                st2 = "COULÉ";
                break;
            default:
                st2 = "";
                break;
        }
        if(st != "") {
            if(st2 == "OK") printf("\033[0;36m #%d\033[0m %s\tEtat : \033[0;32m%s\033[0m\n", i, st, st2);
            else if(st2 == "TOUCHÉ") printf("\033[0;36m #%d\033[0m %s\tEtat : \033[0;33m%s\033[0m\n", i, st, st2);
            else if(st2 == "COULÉ") printf("\033[0;36m #%d\033[0m %s\tEtat : \033[0;31m%s\033[0m\n", i, st, st2);
            else printf("\033[0;36m #%d\033[0m %s\tEtat : %s\n", i, st, st2);
        }
        afficherNavireArmement(armada[i]);
        afficherNavirePos(armada[i]);
        printf("\n");
    }
}

int sortieMatrice(Matrice *m, int x, int y, int taille, Orientation o){
    /*
        Fonction permettant d'assurer qu'un nevire ne sort pas de la matrice.
        Param. :
            m : matrice que l'on veut controller, Type : pointeur de Matrice.
            x : valeur de l'axe des abcisse, Type : int.
            y : valeur de l'axe des ordonnees, Type int.
            taille : taille du navire a poser, Type: int.
            o : Orientation que l'on utilise, Type Orientation.
        Return : Boolean int.
    */
    if(x > m->taille || y > m->taille)return 1;
    if(o==V && x+taille > m->taille)return 1;
    if(o==H && y+taille > m->taille)return 1;
    return 0;
}

int naviresColles(Matrice *m, int x, int y, int taille, Orientation o, int** tab){
    /*
        Fonction permettant d'assurer que les navires ne se touchent pas.
        Param. :
            m : matrice que l'on veut controller, Type : pointeur de Matrice.
            x : valeur de l'axe des abcisse, Type : int.
            y : valeur de l'axe des ordonnees, Type int.
            taille : taille du navire a poser, Type: int.
            o : Orientation que l'on utilise, Type Orientation.
            tab : matrice temporaire representat la ou il reste des emplacement libre sur m, Type: pointeur de pointeur de int.
        Return : Boolean int.
    */
    int maxi=m->taille-1, mini=0;
    for(int i=0;i<taille;i++){
        if(o==V){
            if(tab[y+i][x] == 1)return 1;
        }else if(o==H){
            if(tab[y][x+i] == 1)return 1;
        }
    }
    if(o == V){
        for(int i=0;i<taille;i++){
            tab[y+i][x] = 1;
            if(x+1 <= maxi) tab[y+i][x+1] = 1;
            if(x-1 >= mini) tab[y+i][x-1] = 1;
        }
        if(y-1 >= mini) tab[y-1][x] = 1;
        if(y*taille <= maxi) tab[y+taille][x] = 1;
    }else if(o == H){
        for(int i=0;i<taille;i++){
            tab[y][x+i] = 1;
            if(y+1 <= maxi) tab[y+1][x+i] = 1;
            if(y-1 >= mini) tab[y-1][x+i] = 1;
        }
        if(x-1 >= mini) tab[y][x-1] = 1;
        if(x+taille <= maxi) tab[y][x+taille] = 1;
    }
    return 0;
}

void genererArmadaJoueur(Matrice *m, Navire **armada){
    /*
        Génére l'armada du joueur.
        Param. :
            m : matrice ou l'on ajoute, type : pointeur de navire.
            armada : liste des navire du joueur, type : liste de pointeur de Navire.
    */
    int **tableau2D = (int **)malloc(m->taille * sizeof(int*)); // Mémoire (lignes).
    // Mémoire (colonnes).
    for(char i = 0; i < m->taille; i++){
        tableau2D[i] = (int *)malloc(m->taille * sizeof(int));
    }
    // Initialisation à vide.
    for(int i = 0; i < m->taille; i++){
        for(int j = 0; j < m->taille; j++){
            tableau2D[i][j] = 0;
        }
    }

    int tmp, x;
    NavireType nt;
    Orientation o;
    char y, tmpO;

    for(int i = 0; i < TAILLE_FLOTTE; i++){
        printf("Choisisser un navire:\n1. Torpilleur\n2. Destroyer\n3. Sous-marin\n4. Croiser\n5. Porte-avion\n> ");
        scanf("%d", &tmp);

        while(tmp < 1 || tmp > 5){
            printf("\nCe navire n'existe pas !\n\n");
            printf("Choisisser un navire:\n1. Torpilleur\n2. Destroyer\n3. Sous-marin\n4. Croiser\n5. Porte-avion\n> ");
            scanf("%d", &tmp);
        }
        switch(tmp){
            case 5:
                nt = PORTEAVION;
                break;
            case 4:
                nt = CROISER;
                break;
            case 3:
                nt = SOUSMARIN;
                break;
            case 2:
                nt = DESTROYER;
                break;
            case 1:
                nt = TORPILLEUR;
                break;
        }

        Navire *n = malloc(sizeof(Navire));
        n->etat = OK;
        n->matrice = m;
        n->nom = nt;
        n->taille = getTailleNavire(nt);
        n->posX = (int*)malloc(n->taille * sizeof(int));
        n->posY = (int*)malloc(n->taille * sizeof(int));
        n->armementPrincipale = getTypeTirSpecial(nt);
        if(nt == CROISER){
            n->armementSecondaire = CANONS;
        } else {
            n->armementSecondaire = NORMAL;
        }
        armada[i] = n;

        //Demande des coordonées
        printf("\nPosition ?");
        printf("\ny=");
        scanf("%s",&y);
        //On passe y en majuscule
        if(y >= 97 && y <= 122)y = y-32;
        //Vérification de la position y, si c'est bien une lettre
        while(!( y >= 65 && y <= 90)){
            printf("\nHo non ! Y n'est pas une lettre !");
            printf("\ny=");
            scanf("%s",&y);
            //On passe y en majuscule
            if(y >= 97 && y <= 122)y = y-32;
        }
        //On demande x
        printf("x=");
        scanf("%d",&x);
        //Demande de l'orientation
        printf("Orientation (H ou V)\n>");
        scanf("%s",&tmpO);
        //Vérification de l'orientation
        while(tmpO != 72 && tmpO != 86 && tmpO != 104 && tmpO != 118 ){
            //Si le joueur se trompe de characètre, on lui redemande
            printf("\nCette orientation n'existe pas !\n");
            printf("Orientation (H ou V)\n>");
            scanf("%s",&tmpO);
        }
        if(tmpO == 104 || tmpO == 118)tmpO = tmpO-32;
        if(tmpO == 72) o = H; else if(tmpO == 86) o = V; // 72 et 86 correspond au code ascii de H et V.

        while(sortieMatrice(m,(x-1),(y-65),getTailleNavire(nt),o) == 1){
            printf("\nHo non ! Le navire est hors du champs de bataille !\n");
            //Demande des coordonées
            printf("\nPosition ?");
            printf("\ny=");
            scanf("%s",&y);
            //On passe y en majuscule
            if(y >= 97 && y <= 122)y = y-32;
            //Vérification de la position y, si c'est bien une lettre
            while(!( y >= 65 && y <= 90)){
                printf("\nHo non ! Y n'est pas une lettre !");
                printf("\ny=");
                scanf("%s",&y);
                //On passe y en majuscule
                if(y >= 97 && y <= 122)y = y-32;
            }
            //On demande x
            printf("x=");
            scanf("%d",&x);
            //Demande de l'orientation
            printf("Orientation (H ou V)\n>");
            scanf("%s",&tmpO);
            //Vérification de l'orientation
            while(tmpO != 72 && tmpO != 86 && tmpO != 104 && tmpO != 118 ){
                //Si le joueur se trompe de characètre, on lui redemande
                printf("\nCette orientation n'existe pas !\n");
                printf("Orientation (H ou V)\n>");
                scanf("%s",&tmpO);
            }
            if(tmpO == 104 || tmpO == 118)tmpO = tmpO-32;
            if(tmpO == 72) o = H; else if(tmpO == 86) o = V; // 72 et 86 correspond au code ascii de H et V.
        }

        while(naviresColles(m,(y-65),(x-1),getTailleNavire(nt),o,tableau2D) == 1){
            printf("\nHo non ! Le navire est à coté d'un autre !\n");
            //Demande des coordonées
            printf("\nPosition ?");
            printf("\ny=");
            scanf("%s",&y);
            //On passe y en majuscule
            if(y >= 97 && y <= 122)y = y-32;
            //Vérification de la position y, si c'est bien une lettre
            while(!( y >= 65 && y <= 90)){
                printf("\nHo non ! Y n'est pas une lettre !");
                printf("\ny=");
                scanf("%s",&y);
                //On passe y en majuscule
                if(y >= 97 && y <= 122)y = y-32;
            }
            //On demande x
            printf("x=");
            scanf("%d",&x);
            //Demande de l'orientation
            printf("Orientation (H ou V)\n>");
            scanf("%s",&tmpO);

            //Vérification de l'orientation
            while(tmpO != 72 && tmpO != 86 && tmpO != 104 && tmpO != 118 ){
                //Si le joueur se trompe de characètre, on lui redemande
                printf("\nCette orientation n'existe pas !\n");
                printf("Orientation (H ou V)\n>");
                scanf("%s",&tmpO);
            }
            if(tmpO == 104 || tmpO == 118)tmpO = tmpO-32;
            if(tmpO == 72) o = H; else if(tmpO == 86) o = V; // 72 et 86 correspond au code ascii de H et V.
        }

        placementNavire(m,n,(y-65),(x-1),o);
        printf("\n");
        afficherMatrice(m);
        printf("\n");
        //afficherArmada(armada);
        printf("\n");
    }

    free(tableau2D);
}

void placementAleatoire(Matrice *m, Navire **armada){
    /*
        Génére l'armada du joueur.
        Param. :
            m : matrice où l'on ajoute, type : pointeur de navire.
            armada : liste des navire du joueur ou de l'adversaire, type : liste de pointeur de Navire.
    */
    generationArmadaStandard(m, armada);
    int **tableau2D = (int **)malloc(m->taille * sizeof(int*)); // Mémoire (lignes).
    // Mémoire (colonnes).
    for(char i = 0; i < m->taille; i++){
        tableau2D[i] = (int *)malloc(m->taille * sizeof(int));
    }
    // Initialisation à vide.
    for(int i = 0; i < m->taille; i++){
        for(int j = 0; j < m->taille; j++){
            tableau2D[i][j] = 0;
        }
    }

    int aleaX, aleaY;
    int maxi = m->taille-1, mini = 0;

    for(int num = 0; num < TAILLE_FLOTTE; num++){
        int poser = 0;
        int angle;
        while(poser == 0){
            aleaX = generationIntAleatoire(maxi, mini);
            aleaY = generationIntAleatoire(maxi, mini);
            angle = generationIntAleatoire(4, 1);

            poser = 1;
            for(int i = 0; i < armada[num]->taille; i++){
                if(angle == 1){
                    if(aleaY-i >= mini && tableau2D[aleaX][aleaY-i] == 0){
                        // OK
                    } else {
                        poser = 0;
                        break;
                    }
                }

                if(angle == 2){
                    if(aleaX-i >= mini && tableau2D[aleaX-i][aleaY] == 0){
                        // OK
                    } else {
                        poser = 0;
                        break;
                    }
                }

                if(angle == 3){
                    if(aleaY+i <= maxi && tableau2D[aleaX][aleaY+i] == 0){
                        // OK
                    } else {
                        poser = 0;
                        break;
                    }
                }

                if(angle == 4){
                    if(aleaX+i <= maxi && tableau2D[aleaX+i][aleaY] == 0){
                        // OK
                    } else {
                        poser = 0;
                        break;
                    }
                }
            } // Fin de boucle, on a vérifié que le navire peut être posé.
        } // Fin de boucle, on pose le navire.

        // On le place :
        for(int i = 0; i < armada[num]->taille; i++){
            if(angle == 1){
                tableau2D[aleaX][aleaY-i] = 1;
                armada[num]->posX[i] = aleaX;
                armada[num]->posY[i] = aleaY-i;
                m->value[aleaX][aleaY-i] = 'O';
                // Espacement :
                if(aleaX+1 <= maxi) tableau2D[aleaX+1][aleaY-i] = 2;
                if(aleaX-1 >= mini) tableau2D[aleaX-1][aleaY-i] = 2;
                if(aleaY-i+1 <= maxi && tableau2D[aleaX][aleaY-i+1] != 1) tableau2D[aleaX][aleaY-i+1] = 2;
                if(aleaY-i-1 >= mini && tableau2D[aleaX][aleaY-i-1] != 1) tableau2D[aleaX][aleaY-i-1] = 2;
            }

            if(angle == 2){
                tableau2D[aleaX-i][aleaY] = 1;
                armada[num]->posX[i] = aleaX-i;
                armada[num]->posY[i] = aleaY;
                m->value[aleaX-i][aleaY] = 'O';
                // Espacement :
                if(aleaY+1 <= maxi) tableau2D[aleaX-i][aleaY+1] = 2;
                if(aleaY-1 >= mini) tableau2D[aleaX-i][aleaY-1] = 2;
                if(aleaX-i+1 <= maxi && tableau2D[aleaX-i+1][aleaY] != 1) tableau2D[aleaX-i+1][aleaY] = 2;
                if(aleaX-i-1 >= mini && tableau2D[aleaX-i-1][aleaY] != 1) tableau2D[aleaX-i-1][aleaY] = 2;
            }

            if(angle == 3){
                tableau2D[aleaX][aleaY+i] = 1;
                armada[num]->posX[i] = aleaX;
                armada[num]->posY[i] = aleaY+i;
                m->value[aleaX][aleaY+i] = 'O';
                // Espacement :
                if(aleaX+1 <= maxi) tableau2D[aleaX+1][aleaY+i] = 2;
                if(aleaX-1 >= mini) tableau2D[aleaX-1][aleaY+i] = 2;
                if(aleaY+i+1 <= maxi && tableau2D[aleaX][aleaY+i+1] != 1) tableau2D[aleaX][aleaY+i+1] = 2;
                if(aleaY+i-1 >= mini && tableau2D[aleaX][aleaY+i-1] != 1) tableau2D[aleaX][aleaY+i-1] = 2;
            }

            if(angle == 4){
                tableau2D[aleaX+i][aleaY] = 1;
                armada[num]->posX[i] = aleaX+i;
                armada[num]->posY[i] = aleaY;
                m->value[aleaX+i][aleaY] = 'O';
                // Espacement :
                if(aleaY+1 <= maxi) tableau2D[aleaX+i][aleaY+1] = 2;
                if(aleaY-1 >= mini) tableau2D[aleaX+i][aleaY-1] = 2;
                if(aleaX+i+1 <= maxi && tableau2D[aleaX+i+1][aleaY] != 1) tableau2D[aleaX+i+1][aleaY] = 2;
                if(aleaX+i-1 >= mini && tableau2D[aleaX+i-1][aleaY] != 1) tableau2D[aleaX+i-1][aleaY] = 2;
            }
        }
    }

    free(tableau2D); // On libére la mémoire utilisé avec le tableau temporaire ..
}

void generationArmadaStandard(Matrice *m, Navire **armada){
    /*
        Génére une flotte standard (soit 1 navire de chaque).
        Param. :
            m : notre matrice où l'on souhaite ajouter les navires, type : pointeur de Matrice.
            armada : notre tableau de navire (pointeur), type : tableau de pointeur de navire.
    */
    NavireType nt;

    for(int i = 0; i < TAILLE_FLOTTE; i++){
        // On place en mémoire le navire.
        armada[i] = (Navire*)malloc(sizeof(Navire));
        armada[i]->armementSecondaire = NORMAL;
        // Type de navire.
        switch(i){
            case 4:
                nt = PORTEAVION;
                break;
            case 3:
                nt = CROISER;
                armada[i]->armementSecondaire = getTypeTirSpecial(nt);
                break;
            case 2:
                nt = DESTROYER;
                break;
            case 1:
                nt = SOUSMARIN;
                break;
            case 0:
                nt = TORPILLEUR;
                break;
        }
        armada[i]->armementPrincipale = getTypeTirSpecial(nt);
        armada[i]->etat = OK;
        armada[i]->matrice = m;
        armada[i]->nom = nt;
        armada[i]->taille = getTailleNavire(nt);
        armada[i]->posX = (int*)malloc(armada[i]->taille * sizeof(int));
        armada[i]->posY = (int*)malloc(armada[i]->taille * sizeof(int));
    }
}

int generationIntAleatoire(int maximum, int minimum){
    /*
        Génére un entier aléatoire entre deux valeur.
        Param. :
            maximum : entier maxi, type : entier.
            minimum : entier mini, type : entier.
        Return :
            Retourne l'entier généré aléatoirement.
    */
    return (rand() % (maximum - minimum + 1)) + minimum;
}

int** fonctionTir(int posX, int posY, int choixTir, int direction, Matrice *m){
    /*
        Crée et alloue un tableau dynamique en fonction du tir.
        Param. :
            posX : position en x du tir, type : entier.
            posY : position en y du tir, type : entier.
            choixTir : choix du type de tir, type : entier.
            direction : direction si utilisation du tir par ligne, type : entier.
            m : la matrice correspondante, type pointeur de Matrice.
        Return :
            Retourne un tableau alloué dynamiquement.
    */
    int ligne, colonne = 2;
    int **tableau;

    if(choixTir == 0){
        ligne = 1;
    } else if(choixTir == 1){
        ligne = m->taille;
    } else if(choixTir == 4) {
        ligne = 9;
    } else {
        ligne = 5;
    }

    tableau = (int**)malloc((ligne*colonne) * sizeof(int)); // Mémoire (lignes).
    // Mémoire (colonnes).
    for(char i = 0; i < ligne; i++){
        tableau[i] = (int *)malloc(colonne * sizeof(int));
    }

    if(choixTir == 0){
        // Si c'est un tir normal.
        tableau[0][0] = posX;
        tableau[0][1] = posY;
    }

    if(choixTir == 1) {
        // Si c'est un tir en ligne (sous-marin).
        if(direction == 1){
            // Si on tir en ligne ..
            for(int i = 0; i < ligne; i++){
                tableau[i][0] = posX;
                tableau[i][1] = i;
            }
        } else {
            // Si on tir en colonne ..
            for(int i = 0; i < ligne; i++){
                tableau[i][0] = i;
                tableau[i][1] = posY;
            }
        }
    }

    if(choixTir == 2){
        // Si c'est un tir en croix.
        // On place le 1er tir :
        tableau[0][0] = posX;
        tableau[0][1] = posY;
        // Pour x :
        tableau[1][0] = posX-1;
        tableau[2][0] = posX-1;
        tableau[3][0] = posX+1;
        tableau[4][0] = posX+1;
        // Pour y :
        tableau[1][1] = posY-1;
        tableau[2][1] = posY+1;
        tableau[3][1] = posY-1;
        tableau[4][1] = posY+1;
    }

    if(choixTir == 3){
        // Si c'est un tir en plus.
        // On place le 1er tir :
        tableau[0][0] = posX;
        tableau[0][1] = posY;
        // Pour x :
        tableau[1][0] = posX-1;
        tableau[2][0] = posX+1;
        tableau[3][0] = posX;
        tableau[4][0] = posX;
        // Pour y :
        tableau[1][1] = posY;
        tableau[2][1] = posY;
        tableau[3][1] = posY-1;
        tableau[4][1] = posY+1;
    }

    if(choixTir == 4){
        // Si c'est un tir en carré.
        // On place le 1er tir :
        tableau[0][0] = posX;
        tableau[0][1] = posY;
        // Pour x :
        tableau[1][0] = posX-1;
        tableau[2][0] = posX-1;
        tableau[3][0] = posX-1;
        tableau[4][0] = posX;
        tableau[5][0] = posX;
        tableau[6][0] = posX+1;
        tableau[7][0] = posX+1;
        tableau[8][0] = posX+1;
        // Pour y :
        tableau[1][1] = posY-1;
        tableau[2][1] = posY;
        tableau[3][1] = posY+1;
        tableau[4][1] = posY-1;
        tableau[5][1] = posY+1;
        tableau[6][1] = posY-1;
        tableau[7][1] = posY;
        tableau[8][1] = posY+1;
    }

    return tableau;
}

void effectuerTir(Matrice *m, Matrice *m2, Matrice *m3, Matrice *m4, Navire **armadaJoueur, Navire **armadaAdversaire, int *toucheNavire, int *actionSpeciale, int tour){
    /*
        Effectue un tir sur la matrice vidé.
        Param. :
            m : pointeur de la matrice que le joueur attaque, type : pointeur de Matrice.
            m2 : pointeur de la matrice que le joueur attaque et que l'on affiche, type : pointeur de Matrice.
            m3 : pointeur sur la matrice du joueur, type : pointeur de Matrice.
            m4 : pointeur sur la matrice intermédiaire utilisé par l'IA, type : pointeur de Matrice.
            armadaJoueur : la flotte du joueur, type : tableau de pointeur de navire.
            armadaAdversaire : la flotte de l'adversaire, type : tableau de pointeur de navire.
            toucheNavire : on attend l'adresse d'un entier permettant de savoir si le tour d'avant il y a eu une touche ou pas, type : adresse (donc pointeur) d'entier.
            actionSpeciale : on attend aussi l'adresse d'un entier pour, cette fois, savoir s'il est possible d'effectuer un tir spéciale ou pas, type : adresse (donc pointeur) d'entier.
            tour : tour actuel, type : int
    */
    int choixTir, direction;
    int tableau_de_tir[TYPE_TIR];
    for(int i = 0; i < TYPE_TIR; i++) tableau_de_tir[i] = 0;
    tableau_de_tir[0] = 1;
    // Demander un tir spéciale (donner la liste) ou normal.
    printf("Actions possibles : \n");
    // Si le joueur a touché au dernier tour jouer et qu'il n'a pas utilisé de tir spéciale alors il le peut maintenant :
    if(*toucheNavire == 1 && *actionSpeciale == 0){
        for(int i = 1; i < TYPE_TIR; i++){
            if(tableau_de_tir[1] == 0 && armadaJoueur[i]->armementPrincipale == 1){
                printf("Tir sur toute une ligne ou colonne [1], ");
                tableau_de_tir[1] = 1;
            }

            if(tableau_de_tir[2] == 0 && armadaJoueur[i]->armementPrincipale == 2){
                printf("Tir en 'x' [2], ");
                tableau_de_tir[2] = 1;
            }

            if(tableau_de_tir[3] == 0 && armadaJoueur[i]->nom == CROISER && armadaJoueur[i]->armementSecondaire == 2){
                printf("Tir en '+' [3], ");
                tableau_de_tir[3] = 1;
            }

            if(tableau_de_tir[4] == 0 && armadaJoueur[i]->armementPrincipale == 3){
                printf("Tir en carree [4], ");
                tableau_de_tir[4] = 1;
            }
        }
    }
    printf("Sauvegarder [5], ");
    printf("Tir normal [0]. \n");
    int tmpChoix = -1;
    printf(">");
    scanf("%d", &tmpChoix);
    choixTir = tmpChoix;
    if(choixTir == 5){
        sauvegarde(armadaJoueur,armadaAdversaire, tour, m3, m2, m, m4);
        puts("\033[0;32mSauvegarde terminée.\033[0;m");
        int tmp;
        printf("\nQuitter ?\nOui [1], Non [2].\n>");
        scanf("%d", &tmp);
        while(tmp != 1 && tmp != 2){
            printf("\nQuitter ?\nOui [1], Non [2].\n>");
            scanf("%d", &tmp);
        }
        if(tmp == 1)exit(EXIT_SUCCESS);
    }
    printf("\n");
    while(choixTir < 0 || choixTir > 5 || tableau_de_tir[choixTir] != 1){
        printf("Choisissez un tir : ");
        scanf("%d", &tmpChoix);
        choixTir = tmpChoix;
        printf("\n");
    }

    // Si c'est un tir normale alors actionSpeciale est à 0, sinon ..
    if(choixTir == 0){
        *actionSpeciale = 0;
    } else { // Sinon ..
        // On consomme le tir spéciale (on le remplace par un tir normal) et on modifie la variable des tirs spéciaux :
        for(int i = 1; i < TYPE_TIR; i++){
            if(armadaJoueur[i]->armementPrincipale == 1 && choixTir == 1){
                //armadaJoueur[i]->armementPrincipale = 0;
                // On consomme le tir pour lui mais aussi pour tous les autres navires ayant la même capacité (évitant ainsi la répétition de tir spéciaux dans une flotte avec plusieurs navire de même type).
                for(int elem = 0; elem < TAILLE_FLOTTE; elem++){
                    if(armadaJoueur[elem]->armementPrincipale == 1){
                        armadaJoueur[elem]->armementPrincipale = 0;
                    }
                }
                *actionSpeciale = 1;
                break;
            }

            if(armadaJoueur[i]->armementPrincipale == 2 && choixTir == 2){
                //armadaJoueur[i]->armementPrincipale = 0;
                for(int elem = 0; elem < TAILLE_FLOTTE; elem++){
                    if(armadaJoueur[elem]->armementPrincipale == 2){
                        armadaJoueur[elem]->armementPrincipale = 0;
                    }
                }
                *actionSpeciale = 1;
                break;
            }

            if(armadaJoueur[i]->nom == CROISER && armadaJoueur[i]->armementSecondaire == 2 && choixTir == 3){
                //armadaJoueur[i]->armementSecondaire = 0;
                for(int elem = 0; elem < TAILLE_FLOTTE; elem++){
                    if(armadaJoueur[elem]->nom == CROISER && armadaJoueur[elem]->armementSecondaire == 2){
                        armadaJoueur[elem]->armementSecondaire = 0;
                    }
                }
                *actionSpeciale = 1;
                break;
            }

            if(armadaJoueur[i]->armementPrincipale == 3 && choixTir == 4){
                //armadaJoueur[i]->armementPrincipale = 0;
                for(int elem = 0; elem < TAILLE_FLOTTE; elem++){
                    if(armadaJoueur[elem]->armementPrincipale == 3){
                        armadaJoueur[elem]->armementPrincipale = 0;
                    }
                }
                *actionSpeciale = 1;
                break;
            }
        }
    }

    // On choisit la position :
    int posX = -1, posY = -1;
    printf("Choisir les coordonnées : \n");
    char tmpX;
    printf("x = ");
    scanf("%s", &tmpX);
    posX = atoi(&tmpX);
    while(posX < 1 || posX > m->taille){
        printf("Choisir un 'x' correct : \n");
        printf("x = ");
        scanf("%s", &tmpX);
        posX = atoi(&tmpX);
        // Si c'est une petite ou grande lettre, on n'en veut pas. ^^
        if(tmpX >= 97 && tmpX <= 122 || tmpX >= 65 && tmpX <= 90) posX = -1;
    }
    posX = atoi(&tmpX);
    printf("Choisir pour 'y' maintenant : \n");
    char tmpY;
    printf("y = ");
    scanf("%s", &tmpY);
    // Si c'est en minuscule on le met en maj.
    if(tmpY >= 97 && tmpY <= 122) tmpY = tmpY-32;
    posY = tmpY-64;
    while(posY < 0 || posY > m->taille){
        printf("Choisir un 'y' correct : \n");
        printf("y = ");
        scanf("%s", &tmpY);
        // Si c'est en miniscule, on le met en maj.
        if(tmpY >= 97 && tmpY <= 122) tmpY = tmpY-32;
        posY = tmpY-64;
    }
    posY = tmpY-64;
    printf("\n");

    // Choix de la direction pour un tir en ligne ou colonne si on a choissie ce type de tir.
    if(choixTir == 1){
        printf("Effectuer un barrage sur une ligne [1] ou une colonne [0] ? \n");
        printf("Choix : ");
        scanf("%d", &direction);
        printf("\n");
    } else {
        direction = 1;
    }

    // On tir :
    //printf("ChoixTir : %d \n", choixTir);
    int **tab = fonctionTir(posX-1, posY-1, choixTir, direction, m); // On utilise notre fonction qui retourne un pointeur de tableau.
    int tmp_taille = 0;
    if(choixTir == 0){
        tmp_taille = 1;
    } else if(choixTir == 1){
        tmp_taille = m->taille;
    } else if(choixTir == 4) {
        tmp_taille = 9;
    } else {
        tmp_taille = 5;
    }

    *toucheNavire = 0; // On dit que le joueur n'a pas touché par défaut, mais si c'est le cas alors c'est mise à jour plus bas (lorsqu'on a un "#").
    // L'objectif étant de répondre à la demande : ".. à condition qu'au tour précédent il ait touché un bateau et qu'il n'ait pas utilisé de tir spécial."
    for(int i = 0; i < tmp_taille; i++){
        //printf("%d%c  ", tab[i][0]+1, 65+tab[i][1]);
        if(tab[i][0] >= 0 && tab[i][0] <= m->taille-1 && tab[i][1] >= 0 && tab[i][1] <= m->taille-1){
            if(m->value[tab[i][0]][tab[i][1]] == 'O'){
                m->value[tab[i][0]][tab[i][1]] = '#';
                if(m2 != NULL) m2->value[tab[i][0]][tab[i][1]] = '#';
                *toucheNavire = 1;
                //printf("(--> %d%c a touche ! ) ", tab[i][0]+1, 65+tab[i][1]);
                // Rechercher le(s) navire(s) de l'adversaire pour modifier le statue du navire en touché.
                int trouve = 0;
                for(int num = 0; num < TAILLE_FLOTTE; num++){
                    //printf("Navire %d : \n", num);
                    for(int ref = 0; ref < armadaAdversaire[num]->taille; ref++){
                        //printf("Pos %d%c \n", armadaAdversaire[num]->posX[ref]+1, 65+armadaAdversaire[num]->posY[ref]);
                        if(armadaAdversaire[num]->posX[ref] == tab[i][0] && armadaAdversaire[num]->posY[ref] == tab[i][1]){
                            printf("Navire touche en %d%c ! \n", tab[i][0]+1, tab[i][1]+65);
                            modifierEtatNavire(tab[i][0], tab[i][1], armadaAdversaire[num]);
                            verifierNavire(m, armadaAdversaire[num]);
                            trouve = 1;
                            break;
                        }
                        //printf("\n");
                    }

                    if(trouve == 1) break;
                }
            }

            if(m->value[tab[i][0]][tab[i][1]] == '.'){
                m->value[tab[i][0]][tab[i][1]] = 'X';
                if(m2 != NULL) m2->value[tab[i][0]][tab[i][1]] = 'X';
                printf("Ne touche rien en %d%c. \n", tab[i][0]+1, 65+tab[i][1]);
            }

            /*
            if(m->value[tab[i][0]][tab[i][1]] == '#'){
                printf("Nous avions deja touche le navire a cette endroit commandant .. \n");
            }
            */
        }
    }
    // Affichage de la matrice de l'adversaire (débug/développement) :
    //printf("\n");
    //afficherMatrice(m);
}

void modifierEtatNavire(int positionX, int positionY, Navire *n){
    /*
        Modifie l'état du navire que l'on touche en position X, Y.
        Param. :
            positionX : position x que l'on touche, type : entier.
            positionY : position y que l'on touche, type : entier.
            n : navire de l'adversaire, type : pointeur de navire.
    */

    if(n->etat != COULE){
        n->etat = TOUCHE;
        //printf("Navire touche en %d%c ! \n", positionX+1, positionY+65);
    }
}

void verifierFlotteEntiere(Matrice *m, Navire **armada){
    /*
        Permet de vérifier l'état de la flotte tout entier (vérifie s'il y a un ou plusieurs navires touchés, coulés ou non).
        Param. :
            m : pointeur de matrice se situant la flotte, type : pointeur de Matrice.
            armada : la flotte que l'on veut vérifier, type : tableau de pointeur de Navire.
    */

    // Pour chaque navire.
    for(int i = 0; i < TAILLE_FLOTTE; i++){
        // Pour chaque taille de navire.
        for(int ref = 0; ref < armada[i]->taille; ref++){
            // On récup. la position.
            int x = armada[i]->posX[ref];
            int y = armada[i]->posY[ref];
            if(m->value[x][y] == '#'){
                modifierEtatNavire(x, y, armada[i]);
                verifierNavire(m, armada[i]);
            }
        }
    }
}

void verifierNavire(Matrice *m, Navire *n){
    /*
        Permet de vérifier l'état d'un seul navire de l'armada passé en paramètre (vérifie s'il est coulé ou non).
        Param. :
            m : pointeur de matrice se situant la flotte, type : pointeur de Matrice.
            n : navire à vérifier, type : pointeur de navire.
    */

    if(n->etat == TOUCHE){
        int x, y, compteur = 0;
        for(int i = 0; i < n->taille; i++){
            x = n->posX[i];
            y = n->posY[i];
            if(m->value[x][y] == '#') compteur++;
        }

        if(compteur == n->taille){
            n->etat = COULE;
            n->armementPrincipale = 4;
            n->armementSecondaire = 4;
            //printf("Le navire est en train de couler .. \n");
        }
    } else {
        if(n->etat == COULE){
            //printf("Navire est deja coulé .. \n");
        }

        if(n->etat == OK){
            //printf("Navire sans probleme. \n");
        }
    }
}

int nbNaviresCoulees(Navire **armada){
    /*
        Permet de retourner le nombre de navire encore en jeu de l'armada séléctionné.
        Param. :
            armada : armada que l'on veut analyser, type : tableau de pointeurs de Navire.
    */
    int ret = 0;
    for(int i=0;i<TAILLE_FLOTTE;i++){
        if(armada[i]->etat == COULE)ret++;
    }
    return ret;
}

void sauvegarde(Navire **aJoueur, Navire **aAdversaire, int tour, Matrice *mJ, Matrice *mI, Matrice *mA, Matrice *mIA){
    /*
        Permet de sauvegarder une partie
        Param. :
            aJoueur : armada du joueur, type : tableau de pointeurs de Navire.
            aAdversaire : aramda de l'IA, type : tableau de pointeurs de Navire.
            tour : tour auquel nous avons fait la sauvegarde, type : int.
            mJ : matrice du joueur, type : pointeur de Matrice.
            mI : matrice intermédiaire, type : pointeur de Matrice.
            mA : matrice de l'adversaire, type : pointeur de Matrice.
            mIA : matrice intermédiaire utilisé par l'IA, type : pointeur de Matrice.
    */
    char n, e, o;
    int x, y;
    FILE* f;
    f = fopen(".save","w");
    fprintf(f,"%d %d\n",tour,mJ->taille);

    for(int i=0; i<TAILLE_FLOTTE;i++){
        switch(aJoueur[i]->nom){
            case PORTEAVION:
                n = 'P';
                break;
            case CROISER:
                n = 'C';
                break;
            case DESTROYER:
                n = 'D';
                break;
            case SOUSMARIN:
                n = 'S';
                break;
            case TORPILLEUR:
                n = 'T';
                break;
        }

        switch(aJoueur[i]->etat){
            case OK:
                e = 'O';
                break;
            case TOUCHE:
                e = 'T';
                break;
            case COULE:
                e = 'C';
                break;
        }
        fprintf(f,"%c%c",n,e);

        for(int j=0;j<aJoueur[i]->taille;j++){
            x=aJoueur[i]->posX[j];
            y=aJoueur[i]->posY[j];
            fprintf(f,"%d%d",x,y);
        }
        fprintf(f,"\n");
    }

    for(int i=0;i<mJ->taille;i++){
        for(int j=0;j<mJ->taille;j++){
            fprintf(f,"%c",mJ->value[i][j]);
        }
        fprintf(f,"\n");
    }

    // La même chose pour l'adversaire
    for(int i=0; i<TAILLE_FLOTTE;i++){
        switch(aAdversaire[i]->nom){
            case PORTEAVION:
                n = 'P';
                break;
            case CROISER:
                n = 'C';
                break;
            case DESTROYER:
                n = 'D';
                break;
            case SOUSMARIN:
                n = 'S';
                break;
            case TORPILLEUR:
                n = 'T';
                break;
        }

        switch(aAdversaire[i]->etat){
            case OK:
                e = 'O';
                break;
            case TOUCHE:
                e = 'T';
                break;
            case COULE:
                e = 'C';
                break;
        }
        fprintf(f,"%c%c",n,e);

        for(int j=0;j<aAdversaire[i]->taille;j++){
            x=aAdversaire[i]->posX[j];
            y=aAdversaire[i]->posY[j];
            fprintf(f,"%d%d",x,y);
        }
        fprintf(f,"\n");
    }

    for(int i=0;i<mI->taille;i++){
        for(int j=0;j<mI->taille;j++){
            fprintf(f,"%c",(mI->value[i][j]));
        }
        fprintf(f,"\n");
    }

    for(int i=0;i<mA->taille;i++){
        for(int j=0;j<mA->taille;j++){
            fprintf(f,"%c",(mA->value[i][j]));
        }
        fprintf(f,"\n");
    }

    for(int i=0;i<mIA->taille;i++){
        for(int j=0;j<mIA->taille;j++){
            fprintf(f,"%c",(mIA->value[i][j]));
        }
        fprintf(f,"\n");
    }

    fclose(f);
}

int charger(int *tour, Matrice *m, Matrice *m2, Matrice *m3, Matrice *m4, Navire **aJ, Navire **aA){
    /*
        Permet de charger une partie sauvegarder.
        Param. :
            tour : nombre de tours, Type : pointeur d'entier
            m : Matrice du joueur, Type : pointeur de Matrice
            m2 : Matrice de l'adversaire, Type : pointeur de Matrice
            m3 : Matrice de l'adversaire que l'on affiche, Type : pointeur de Matrice
            m4 : matrice intermédiaire de utilisé par l'IA, Type : pointeur de Matrice
            aJ : armada du joueur, Type : pointeur de tableau de Navire
            aA : armada de l'adversaire, Type : pointeur de tableau de Navire
        Return :
            Entier déterminant si le chargement à réussit.
    */
    int t;
    char n, e, x, y, tmp;
    FILE *f = fopen(".save","r");
    // On récupére le tour
    //t = fgetc(f);
    fscanf(f,"%d",&t);
    // Avant de continuer, on vérifie bien que le fichier n'est pas vide
    if(t == -1){
        printf("\033[0;31mAucune sauvegarde trouvée.\033[0;m\n");
        return 2;
    }
    // On modifie le tour
    *tour=(t);
    // On récupére la taille des matrices puis on les recréer
    fscanf(f,"%d",&t);
    m->taille = t;
    m->titre = "Matrice du joueur";
    m2->taille = t;
    m2->titre = "Matrice de l'adversaire";
    m3->taille = t;
    m3->titre = "Matrice intermédiaire";

    // On reconstruit la flotte du joueur
    for(int i=0;i<TAILLE_FLOTTE;i++){
        aJ[i]->matrice = m;
        n = fgetc(f);
        while(n == '\n'){
            n = fgetc(f);
        }

        // TODO Ajouter l'armement.

        switch(n){
            case 'P':
                aJ[i]->nom = PORTEAVION;
                aJ[i]->taille = 5;
                break;
            case 'C':
                aJ[i]->nom = CROISER;
                aJ[i]->armementSecondaire = getTypeTirSpecial(aJ[i]->nom);
                aJ[i]->taille = 4;
                break;
            case 'D':
                aJ[i]->nom = DESTROYER;
                aJ[i]->taille = 3;
                break;
            case 'S':
                aJ[i]->nom = SOUSMARIN;
                aJ[i]->taille = 3;
                break;
            case 'T':
                aJ[i]->nom = TORPILLEUR;
                aJ[i]->taille = 2;
                break;
        }

        e = fgetc(f);
        switch(e){
            case 'O':
                aJ[i]->etat = OK;
                break;
            case 'T':
                aJ[i]->etat = TOUCHE;
                break;
            case 'C':
                aJ[i]->etat = COULE;
                break;
        }

        for(int j=0;j<aJ[i]->taille;j++){
            aJ[i]->posX[j] = fgetc(f)-48;
            aJ[i]->posY[j] = fgetc(f)-48;
        }
    }

    // On reconstruit la matrice du joueur
    for(int i=0;i<m->taille;i++){
        for(int j=0;j<m->taille;j++){
            tmp = fgetc(f);
            if(tmp == '\n') tmp = fgetc(f);
            m->value[i][j] = tmp;
        }
    }

    // On fait la même chose pour l'adversaire
    for(int i=0;i<TAILLE_FLOTTE;i++){
        aA[i]->matrice = m;
        n = fgetc(f);
        while(n == '\n'){
            n = fgetc(f);
        }

        // TODO Ajouter l'armement.

        switch(n){
            case 'P':
                aA[i]->nom = PORTEAVION;
                aA[i]->taille = 5;
                break;
            case 'C':
                aA[i]->nom = CROISER;
                aA[i]->armementSecondaire = getTypeTirSpecial(aJ[i]->nom);
                aA[i]->taille = 4;
                break;
            case 'D':
                aA[i]->nom = DESTROYER;
                aA[i]->taille = 3;
                break;
            case 'S':
                aA[i]->nom = SOUSMARIN;
                aA[i]->taille = 3;
                break;
            case 'T':
                aA[i]->nom = TORPILLEUR;
                aA[i]->taille = 2;
                break;
        }

        e = fgetc(f);
        switch(e){
            case 'O':
                aA[i]->etat = OK;
                break;
            case 'T':
                aA[i]->etat = TOUCHE;
                break;
            case 'C':
                aA[i]->etat = COULE;
                break;
        }

        for(int j=0;j<aA[i]->taille;j++){
            aA[i]->posX[j] = fgetc(f)-48;
            aA[i]->posY[j] = fgetc(f)-48;
        }
    }

    for(int i=0;i<m3->taille;i++){
        for(int j=0;j<m3->taille;j++){
            tmp = fgetc(f);
            if(tmp == '\n') tmp = fgetc(f);
            m3->value[i][j] = tmp;
        }
    }

    for(int i=0;i<m2->taille;i++){
        for(int j=0;j<m2->taille;j++){
            tmp = fgetc(f);
            if(tmp == '\n') tmp = fgetc(f);
            m2->value[i][j] = tmp;
        }
    }

    for(int i=0;i<m4->taille;i++){
        for(int j=0;j<m4->taille;j++){
            tmp = fgetc(f);
            if(tmp == '\n') tmp = fgetc(f);
            m4->value[i][j] = tmp;
        }
    }

    fclose(f);
    puts("\033[0;32mPartie chargée.\033[0;m");
    return 1;
}

void afficherPlateauDeJeu(Matrice *mat_1, Matrice *mat_2){
    /*
        Permet d'afficher dans la sortie standard les matrices passée en paramètre.
        Param. :
            mat_1 : pointeur de la 1er matrice que l'on veut afficher, type : pointeur de Matrice.
            mat_2 : pointeur de la 2eme matrice que l'on veut afficher, type : pointeur de Matrice.
    */
    printf("%s : ", (mat_1->titre));
    for(int i = 0; i < (mat_1->taille - 4); i++) printf("  ");
    printf("%s : \n", (mat_2->titre));

    printf("     ");
    for(int i = 0; i < mat_1->taille; i++) printf("%c ", 65+i);
    printf("[y] ");
    printf("      ");
    for(int i = 0; i < mat_2->taille; i++) printf("%c ", 65+i);
    printf("[y] \n");

    for(int i = 0; i < mat_1->taille; i++){
        if(i+1 >= 10) printf(" %d  ", i+1);
        else printf("  %d  ", i+1);

        for(int j = 0; j < mat_1->taille; j++){
            if(mat_1->value[i][j]=='O')printf("\033[0;32m%c \033[0m",mat_1->value[i][j]);
            else if(mat_1->value[i][j]=='.')printf("\033[0;34m%c \033[0m",mat_1->value[i][j]);
            else if(mat_1->value[i][j]=='#')printf("\033[0;31m%c \033[0m",mat_1->value[i][j]);
            else printf("%c ", mat_1->value[i][j]);
        }

        printf("     ");

        if(i+1 >= 10) printf(" %d  ", i+1);
        else printf("  %d  ", i+1);

        for(int j = 0; j < mat_2->taille; j++){
            if(mat_2->value[i][j]=='O')printf("\033[0;32m%c \033[0m",mat_2->value[i][j]);
            else if(mat_2->value[i][j]=='.')printf("\033[0;34m%c \033[0m",mat_2->value[i][j]);
            else if(mat_2->value[i][j]=='#')printf("\033[0;31m%c \033[0m",mat_2->value[i][j]);
            else printf("%c ", mat_2->value[i][j]);
        }
        printf("\n");
    }
    printf(" [x] ");
    printf("     ");
    for(int i = 0; i < mat_2->taille*2; i++) printf(" ");
    printf(" [x] \n\n");
}

void initialiserIA(Matrice *matOrigine, IA *ordinateur, int taille_matrice){
    /*
        Permet d'initialiser notre IA pour le jeu.
        Param. :
            matOrigine : c'est la matrice d'origine de l'adversaire, type : pointeur de matrice.
            ordinateur : c'est l'adresse de notre IA, type : adresse de l'IA.
            taille_matrice : taille de la grille, type : entier.
    */
    IA notre_IA;
    notre_IA.etat_IA = R;
    notre_IA.matrice = matOrigine;
    notre_IA.matScanner = genererMatriceVide("Scanner", taille_matrice);
    notre_IA.posXtouche = -1;
    notre_IA.posYtouche = -1;
    notre_IA.angle = 0;
    notre_IA.toucheNavire = 0;
    notre_IA.tirSpecialPossible = 0;

    *ordinateur = notre_IA;
}

void afficherInfoIA(IA *ordinateur){
    /*
        Permet d'afficher l'état de l'IA.
        Param. :
            ordinateur : c'est l'adresse de notre IA, type : adresse de l'IA.
    */
    printf("Etat de l'IA :  ");
    if(ordinateur->etat_IA == R) printf("Recherche de navire. \n");
    if(ordinateur->etat_IA == O) printf("Determine l'orientation. \n");
    if(ordinateur->etat_IA == D) printf("Cherche a détruire un navire. \n");
    // Si l'IA a touché un navire alors on peut le dire.
    if(ordinateur->posXtouche != -1 && ordinateur->posYtouche != -1){
        printf("Dernier position touché : %d%c. Angle : %d. \n", 1+ordinateur->posXtouche, 65+ordinateur->posYtouche, ordinateur->angle);
    }
    printf("Matce d'origine : \n");
    afficherMatrice(ordinateur->matrice);
    printf("Matrice scanner de la zone ennemie : \n");
    afficherMatrice(ordinateur->matScanner);
    printf("A touche un navire ennemie : %d. \n", ordinateur->toucheNavire);
    printf("Peut utiliser un tir spécial : %d. \n", ordinateur->tirSpecialPossible);
}

void tourDeNotreIA(IA *ordinateur, Matrice *matriceJoueur, Navire **armadaJoueur, Navire **armadaIA){
    /*
        Permet à notre IA d'eefctuer une tir.
        Param. :
            ordinateur : c'est l'adresse de notre IA, type : adresse de l'IA.
            matriceJoueur : matrice du joueur avec ces navires, type : pointeur de Matrice.
            armadaJoueur : la flotte entière du joueur, type : tableau de pointeurs de Navire.
            armadaIA : la flotte entière de l'IA, type : tableau de pointeurs de Navire.
    */
    int aleaX, aleaY;
    int maxi = matriceJoueur->taille-1, mini = 0;
    int init = 0;

    if(ordinateur->etat_IA == R){
        int posOK = 0;
        int touche = 0;
        // Tir une case sur deux en aléatoire là où on a pas déjà tiré bien sûr ..
        while(posOK == 0){
            aleaX = generationIntAleatoire(maxi, mini);
            aleaY = generationIntAleatoire(maxi, mini);

            int uneCaseSurDeux = 0; // Permet (lors de la recherche uniquement) de tiré une case sur deux pour détecter un navire !
            if(aleaX % 2 == 0 && aleaY % 2 == 1){
                uneCaseSurDeux = 1;
            }

            if(aleaX % 2 == 1 && aleaY % 2 == 0){
                uneCaseSurDeux = 1;
            }

            // Si sur la matrice d'observation de l'IA, on a un '.' alors on place le tir.
            if(uneCaseSurDeux == 1 && ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                // Si sur la matrice du joueur, il n'y avait rien, on place un 'X' sur les deux matrices.
                if(matriceJoueur->value[aleaX][aleaY] == '.'){
                    matriceJoueur->value[aleaX][aleaY] = 'X';
                    ordinateur->matScanner->value[aleaX][aleaY] = 'X';
                    ordinateur->toucheNavire = 0;
                    printf("Tir en %d%c dans l'eau. \n", aleaX+1, aleaY+65);
                }
                // Par contre, s'il a un navire alors on place un '#' sur la matrice d'observation et celle du joueur.
                if(matriceJoueur->value[aleaX][aleaY] == 'O'){
                    matriceJoueur->value[aleaX][aleaY] = '#';
                    ordinateur->matScanner->value[aleaX][aleaY] = '#';
                    ordinateur->toucheNavire = 1;
                    touche = 1;
                    printf("Tir en %d%c à touché. \n", aleaX+1, aleaY+65);
                }
                posOK = 1;
            }
        }

        // Si on touche un navire (on enregistre le x et y), on passe à l'état 'O'.
        if(posOK == 1 && touche == 1){
            ordinateur->posXtouche = aleaX;
            ordinateur->posYtouche = aleaY;
            ordinateur->etat_IA = O;
            init = 1;
        }
    }

    if(init == 0 && ordinateur->etat_IA == O){
        aleaX = ordinateur->posXtouche;
        aleaY = ordinateur->posYtouche;
        // Comme pour la fonction de placement (même systeme 1, 2, 3 ou 4 pour l'angle), on détermine l'angle (<=> l'orientation) du navire ennemie.
        int angle = 0;
        int angleOK = 0;
        int trouve = 0;
        // Tant que l'angle n'est pas bon (Autrement dit, on regarde si on peut tirer en fonction de l'angle).
        while(angleOK == 0){
            angle = generationIntAleatoire(4, 1);

            if(angle == 1 && aleaY-1 >= mini && ordinateur->matScanner->value[aleaX][aleaY-1] == '.'){
                // On fait le tir et on regarde si on a touché.
                // Si sur la matrice du joueur, il n'y avait rien, on place un 'X' sur les deux matrices. On n'a rien trouvé ..
                if(matriceJoueur->value[aleaX][aleaY-1] == '.'){
                    matriceJoueur->value[aleaX][aleaY-1] = 'X';
                    ordinateur->matScanner->value[aleaX][aleaY-1] = 'X';
                    ordinateur->toucheNavire = 0;
                    printf("Tir en %d%c dans l'eau. \n", aleaX+1, aleaY+65-1);
                }
                // Par contre, s'il a un navire alors on place un '#' sur la matrice d'observation et celle du joueur. On a trouvé l'orientation !
                if(matriceJoueur->value[aleaX][aleaY-1] == 'O'){
                    matriceJoueur->value[aleaX][aleaY-1] = '#';
                    ordinateur->matScanner->value[aleaX][aleaY-1] = '#';
                    ordinateur->toucheNavire = 1;
                    trouve = 1;
                    printf("Tir en %d%c à touché. \n", aleaX+1, aleaY+65-1);
                }
                // Le tir a été fait, l'angle peut être trouvé ou non, dans tout les cas on a fait un tir.
                angleOK = 1;
            }

            if(angle == 2 && aleaX-1 >= mini && ordinateur->matScanner->value[aleaX-1][aleaY] == '.'){
                // On fait pareil .. le tir et on regarde si on a touché ou pas.
                if(matriceJoueur->value[aleaX-1][aleaY] == '.'){
                    matriceJoueur->value[aleaX-1][aleaY] = 'X';
                    ordinateur->matScanner->value[aleaX-1][aleaY] = 'X';
                    ordinateur->toucheNavire = 0;
                    printf("Tir en %d%c dans l'eau. \n", aleaX, aleaY+65);
                }

                if(matriceJoueur->value[aleaX-1][aleaY] == 'O'){
                    matriceJoueur->value[aleaX-1][aleaY] = '#';
                    ordinateur->matScanner->value[aleaX-1][aleaY] = '#';
                    ordinateur->toucheNavire = 1;
                    trouve = 1;
                    printf("Tir en %d%c à touché. \n", aleaX, aleaY+65);
                }

                angleOK = 1;
            }

            if(angle == 3 && aleaY+1 <= maxi && ordinateur->matScanner->value[aleaX][aleaY+1] == '.'){
                // On fait pareil .. le tir et on regarde si on a touché ou pas.
                if(matriceJoueur->value[aleaX][aleaY+1] == '.'){
                    matriceJoueur->value[aleaX][aleaY+1] = 'X';
                    ordinateur->matScanner->value[aleaX][aleaY+1] = 'X';
                    ordinateur->toucheNavire = 0;
                    printf("Tir en %d%c dans l'eau. \n", aleaX+1, aleaY+65+1);
                }

                if(matriceJoueur->value[aleaX][aleaY+1] == 'O'){
                    matriceJoueur->value[aleaX][aleaY+1] = '#';
                    ordinateur->matScanner->value[aleaX][aleaY+1] = '#';
                    ordinateur->toucheNavire = 1;
                    trouve = 1;
                    printf("Tir en %d%c à touché. \n", aleaX+1, aleaY+65+1);
                }

                angleOK = 1;
            }

            if(angle == 4 && aleaX+1 <= maxi && ordinateur->matScanner->value[aleaX+1][aleaY] == '.'){
                // On fait pareil .. le tir et on regarde si on a touché ou pas.
                if(matriceJoueur->value[aleaX+1][aleaY] == '.'){
                    matriceJoueur->value[aleaX+1][aleaY] = 'X';
                    ordinateur->matScanner->value[aleaX+1][aleaY] = 'X';
                    ordinateur->toucheNavire = 0;
                    printf("Tir en %d%c dans l'eau. \n", aleaX+2, aleaY+65);
                }

                if(matriceJoueur->value[aleaX+1][aleaY] == 'O'){
                    matriceJoueur->value[aleaX+1][aleaY] = '#';
                    ordinateur->matScanner->value[aleaX+1][aleaY] = '#';
                    ordinateur->toucheNavire = 1;
                    trouve = 1;
                    printf("Tir en %d%c à touché. \n", aleaX+2, aleaY+65);
                }

                angleOK = 1;
            }
        }

        // Si on le trouve (on enregistre l'angle), on passe à l'état 'D'.
        if(trouve == 1){
            ordinateur->angle = angle;
            ordinateur->etat_IA = D;
            init = 2;
        }
    }

    if(init == 0 && ordinateur->etat_IA == D){
        aleaX = ordinateur->posXtouche;
        aleaY = ordinateur->posYtouche;
        int angle = ordinateur->angle;

        // Gestion des tirs spéciaux :
        int tableau_de_tir[TYPE_TIR];
        int choixTirIA = 0;
        for(int i = 0; i < TYPE_TIR; i++) tableau_de_tir[i] = 0;
        if(ordinateur->toucheNavire == 1 && ordinateur->tirSpecialPossible == 0){
            // On vérifie les tirs possibles.
            //printf("t: %d et speP : %d \n", ordinateur->toucheNavire, ordinateur->tirSpecialPossible);
            tableau_de_tir[0] = 1;
            for(int i = 1; i < TYPE_TIR; i++){
                if(tableau_de_tir[1] == 0 && armadaIA[i]->armementPrincipale == 1){
                    tableau_de_tir[1] = 1;
                }

                if(tableau_de_tir[2] == 0 && armadaIA[i]->armementPrincipale == 2){
                    tableau_de_tir[2] = 1;
                }

                if(tableau_de_tir[3] == 0 && armadaIA[i]->nom == CROISER && armadaIA[i]->armementSecondaire == 2){
                    tableau_de_tir[3] = 1;
                }

                if(tableau_de_tir[4] == 0 && armadaIA[i]->armementPrincipale == 3){
                    tableau_de_tir[4] = 1;
                }
            }
            // Parmis ces tirs, on choisit en random.
            choixTirIA = generationIntAleatoire(TYPE_TIR-1, 0);
            while(choixTirIA < 0 || choixTirIA > 4 || tableau_de_tir[choixTirIA] != 1){
                choixTirIA = generationIntAleatoire(TYPE_TIR-1, 0);
            }
            //printf("Tir utilise : %d. \n", choixTirIA);
            // On appel la fonction de tir plus bas, et prépare des variables pour effectuer le tir dans le 'while' juste après le 'if'.
            // En fonction du tir, on modifie tout de suite la valeur de tirSpecialPossible et on consomme tout de suite le tir.
            if(choixTirIA == 0){
                ordinateur->tirSpecialPossible = 0;
            } else {
                for(int i = 1; i < TYPE_TIR; i++){
                    if(armadaIA[i]->armementPrincipale == 1 && choixTirIA == 1){
                        armadaIA[i]->armementPrincipale = 0;
                        ordinateur->tirSpecialPossible = 1;
                        break;
                    }

                    if(armadaIA[i]->armementPrincipale == 2 && choixTirIA == 2){
                        armadaIA[i]->armementPrincipale = 0;
                        ordinateur->tirSpecialPossible = 1;
                        break;
                    }

                    if(armadaIA[i]->nom == CROISER && armadaIA[i]->armementSecondaire == 2 && choixTirIA == 3){
                        armadaIA[i]->armementSecondaire = 0;
                        ordinateur->tirSpecialPossible = 1;
                        break;
                    }

                    if(armadaIA[i]->armementPrincipale == 3 && choixTirIA == 4){
                        armadaIA[i]->armementPrincipale = 0;
                        ordinateur->tirSpecialPossible = 1;
                        break;
                    }
                }
            }
        }

        // On tir dans la bonne direction tant qu'on ne touche pas l'eau.
        int sens = 0;
        while(sens == 0){
            if(angle == 1){
                // Si on a déjà touché à cette endroit alors on décale.
                if(ordinateur->matScanner->value[aleaX][aleaY] == '#'){
                    aleaY--;
                    if(aleaY < mini){
                        sens = 2; // On est au bout ..
                        break;
                    }
                }

                // Si on a pas tiré à cette endroit alors on tir et on met à jour les matrices.
                if(ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                    // ######## Tir ########
                    //printf("On tir avec un %d !! \n", choixTirIA);
                    int **tab = fonctionTir(aleaX, aleaY, choixTirIA, 1, matriceJoueur); // On utilise notre fonction qui retourne un pointeur de tableau.
                    int tmp_taille = 0;
                    if(choixTirIA == 0){
                        tmp_taille = 1;
                    } else if(choixTirIA == 1){
                        tmp_taille = matriceJoueur->taille;
                    } else if(choixTirIA == 4) {
                        tmp_taille = 9;
                    } else {
                        tmp_taille = 5;
                    }

                    // On part du principe que l'IA n'a pas touché, comme pour le tir du joueur ..
                    ordinateur->toucheNavire = 0;
                    // On parcours notre tableau retourné par la fonction de tir.
                    for(int i = 0; i < tmp_taille; i++){
                        // On vérifi que l'on est pas en dehors de la grille puis on met à jour les matrices.
                        if(tab[i][0] >= 0 && tab[i][0] <= matriceJoueur->taille-1 && tab[i][1] >= 0 && tab[i][1] <= matriceJoueur->taille-1){
                            if(matriceJoueur->value[tab[i][0]][tab[i][1]] == '.'){
                                matriceJoueur->value[tab[i][0]][tab[i][1]] = 'X';
                                ordinateur->matScanner->value[tab[i][0]][tab[i][1]] = 'X';
                                printf("Tir en %d%c dans l'eau. \n", tab[i][0]+1, tab[i][1]+65);
                            }

                            if(matriceJoueur->value[tab[i][0]][tab[i][1]] == 'O'){
                                matriceJoueur->value[tab[i][0]][tab[i][1]] = '#';
                                ordinateur->matScanner->value[tab[i][0]][tab[i][1]] = '#';
                                ordinateur->toucheNavire = 1;
                                printf("Tir en %d%c à touché. \n", tab[i][0]+1, tab[i][1]+65);
                            }

                            //printf("%d%c \n", tab[i][0]+1, tab[i][1]+65);
                        }
                    }

                    sens = 1;
                    //printf("Sens : %d \n", sens);
                    /*
                    if(matriceJoueur->value[aleaX][aleaY] == '.'){
                        matriceJoueur->value[aleaX][aleaY] = 'X';
                        ordinateur->matScanner->value[aleaX][aleaY] = 'X';
                        ordinateur->toucheNavire = 0;
                        sens = 2; // On arrive au bout d'un côté !
                    }

                    if(matriceJoueur->value[aleaX][aleaY] == 'O'){
                        matriceJoueur->value[aleaX][aleaY] = '#';
                        ordinateur->matScanner->value[aleaX][aleaY] = '#';
                        ordinateur->toucheNavire = 1;
                        sens = 1; // Il reste peut être un morceau de navire.
                    }
                    */
                }

                // Si on a déjà tiré à cette endroit sans touché .. On est arrivé au bout.
                if(ordinateur->matScanner->value[aleaX][aleaY] == 'X'){
                    sens = 2; // On arrive au bout d'un côté !
                }
            }

            if(angle == 2){
                if(ordinateur->matScanner->value[aleaX][aleaY] == '#'){
                    aleaX--;
                    if(aleaX < mini){
                        sens = 2; // On est au bout ..
                        break;
                    }
                }

                if(ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                    // ######## Tir ########
                    //printf("On tir avec un %d !! \n", choixTirIA);
                    int **tab = fonctionTir(aleaX, aleaY, choixTirIA, 0, matriceJoueur); // On utilise notre fonction qui retourne un pointeur de tableau.
                    int tmp_taille = 0;
                    if(choixTirIA == 0){
                        tmp_taille = 1;
                    } else if(choixTirIA == 1){
                        tmp_taille = matriceJoueur->taille;
                    } else if(choixTirIA == 4) {
                        tmp_taille = 9;
                    } else {
                        tmp_taille = 5;
                    }

                    // On part du principe que l'IA n'a pas touché, comme pour le tir du joueur ..
                    ordinateur->toucheNavire = 0;
                    // On parcours notre tableau retourné par la fonction de tir.
                    for(int i = 0; i < tmp_taille; i++){
                        // On vérifi que l'on est pas en dehors de la grille puis on met à jour les matrices.
                        if(tab[i][0] >= 0 && tab[i][0] <= matriceJoueur->taille-1 && tab[i][1] >= 0 && tab[i][1] <= matriceJoueur->taille-1){
                            if(matriceJoueur->value[tab[i][0]][tab[i][1]] == '.'){
                                matriceJoueur->value[tab[i][0]][tab[i][1]] = 'X';
                                ordinateur->matScanner->value[tab[i][0]][tab[i][1]] = 'X';
                                printf("Tir en %d%c dans l'eau. \n", tab[i][0]+1, tab[i][1]+65);
                            }

                            if(matriceJoueur->value[tab[i][0]][tab[i][1]] == 'O'){
                                matriceJoueur->value[tab[i][0]][tab[i][1]] = '#';
                                ordinateur->matScanner->value[tab[i][0]][tab[i][1]] = '#';
                                ordinateur->toucheNavire = 1;
                                printf("Tir en %d%c à touché. \n", tab[i][0]+1, tab[i][1]+65);
                            }

                            //printf("%d%c \n", tab[i][0]+1, tab[i][1]+65);
                        }
                    }

                    sens = 1;
                    //printf("Sens : %d \n", sens);
                    /*
                    if(matriceJoueur->value[aleaX][aleaY] == '.'){
                        matriceJoueur->value[aleaX][aleaY] = 'X';
                        ordinateur->matScanner->value[aleaX][aleaY] = 'X';
                        ordinateur->toucheNavire = 0;
                        sens = 2; // On arrive au bout d'un côté !
                    }

                    if(matriceJoueur->value[aleaX][aleaY] == 'O'){
                        matriceJoueur->value[aleaX][aleaY] = '#';
                        ordinateur->matScanner->value[aleaX][aleaY] = '#';
                        ordinateur->toucheNavire = 1;
                        sens = 1; // Il reste peut être un morceau de navire.
                    }
                    */
                }

                if(ordinateur->matScanner->value[aleaX][aleaY] == 'X'){
                    sens = 2; // On arrive au bout d'un côté !
                }
            }

            if(angle == 3){
                if(ordinateur->matScanner->value[aleaX][aleaY] == '#'){
                    aleaY++;
                    if(aleaY > maxi){
                        sens = 2; // On est au bout ..
                        break;
                    }
                }

                if(ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                    // ######## Tir ########
                    //printf("On tir avec un %d !! \n", choixTirIA);
                    int **tab = fonctionTir(aleaX, aleaY, choixTirIA, 1, matriceJoueur); // On utilise notre fonction qui retourne un pointeur de tableau.
                    int tmp_taille = 0;
                    if(choixTirIA == 0){
                        tmp_taille = 1;
                    } else if(choixTirIA == 1){
                        tmp_taille = matriceJoueur->taille;
                    } else if(choixTirIA == 4) {
                        tmp_taille = 9;
                    } else {
                        tmp_taille = 5;
                    }

                    // On part du principe que l'IA n'a pas touché, comme pour le tir du joueur ..
                    ordinateur->toucheNavire = 0;
                    // On parcours notre tableau retourné par la fonction de tir.
                    for(int i = 0; i < tmp_taille; i++){
                        // On vérifi que l'on est pas en dehors de la grille puis on met à jour les matrices.
                        if(tab[i][0] >= 0 && tab[i][0] <= matriceJoueur->taille-1 && tab[i][1] >= 0 && tab[i][1] <= matriceJoueur->taille-1){
                            if(matriceJoueur->value[tab[i][0]][tab[i][1]] == '.'){
                                matriceJoueur->value[tab[i][0]][tab[i][1]] = 'X';
                                ordinateur->matScanner->value[tab[i][0]][tab[i][1]] = 'X';
                                printf("Tir en %d%c dans l'eau. \n", tab[i][0]+1, tab[i][1]+65);
                            }

                            if(matriceJoueur->value[tab[i][0]][tab[i][1]] == 'O'){
                                matriceJoueur->value[tab[i][0]][tab[i][1]] = '#';
                                ordinateur->matScanner->value[tab[i][0]][tab[i][1]] = '#';
                                ordinateur->toucheNavire = 1;
                                printf("Tir en %d%c à touché. \n", tab[i][0]+1, tab[i][1]+65);
                            }

                            //printf("%d%c \n", tab[i][0]+1, tab[i][1]+65);
                        }
                    }

                    sens = 1;
                    //printf("Sens : %d \n", sens);
                    /*
                    if(matriceJoueur->value[aleaX][aleaY] == '.'){
                        matriceJoueur->value[aleaX][aleaY] = 'X';
                        ordinateur->matScanner->value[aleaX][aleaY] = 'X';
                        ordinateur->toucheNavire = 0;
                        sens = 2; // On arrive au bout d'un côté !
                    }

                    if(matriceJoueur->value[aleaX][aleaY] == 'O'){
                        matriceJoueur->value[aleaX][aleaY] = '#';
                        ordinateur->matScanner->value[aleaX][aleaY] = '#';
                        ordinateur->toucheNavire = 1;
                        sens = 1; // Il reste peut être un morceau de navire.
                    }
                    */
                }

                if(ordinateur->matScanner->value[aleaX][aleaY] == 'X'){
                    sens = 2; // On arrive au bout d'un côté !
                }
            }

            if(angle == 4){
                if(ordinateur->matScanner->value[aleaX][aleaY] == '#'){
                    aleaX++;
                    if(aleaX > maxi){
                        sens = 2; // On est au bout ..
                        break;
                    }
                }

                if(ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                    // ######## Tir ########
                    //printf("On tir avec un %d !! \n", choixTirIA);
                    int **tab = fonctionTir(aleaX, aleaY, choixTirIA, 0, matriceJoueur); // On utilise notre fonction qui retourne un pointeur de tableau.
                    int tmp_taille = 0;
                    if(choixTirIA == 0){
                        tmp_taille = 1;
                    } else if(choixTirIA == 1){
                        tmp_taille = matriceJoueur->taille;
                    } else if(choixTirIA == 4) {
                        tmp_taille = 9;
                    } else {
                        tmp_taille = 5;
                    }

                    // On part du principe que l'IA n'a pas touché, comme pour le tir du joueur ..
                    ordinateur->toucheNavire = 0;
                    // On parcours notre tableau retourné par la fonction de tir.
                    for(int i = 0; i < tmp_taille; i++){
                        // On vérifi que l'on est pas en dehors de la grille puis on met à jour les matrices.
                        if(tab[i][0] >= 0 && tab[i][0] <= matriceJoueur->taille-1 && tab[i][1] >= 0 && tab[i][1] <= matriceJoueur->taille-1){
                            if(matriceJoueur->value[tab[i][0]][tab[i][1]] == '.'){
                                matriceJoueur->value[tab[i][0]][tab[i][1]] = 'X';
                                ordinateur->matScanner->value[tab[i][0]][tab[i][1]] = 'X';
                                printf("Tir en %d%c dans l'eau. \n", tab[i][0]+1, tab[i][1]+65);
                            }

                            if(matriceJoueur->value[tab[i][0]][tab[i][1]] == 'O'){
                                matriceJoueur->value[tab[i][0]][tab[i][1]] = '#';
                                ordinateur->matScanner->value[tab[i][0]][tab[i][1]] = '#';
                                ordinateur->toucheNavire = 1;
                                printf("Tir en %d%c à touché. \n", tab[i][0]+1, tab[i][1]+65);
                            }

                            //printf("%d%c \n", tab[i][0]+1, tab[i][1]+65);
                        }
                    }

                    sens = 1;
                    //printf("Sens : %d \n", sens);
                    /*
                    if(matriceJoueur->value[aleaX][aleaY] == '.'){
                        matriceJoueur->value[aleaX][aleaY] = 'X';
                        ordinateur->matScanner->value[aleaX][aleaY] = 'X';
                        ordinateur->toucheNavire = 0;
                        sens = 2; // On arrive au bout d'un côté !
                    }

                    if(matriceJoueur->value[aleaX][aleaY] == 'O'){
                        matriceJoueur->value[aleaX][aleaY] = '#';
                        ordinateur->matScanner->value[aleaX][aleaY] = '#';
                        ordinateur->toucheNavire = 1;
                        sens = 1; // Il reste peut être un morceau de navire.
                    }
                    */
                }

                if(ordinateur->matScanner->value[aleaX][aleaY] == 'X'){
                    sens = 2; // On arrive au bout d'un côté !
                }
            }
        }

        // Si on touche l'eau (sens => 2), on regarde dans l'autre sens parce que le navire n'est peut être pas coulé entièrement.
        // Pour cela, on va modifier l'angle pour que l'IA qui regardera dans ce sens si elle n'a pas touché l'eau de l'autre côté.
        // (aucun tir dans cette condition)
        if(sens == 2){
            if(angle == 1) ordinateur->angle = 3;
            if(angle == 2) ordinateur->angle = 4;
            if(angle == 3) ordinateur->angle = 1;
            if(angle == 4) ordinateur->angle = 2;

            // On dit que le navire est mort si en parcourant dans les deux sens on a un 'X' après les '#'.
            int verification = 0;
            // Pour aller plus vite on reprend les coordonées où on découvert le navire.
            aleaX = ordinateur->posXtouche;
            aleaY = ordinateur->posYtouche;
            angle = ordinateur->angle;
            // On va donc vérifier si on a un 'X' après un '#' dans le nouveau sens (si c'est le cas on repassera en R sinon on reste en D mais avec un nouveau angle).
            while(verification == 0){
                if(angle == 1){
                    // Si on a déjà touché à cette endroit alors on décale.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == '#'){
                        aleaY--;
                        if(aleaY < mini){
                            verification = 2; // On est au bout ..
                            break;
                        }
                    }

                    // Si on a pas tiré à cette endroit alors il reste peut être un morceau au navire.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                        verification = 1;
                    }

                    // Si on a tiré mais qu'il n'y a rien non plus au bout.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == 'X'){
                        verification = 2;
                    }
                }

                if(angle == 2){
                    if(ordinateur->matScanner->value[aleaX][aleaY] == '#'){
                        aleaX--;
                        if(aleaX < mini){
                            verification = 2; // On est au bout ..
                            break;
                        }
                    }

                    // Si on a pas tiré à cette endroit alors il reste peut être un morceau au navire.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                        verification = 1;
                    }

                    // Si on a tiré mais qu'il n'y a rien non plus au bout.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == 'X'){
                        verification = 2;
                    }
                }

                if(angle == 3){
                    if(ordinateur->matScanner->value[aleaX][aleaY] == '#'){
                        aleaY++;
                        if(aleaY > maxi){
                            verification = 2; // On est au bout ..
                            break;
                        }
                    }

                    // Si on a pas tiré à cette endroit alors il reste peut être un morceau au navire.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                        verification = 1;
                    }

                    // Si on a tiré mais qu'il n'y a rien non plus au bout.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == 'X'){
                        verification = 2;
                    }
                }

                if(angle == 4){
                    if(ordinateur->matScanner->value[aleaX][aleaY] == '#'){
                        aleaX++;
                        if(aleaX > maxi){
                            verification = 2; // On est au bout ..
                            break;
                        }
                    }

                    // Si on a pas tiré à cette endroit alors il reste peut être un morceau au navire.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == '.'){
                        verification = 1;
                    }

                    // Si on a tiré mais qu'il n'y a rien non plus au bout.
                    if(ordinateur->matScanner->value[aleaX][aleaY] == 'X'){
                        verification = 2;
                    }
                }
            }

            // On repasse à l'état 'R' pour rechercher une autre navire si on a tiré mais qu'il n'y a rien non plus au bout.
            if(verification == 2){
                ordinateur->posXtouche = -1;
                ordinateur->posYtouche = -1;
                ordinateur->angle = 0;
                ordinateur->etat_IA = R;

                // Faire un tir en aléa pour ne pas perdre un tour ..
            }
        }
    }

    verifierFlotteEntiere(matriceJoueur, armadaJoueur);
}

// Fin.
