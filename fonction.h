#ifndef FONCTION_H
#define FONCTION_H

typedef enum etat {ATTENTE,PLACEE,TOUCHE,COULE} Etat;
typedef enum navireType {PORTEAVION,CROISER,DESTROYER,SOUSMARIN,TORPILLEUR} NavireType;

typedef struct matrice Matrice;
typedef struct navire Navire;

struct matrice{
    int taille; // Taille de notre matrice.
    char **value; // Notre matrice (tableau à 2D).
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

// -- Variable(s) globale(s)


// -- Fonctions :
// Retourne la taille d'un navire en fonction de son type.
int getTailleNavire(NavireType nt);
// Fonction "genererNavire" permettant d'initialer un navire.
Navire *genererNavire(NavireType nt, Matrice *m);
// Fonction "placementNavire" permettant de placer un navire.
void placementNavire(Matrice *m, NavireType nt, int *posX, int *posY);
// Fonction "genererMatriceVide" permettant de créer une matrice vide.
Matrice* genererMatriceVide(char *titre, int taille_matrice);
// Fonction "afficherMatrice" qui permet d'afficher la matrice.
void afficherMatrice(Matrice *m);
// Fonction "choisirTaille" qui permet de choisir la taille de la grille. Passage par adresse de l'entier.
void choisirTaille(int *ptr);

#endif
