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
    puts("Votre armada : ");
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
            if(st2 == "OK")printf("#%d %s\tEtat : \033[0;32m%s\033[0m\n", i, st, st2);
            else if(st2 == "TOUCHÉ")printf("#%d %s\tEtat : \033[0;33m%s\033[0m\n", i, st, st2);
            else if(st2 == "COULÉ")printf("#%d %s\tEtat : \033[0;31m%s\033[0m\n", i, st, st2);
            else printf("#%d %s\tEtat : %s\n", i, st, st2);
        }
        afficherNavireArmement(armada[i]);
        afficherNavirePos(armada[i]);
        printf("\n\n");
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
    printf("Placement aleatoire .. \n");

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
                    } else {
                        poser = 0;
                        break;
                    }
                }

                if(angle == 2){
                    if(aleaX-i >= mini && tableau2D[aleaX-i][aleaY] == 0){
                    } else {
                        poser = 0;
                        break;
                    }
                }

                if(angle == 3){
                    if(aleaY+i <= maxi && tableau2D[aleaX][aleaY+i] == 0){
                    } else {
                        poser = 0;
                        break;
                    }
                }

                if(angle == 4){
                    if(aleaX+i <= maxi && tableau2D[aleaX+i][aleaY] == 0){
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
    printf("Creation d'une flotte standard .. \n");

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

void effectuerTir(Matrice *m, Matrice *m2, Navire **armadaJoueur, Navire **armadaAdversaire, int *toucheNavire, int *actionSpeciale, int tour){
    /*
        Effectue un tir sur la matrice vidé.
        Param. :
            m : pointeur de la matrice que le joueur attaque, type : pointeur de Matrice.
            m2 : pointeur de la matrice que le joueur attaque et que l'on affiche, type : pointeur de Matrice.
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
    printf("Actions : \n");
    // Si le joueur a touché au dernier tour jouer et qu'il n'a pas utilisé de tir spéciale alors il le peut maintenant :
    if(*toucheNavire == 1 && *actionSpeciale == 0){
        for(int i = 1; i < TYPE_TIR; i++){
            if(armadaJoueur[i]->armementPrincipale == 1){
                printf("Tir sur toute une ligne ou colonne [1], ");
                tableau_de_tir[1] = 1;
            }

            if(armadaJoueur[i]->armementPrincipale == 2){
                printf("Tir en 'x' [2], ");
                tableau_de_tir[2] = 1;
            }

            if(armadaJoueur[i]->nom == CROISER && armadaJoueur[i]->armementSecondaire == 2){
                printf("Tir en '+' [3], ");
                tableau_de_tir[3] = 1;
            }

            if(armadaJoueur[i]->armementPrincipale == 3){
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
        sauvegarde(armadaJoueur,armadaAdversaire,tour);
        puts("\033[0;32mSauvegarde terminée.\033[0;m");
    }
    printf("\n");
    while(choixTir < 0 || choixTir > 5 || tableau_de_tir[choixTir] != 1){
        printf("Choisissez un tir : ");
        scanf("%d", &tmpChoix);
        choixTir = tmpChoix;
        printf("\n");
    }

    // Si c'est un tir normale alors actionSpeciale est à 0.
    if(choixTir == 0){
        *actionSpeciale = 0;
    }
    // On consomme le tir spéciale (on le remplace par un tir normal) et on modifie la variable des tirs spéciaux :
    for(int i = 1; i < TYPE_TIR; i++){
        if(armadaJoueur[i]->armementPrincipale == 1 && choixTir == 1){
            armadaJoueur[i]->armementPrincipale = 0;
            *actionSpeciale = 1;
            break;
        }

        if(armadaJoueur[i]->armementPrincipale == 2 && choixTir == 2){
            armadaJoueur[i]->armementPrincipale = 0;
            *actionSpeciale = 1;
            break;
        }

        if(armadaJoueur[i]->nom == CROISER && armadaJoueur[i]->armementSecondaire == 2 && choixTir == 3){
            armadaJoueur[i]->armementSecondaire = 0;
            *actionSpeciale = 1;
            break;
        }

        if(armadaJoueur[i]->armementPrincipale == 3 && choixTir == 4){
            armadaJoueur[i]->armementPrincipale = 0;
            *actionSpeciale = 1;
            break;
        }
    }

    // On choisit la position :
    int posX = -1, posY = -1;
    printf("Choisir les coordonnées : \n");
    printf("x = ");
    scanf("%d", &posX);
    while(posX < 0 || posX > m->taille){
        printf("Choisir un 'x' correct : \n");
        printf("x = ");
        scanf("%d", &posX);
    }
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
    printf("ChoixTir : %d \n", choixTir);
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
        if(tab[i][0] >= 0 && tab[i][0] <= m->taille && tab[i][1] >= 0 && tab[i][1] <= m->taille){
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
        printf("Navire touche en %d%c ! \n", positionX+1, positionY+65);
    }
}

void verifierFlotteEntiere(Matrice *m, Navire **armada){
    /*
        Permet de vérifier l'état de la flotte tout entier (vérifie s'il y a un ou plusieurs navires coulé ou non).
        Param. :
            m : pointeur de matrice se situant la flotte, type : pointeur de Matrice.
            armada : la flotte que l'on veut vérifier, type : tableau de pointeur de Navire.
    */

    for(int i = 0; i < TAILLE_FLOTTE; i++){
        verifierNavire(m, armada[i]);
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
            printf("Le navire a coule .. \n");
        }
    } else {
        if(n->etat == COULE){
            printf("Navire est deja coulé .. \n");
        }

        if(n->etat == OK){
            printf("Navire sans probleme. \n");
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

void sauvegarde(Navire **aJoueur, Navire **aAdversaire, int tour){
    /*
        Permet de sauvegarder une partie
        Param. :
            aJoueur : armada du joueur, type : tableau de pointeurs de Navire;
            aAdversaire : aramda de l'IA, type : tableau de pointeurs de Navire
            tour : tour auquel nous avons fait la sauvegarde, type : int
    */
    char n, e, o;
    int x, y;
    FILE* f;
    f = fopen(".save","w");
    fprintf(f,"%d\n",tour);
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
        x=aJoueur[i]->posX[0];
        y=aJoueur[i]->posY[0];
        if(aJoueur[i]->posX[1] != x){
            o = 'V';
        }else{
            o = 'H';
        }
        fprintf(f,"%c %c %d %d %c\n",n,e,x,y,o);
    }
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
        x=aAdversaire[i]->posX[0];
        y=aAdversaire[i]->posY[0];
        if(aAdversaire[i]->posX[1] != x){
            o = 'V';
        }else{
            o = 'H';
        }
        fprintf(f,"%c %c %d %d %c\n",n,e,x,y,o);
    }
    fclose(f);
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
    printf("     ");
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