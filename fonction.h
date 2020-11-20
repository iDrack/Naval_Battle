#ifndef FONCTION_H
#define FONCTION_H

#define TAILLE 10

typedef enum etat {ATTENTE,PLACEE,TOUCHE,COULE} Etat;
typedef enum navireType {PORTEAVION,CROISER,DESTROYER,SOUSMARIN,TORPILLEUR} NavireType;

typedef struct matrice Matrice;
typedef struct navire Navire;

struct matrice{
    int taille; // Taille de notre matrice.
    char value[TAILLE][TAILLE]; // Notre matrice.
    char *titre;
};

struct navire{
    NavireType nom;
    Etat etat;
    Matrice *matrice;
    int taille;
    // Ajouter les tirs speciaux
};

Navire *genererNavire(NavireType nt, Matrice *m);
Matrice* genererMatriceVide(char *titre);
void afficherMatrice(Matrice *m);

#endif
