#ifndef PROJET_GRAPHE_H
#define PROJET_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

///--------------------------------------------STRUCTURES-------------------------------------------------

typedef struct {
    int sommet_depart, sommet_arrive, poids;
} Arete;

struct Pile {
    pSommet sommets[15];
    int sommetCourant;
};
// structure pour stocker une composante connexe
struct ComposanteConnexe
{
    int* sommets; // tableau des sommets dans la composante
    int taille;   // nombre de sommets dans la composante
};

// alias de pointeur sur une composante connexe
typedef struct ComposanteConnexe* pComposanteConnexe;
// structure pour stocker une composante connexe
struct ComposanteConnexe
{
    int* sommets; // tableau des sommets dans la composante
    int taille;   // nombre de sommets dans la composante
};

// alias de pointeur sur une composante connexe
typedef struct ComposanteConnexe* pComposanteConnexe;

/* structure pour stocker un chemin */
struct Chemin
{
    int sommet;
    struct Chemin* suivant;
};

/* alias de pointeur sur un Chemin */
typedef struct Chemin* pChemin;

/* structure d'un arc*/
struct Arc
{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int valeur;
    struct Arc* arc_suivant;
};

/* alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    int valeur;
    char couleur; //remplacé par visite
};

/* alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int orientation;
    int ordre;
    pSommet* pSommet;
} Graphe;

///--------------------------------------------FONCTIONS-------------------------------------------------

// créer le graphe
Graphe* CreerGraphe(int ordre);

// lire le graphe
Graphe * lire_graphe(char * nomFichier);

// ajouter l'arête entre les somets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2, int premierSommet);

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num);

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe);





#endif //PROJET_GRAPHE_H 
