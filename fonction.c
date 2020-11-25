#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction.h"

int getTailleNavire(NavireType nt){
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

    return n;
}

void placementNavire(Matrice *m, NavireType nt, int x, int y, Orientation o){
    /*
    Permet de placer un navire selon des coordonées et une orientation sur la matrice voulu.
    Param. :
        m : matrice que l'on veut modifier, type : pointeur de Matrice.
        nt : type de navire a placer, type : NavireType.
        x : coordonee de l'axe des abcisses, type : int.
        y : coordonne de l'axe des ordonnees, type : int.
        o : orientation voulu du navire, type : Orientation.
    */
    Navire *notre_navire = genererNavire(nt, m);
    int taille = getTailleNavire(nt);
    int posX[taille], posY[taille];
    if(o == H){
        for(int i = 0; i < taille; i++){
            posX[i] = x+i;
            posY[i] = y;
        }
    }else if(o == V){
        for(int i = 0; i < taille; i++){
            posX[i] = x;
            posY[i] = y+i;
        }
    }

    for(int i = 0; i < notre_navire->taille; i++){
        notre_navire->posX[i] = posX[i];
        notre_navire->posY[i] = posY[i];
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
        m : pointeur de la matrice aue l'on veut afficher, type : pointeur de Matrice.
    */
    printf("%s : \n", m->titre);
    printf("     ");
    for(int i = 0; i < m->taille; i++) printf("%c ", 65+i);
    printf("\n");
    for(int i = 0; i < m->taille; i++){
        if(i+1 >= 10) printf(" %d  ", i+1);
        else printf("  %d  ", i+1);

        for(int j = 0; j < m->taille; j++){
            printf("%c ", m->value[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void choisirTaille(int *ptr){
    /*
    Permet de deternimer la taille d'une matrice.
    Param. :
        ptr : pointeur de la taille de matrice que l'on veut modifier, type: pointeur d'int.
    */
    int taille_matrice;
    printf("Choisissez la taille de la grille de jeu (26 max) : ");
    scanf("%d", &taille_matrice);
    printf("\n");
    while(taille_matrice > 26 || taille_matrice < 0){
        printf("Choisissez une taille conforme de grille (26 max) : ");
        scanf("%d", &taille_matrice);
        printf("\n");
    }

    *ptr = taille_matrice;
}

void afficherArmada(Navire **armada){
    puts("Votre armada :\n");
    char* st;
    char* st2;
    for(int i = 0; i < 5; i++){
        NavireType nt=armada[i]->nom;
        switch(nt){
            case PORTEAVION:
                st="Porte-avion";
                break;
            case CROISER:
                st="Croiser  ";
                break;
            case DESTROYER:
                st="Destroyer";
                break;
            case SOUSMARIN:
                st="Sous-marin";
                break;
            case TORPILLEUR:
                st="Torpilleur";
                break;
            default:
                st="";
                break;
        }
        Etat et=armada[i]->etat;
        switch(et){
            case OK:
                st2="OK";
                break;
            case TOUCHE:
                st2="TOUCHE";
                break;
            case COULE:
                st2="COULE";
                break;
            default:
                st2="";
                break;
        }
        if(st != "")printf("%s\tEtat:%s\n",st,st2);
    }
    printf("\n");
}

int sortieMatrice(Matrice *m, int x, int y, int taille, Orientation o){
    /*
    Fonction permettant d'assurer qu'un nevire ne sort pas de la matrice
    Param. :
        m : matrice que l'on veut controller, Type : pointeur de Matrice
        x : valeur de l'axe des abcisse, Type : int
        y : valeur de l'axe des ordonnees, Type int
        taille : taille du navire a poser, Type: int
        o : Orientation que l'on utilise, Type Orientation
    */
    if(o==V && x+taille >= m->taille)return 1;
    if(o==H && y+taille >= m->taille)return 1;
    return 0;
}

int naviresColles(Matrice *m, int x, int y, int taille, Orientation o, int** tab){
    /*
    Fonction permettant d'assurer que les navires ne se touchent pas
    Param. :
        m : matrice que l'on veut controller, Type : pointeur de Matrice
        x : valeur de l'axe des abcisse, Type : int
        y : valeur de l'axe des ordonnees, Type int
        taille : taille du navire a poser, Type: int
        o : Orientation que l'on utilise, Type Orientation
        tab : matrice temporaire representat la ou il reste des emplacement libre sur m, Type: pointeur de pointeur de int
    */
    int maxi=m->taille-1, mini=0;
    for(int i=0;i<=taille;i++){
        if(o==V){
            if(tab[y+i][x] == 1)return 1;
        }else if(o==H){
            if(tab[y][x+i] == 1)return 1;
        }
    }
    for(int i=0;i<taille;i++){
        if(o==V){
            tab[y+i][x]=1;
            if(x+1 < maxi)tab[y+i][x+1]=1;
            if(x-1 > mini)tab[y+i][x-1]=1;
            if(y+taille > maxi)tab[y+taille][x]=1;
            if(y-1 < mini)tab[y+1][x]=1;
        }else if(o==H){
            tab[y][x+i]=1;
            if(y+1 < maxi)tab[y+1][x+i]=1;
            if(y-1 > mini)tab[y-1][x+i]=1;
            if(x+taille > maxi)tab[y][x+taille]=1;
            if(x-1 < mini)tab[y][x-1]=1;
        }
    }
    if(o==H){
        tab[y][x-1]=1;
        tab[y][x+taille]=1;
    }else if(o==V){
        tab[y-1][x]=1;
        tab[y+taille][x]=1;
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
    int tmp, x, y;
    NavireType nt;
    Orientation o;
    char tmpO;
    for(int i = 0; i < TAILLE_FLOTTE; i++){
        printf("Choisisser un navire:\n1. Torpilleur\n2. Destroyer\n3. Sous-marin\n4. Croiser\n5. Porte-avion\n> ");
        scanf("%d", &tmp);
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
        armada[i] = n;

        printf("\nPosition ?");
        printf("\ny=");
        scanf("%d",&y);
        printf("x=");
        scanf("%d",&x);

        printf("Orientation (H ou V)\n>");
        scanf("%s",&tmpO);

        if(tmpO == 72) o = H; else if(tmpO == 86) o = V; // 72 et 86 correspond au code ascii de H et V.

        while(sortieMatrice(m,(x-1),(y-1),getTailleNavire(nt),o) == 1){
            printf("\nHo non ! Le navire est hors du champs de bataille !\n");
            printf("\ny=");
            scanf("%d",&y);
            printf("x=");
            scanf("%d",&x);
            printf("Orientation (H ou V)\n>");
            scanf("%s",&tmpO);
            if(tmpO == 72) o = H; else if(tmpO == 86) o = V; // 72 et 86 correspond au code ascii de H et V.
        }
        while(naviresColles(m,(y-1),(x-1),getTailleNavire(nt),o,tableau2D) == 1){            
            printf("\nHo non ! Le navire est cote a cote a un autre !\n");
            printf("\ny=");
            scanf("%d",&y);
            printf("x=");
            scanf("%d",&x);
            printf("Orientation (H ou V)\n>");
            scanf("%s",&tmpO);
            if(tmpO == 72) o = H; else if(tmpO == 86) o = V; // 72 et 86 correspond au code ascii de H et V.
        }
        placementNavire(m,nt,(y-1),(x-1),o);
        afficherMatrice(m);

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
    generationArmadeStandard(m, armada);
    //afficherArmada(armada);
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
        //printf("## Navire %d : \n", num+1);
        int poser = 0;
        int angle;
        while(poser == 0){
            aleaX = generationIntAleatoire(maxi, mini);
            aleaY = generationIntAleatoire(maxi, mini);
            angle = generationIntAleatoire(4, 1);
            //printf("Angle : %d \n", angle);

            poser = 1;
            for(int i = 0; i < armada[num]->taille; i++){
                if(angle == 1){
                    if(aleaY-i >= mini && tableau2D[aleaX][aleaY-i] == 0){
                        //printf("--> X : %d  |  Y : %c \n", aleaX+1, 65+aleaY-i);
                    } else {
                        //printf("Positionnement en X : %d  |  Y : %c impossible \n", aleaX+1, 65+aleaY-i);
                        //printf("(%d) On doit changer d'angle .. \n", angle);
                        poser = 0;
                        //printf("Var. poser a %d ! \n", poser);
                        break;
                    }
                }

                if(angle == 2){
                    if(aleaX-i >= mini && tableau2D[aleaX-i][aleaY] == 0){
                        //printf("--> X : %d  |  Y : %c \n", aleaX-i+1, 65+aleaY);
                    } else {
                        //printf("Positionnement en X : %d  |  Y : %c impossible \n", aleaX-i+1, 65+aleaY);
                        //printf("(%d) On doit changer d'angle .. \n", angle);
                        poser = 0;
                        //printf("Var. poser a %d ! \n", poser);
                        break;
                    }
                }

                if(angle == 3){
                    if(aleaY+i <= maxi && tableau2D[aleaX][aleaY+i] == 0){
                        //printf("--> X : %d  |  Y : %c \n", aleaX+1, 65+aleaY+i);
                    } else {
                        //printf("Positionnement en X : %d  |  Y : %c impossible \n", aleaX+1, 65+aleaY+i);
                        //printf("(%d) On doit changer d'angle .. \n", angle);
                        poser = 0;
                        //printf("Var. poser a %d ! \n", poser);
                        break;
                    }
                }

                if(angle == 4){
                    if(aleaX+i <= maxi && tableau2D[aleaX+i][aleaY] == 0){
                        //printf("--> X : %d  |  Y : %c \n", aleaX+i+1, 65+aleaY);
                    } else {
                        //printf("Positionnement en X : %d  |  Y : %c impossible \n", aleaX+i+1, 65+aleaY);
                        //printf("(%d) On doit changer d'angle .. \n", angle);
                        poser = 0;
                        break;
                    }
                }
            } // Fin de boucle, on a vérifié que le navire peut être posé.
        } // Fin de boucle, on pose le navire.

        // On le place :
        //printf("C'est ok donc on le place. \n");
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
    // Affichage :
    afficherMatrice(m);
}

void generationArmadeStandard(Matrice *m, Navire **armada){
    /*
        Génére une flotte standard (soit 1 navire de chaque).
    */
    NavireType nt;
    printf("Creation d'une flotte standard .. \n");

    for(int i = 0; i < TAILLE_FLOTTE; i++){
        // On place en mémoire le navire.
        armada[i] = (Navire*)malloc(sizeof(Navire));
        // Type de navire.
        switch(i){
            case 4:
                nt = PORTEAVION;
                break;
            case 3:
                nt = CROISER;
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
        armada[i]->etat = OK;
        armada[i]->matrice = m;
        armada[i]->nom = nt;
        armada[i]->taille = getTailleNavire(nt);
        armada[i]->posX = (int*)malloc(armada[i]->taille * sizeof(int));
        armada[i]->posY = (int*)malloc(armada[i]->taille * sizeof(int));
    }
}

int generationIntAleatoire(int maximum, int minimum){
    return (rand() % (maximum - minimum + 1)) + minimum;
}

