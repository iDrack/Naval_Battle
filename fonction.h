#ifndef FONCTION_H
#define FONCTION_H

#define TAILLE_FLOTTE 5

typedef enum etat {OK,TOUCHE,COULE} Etat;
typedef enum navireType {PORTEAVION,CROISER,DESTROYER,SOUSMARIN,TORPILLEUR} NavireType;
typedef enum orientation {H,V} Orientation; // H=Horizontal, V=Vertical
typedef struct matrice Matrice;
typedef struct navire Navire;

struct matrice{
    int taille; // Taille de notre matrice.
    char **value; // Notre matrice (tableau � 2D).
    char *titre;
};

struct navire{
    NavireType nom;
    Etat etat;
    Matrice* matrice; // Pointeur de Matrice.
    int taille;
    // Positionnement (tableau d'entier).
    int *posX; // ex : 3, 4, 5
    int *posY; // ex : 2, 2, 2
    // Ajouter les tirs speciaux
};

// -- Fonctions :
// Retourne la taille d'un navire en fonction de son type.
int getTailleNavire(NavireType nt);
// Fonction "genererNavire" permettant d'initialer un navire, sans affectation de position.
Navire *genererNavire(NavireType nt, Matrice *m);
// Fonction "placementNavire" permettant de cr�er et placer un navire � une position donn�.
void placementNavire(Matrice *m, NavireType nt, int posX, int posY, Orientation o);
// Fonction "genererMatriceVide" permettant de cr�er une matrice vide (initialisation de la grille de jeu).
Matrice* genererMatriceVide(char *titre, int taille_matrice);
// Fonction "afficherMatrice" qui permet d'afficher la matrice/grille de jeu.
void afficherMatrice(Matrice *m);
// Fonction "choisirTaille" qui permet de choisir la taille de la grille. Passage par adresse de l'entier.
void choisirTaille(int *ptr);
// Fonction "genererArmada" permettant au joueur de generer son armada et de placer ses navires
void genererArmadaJoueur(Matrice *m, Navire **armada);

void afficherArmada(Navire **armada);
// Fonction "placementAleatoire" permettant de placer al�atoirement les navires sur une matrice donn�.
void placementAleatoire(Matrice *m);

#endif
