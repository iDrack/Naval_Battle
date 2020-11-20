#ifndef FONCTION_H
#define FONCTION_H

#define TAILLE 10

typedef enum etat{ATTENTE,PLACEE,TOUCHE,COULE}Etat;
typedef enum navireType{PORTEAVION,CROISER,DESTROYER,SOUSMARIN,TORPILLEUR}NavireType;

typedef struct matrice{
    int taille; //Taille de notre matrice
    char value[TAILLE][TAILLE]; //Notre matrice
    char *titre;
}Matrice;

typedef struct navire{
    NavireType nom;
    Etat etat;
    Matrice *matrice;
    int taille;
    //Ajouter les tris speciaux
}Navire;

Navire *genererNavire(NavireType nt, Matrice *m);
Matrice* genererMatriceVide(char *titre);
void afficherMatrice(Matrice *m);

#endif
