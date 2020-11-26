#ifndef FONCTION_H
#define FONCTION_H

#define TAILLE_FLOTTE 5
#define TYPE_TIR 5

typedef enum etat {OK,TOUCHE,COULE} Etat;
typedef enum navireType {PORTEAVION,CROISER,DESTROYER,SOUSMARIN,TORPILLEUR} NavireType;
typedef enum tirSpecial {NORMAL,BARAGE,CANONS,BONBARDEMENT} TirType;
typedef enum orientation {H,V} Orientation; // H = Horizontal, V = Vertical
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
    // Tir(s) :
    TirType tir;
};

// -- Fonctions :
// Retourne la taille d'un navire en fonction de son type.
int getTailleNavire(NavireType nt);
// Fonction "genererNavire" permettant d'initialer un navire, sans affectation de position.
Navire *genererNavire(NavireType nt, Matrice *m);
// Fonction "placementNavire" permettant de créer et placer un navire à une position donné.
void placementNavire(Matrice *m, NavireType nt, int posX, int posY, Orientation o);
// Fonction "genererMatriceVide" permettant de cr�er une matrice vide (initialisation de la grille de jeu).
Matrice* genererMatriceVide(char *titre, int taille_matrice);
// Fonction "afficherMatrice" qui permet d'afficher la matrice/grille de jeu.
void afficherMatrice(Matrice *m);
// Fonction "choisirTaille" qui permet de choisir la taille de la grille. Passage par adresse de l'entier.
void choisirTaille(int *ptr);
// Fonction "sortieMatrice" permettant de verifier si un navire ne sort pas de la matrice.
int sortieMatrice(Matrice *m, int x, int y, int taille, Orientation o);
// Fonction "naviresColles" permettant de verifier si 2 navires se supperpose ou sont trop proche.
int naviresColles(Matrice *m, int x, int y, int taille, Orientation o, int** tab);
// Fonction "genererArmada" permettant au joueur de generer son armada et de placer ses navires.
void genererArmadaJoueur(Matrice *m, Navire **armada);
// Fonction "afficherArmada" permettant d'afficher l'armada d'un joueur.
void afficherArmada(Navire **armada);
// Fonction "placementAleatoire" permettant de placer aléatoirement les navires sur une matrice donné (avec des navires non collé entre eux).
void placementAleatoire(Matrice *m, Navire **armada);
// Fonction "generationArmadaStandard" permettant de génére une flotte standard composée de 5 bateaux (soit 1 navire de chaque).
void generationArmadaStandard(Matrice *m, Navire **armada);
// Fonction "generationIntAleatoire" permettant de générer un nombre aléatoire entre deux valeurs.
int generationIntAleatoire(int maximum, int minimum);
// Fonction "fonctionTir" qui renvoie un pointeur sur un tableau alloué dynamiquement.
int** fonctionTir(int posX, int posY, int choixTir, int direction, Matrice *m);
// Fonction "effectuerTir" qui permet au joueur d'effectuer un tir sur la matrice cible passé en paramètre.
void effectuerTir(Matrice *m, Navire **armadaJoueur, Navire **armadaAdversaire);
// Fonction "modifierEtatNavire" permettant de modifier l'état du navire situé à la position posX et posY de l'armada passé en paramètre.
void modifierEtatNavire(int positionX, int positionY, Navire **armada);

#endif
