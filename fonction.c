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
    printf("\n%s : \n", m->titre);
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

void genererArmadaJoueur(Matrice *m, Navire **armada){
    /*
    Génére l'armada du joueur.
    Param. :
        m : matrice ou l'on ajoute, type : pointeur de navire.
        armada : liste des navire du joueur, type : liste de pointeur de Navire.
    */

    //TODO Gérer les collisions !
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
        //Navire *n=genererNavire(nt,m);
        Navire *n = malloc(sizeof(Navire));
        n->etat = OK;
        n->matrice = m;
        n->nom = nt;
        n->taille = getTailleNavire(nt);
        armada[i] = n;

        printf("\nPosition ?");
        printf("\nx=");
        scanf("%d",&x);
        printf("y=");
        scanf("%d",&y);

        printf("Orientation (H ou V)\n>");
        scanf("%s",&tmpO);

        if(tmpO == 72) o = H; else if(tmpO == 86) o = V; // 72 et 86 correspond au code ascii de H et V.
        placementNavire(m,nt,(y-1),(x-1),o);
        afficherMatrice(m);

        printf("\n");
    }
}

void placementAleatoire(Matrice *m, Navire **armada){
    /*
    Génére l'armada du joueur.
    Param. :
        m : matrice où l'on ajoute, type : pointeur de navire.
        armada : liste des navire du joueur ou de l'adversaire, type : liste de pointeur de Navire.
    */
    generationArmadeStandard(m, armada);
    int nombreAleatoireX, nombreAleatoireY;
    int maximum = m->taille, minimum = 1;
    int orientationAleatoire;

    // Parcours tous les navires de l'armada pour le placement.
    for(int num = 0; num < TAILLE_FLOTTE; num++){
        int selection = 0;
        while(selection == 0){
            // Génération du nombre aléatoire :
            srand(time(NULL));
            // Position ?
            nombreAleatoireX = (rand() % (maximum - minimum + 1)) + minimum;
            nombreAleatoireY = (rand() % (maximum - minimum + 1)) + minimum;
            while( m->value[nombreAleatoireX][nombreAleatoireY] != '.' ){
                nombreAleatoireX = (rand() % (maximum - minimum + 1)) + minimum;
                nombreAleatoireY = (rand() % (maximum - minimum + 1)) + minimum;
            }

            // Orientation ?
            int orientOK = 0;
            int recommencer = 0;
            while(orientOK == 0 && recommencer < 2){
                orientOK = 1;
                orientationAleatoire = (rand() % (maximum - minimum + 1)) + minimum;
                if(orientationAleatoire >= (maximum / 2)){
                    for(int i = 0; i < armada[num]->taille; i++){
                        if( m->value[nombreAleatoireX+i][nombreAleatoireY] != '.' ){
                            orientOK = 0;
                            recommencer++;
                            break;
                        }
                    }

                    if(orientOK == 1){
                        selection = 1;
                        for(int i = 0; i < armada[num]->taille; i++){
                            armada[num]->posX[i] = nombreAleatoireX+i;
                            armada[num]->posY[i] = nombreAleatoireY;
                        }
                    }
                } else {
                    for(int i = 0; i < armada[num]->taille; i++){
                        if( m->value[nombreAleatoireX][nombreAleatoireY+i] != '.' ){
                            orientOK = 0;
                            recommencer++;
                            break;
                        }
                    }

                    if(orientOK == 1){
                        selection = 1;
                        for(int i = 0; i < armada[num]->taille; i++){
                            armada[num]->posX[i] = nombreAleatoireX;
                            armada[num]->posY[i] = nombreAleatoireY+i;
                        }
                    }
                }
            }
        }
    }

    // En cours ..
    afficherMatrice(m);
}

void generationArmadeStandard(Matrice *m, Navire **armada){
    /*
        Génére une flotte standard (soit 1 navire de chaque).
    */
    NavireType nt;

    for(int i = 0; i < TAILLE_FLOTTE; i++){
        // On place en mémoire le navire.
        armada[i] = (Navire*)malloc(sizeof(Navire));
        // Type de navire.
        switch(i){
            case 5:
                nt = PORTEAVION;
                break;
            case 4:
                nt = CROISER;
                break;
            case 3:
                nt = DESTROYER;
                break;
            case 2:
                nt = SOUSMARIN;
                break;
            case 1:
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

