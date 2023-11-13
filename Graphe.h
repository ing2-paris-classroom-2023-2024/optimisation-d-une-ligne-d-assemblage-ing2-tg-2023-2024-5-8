#ifndef PROJET_GRAPHE_H
#define PROJET_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

///--------------------------------------------STRUCTURES-------------------------------------------------
struct Arc {
    int sommet;
    int capacite;
    int flot;
    struct Arc* arc_suivant;
};

typedef struct Arc* pArc;

struct Sommet {
    struct Arc* arc;
    int valeur;
    char nom_sommet[2]; //modifier la taille du tableau si nécessaire
    int flux_min; //pour stocker le flux minimal du chemin augmentant
};

typedef struct Sommet* pSommet;

typedef struct Graphe {
    int taille;
    int ordre;
    pSommet* pSommet;
} Graphe;

typedef struct {
    int sommet_depart, sommet_arrive, poids;
} Arete;

struct Pile {
    pSommet sommets[15];
    int sommetCourant;
};

///--------------------------------------------FONCTIONS-------------------------------------------------
//fonction pour afficher les successeurs du sommet num
void afficher_successeurs(pSommet* sommet, int num);

//fonction pour créer le graphe
Graphe* CreerGraphe(int ordre);

//fonction pour lire le graphe depuis un fichier
Graphe* lire_graphe(char* nomFichier);


// structure pour stocker une composante connexe
struct ComposanteConnexe
{
    int* sommets; // tableau des sommets dans la composante
    int taille;   // nombre de sommets dans la composante
};

// alias de pointeur sur une composante connexe
typedef struct ComposanteConnexe* pComposanteConnexe;

#endif //PROJET_GRAPHE_H 
