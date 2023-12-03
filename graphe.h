#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* Structure d'un arc*/
struct Arc
{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int poids;
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    float temps;
    int valeur;
    int degre;
    int couleur;

};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int ordre;
    pSommet* pSommet;
} Graphe;

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

/* structure pour stocker un chemin */
struct Chemin
{
    int sommet;
    struct Chemin* suivant;
};

/* alias de pointeur sur un Chemin */
typedef struct Chemin* pChemin;

typedef struct{
    int *station;
    int taille
}station;

typedef struct{
    bool* source;
    bool* source_isole
}res_source;

// créer le graphe
Graphe* CreerGraphe(int ordre);

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids);

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num);

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe);

Graphe* lire_graphe(char* nomFichier);
Graphe* lire_graphe_oriente(char* nomFichier);
void lire_graphe_tps(char* nomFichier,Graphe *graphe);


//fonction de la contrainte exclusion
int BFS(Graphe* graphe, int sommetInitial);
void afficher_chemin(pChemin chemin);
void liberer_chemin(pChemin chemin);
pComposanteConnexe init_composante(int taille);
void ajouter_sommet(pComposanteConnexe composante, int sommet);
void afficher_composante(pComposanteConnexe composante);
void dfs_composante(Graphe* graphe, bool* visite, pComposanteConnexe composante, int sommetCourant);
void trouver_nb_stations(Graphe* graphe);

//fonction contrainte precedence
res_source trouver_sources(Graphe* graphe,Graphe *graphe1);
float BFS_temps(Graphe* graphe, int sommetInitial);
float temps_total(Graphe *graphe,bool *source,bool* source_isole);

//algo pour la coloration
int trouverCouleurMinimale(struct Graphe* graphe, int sommet);
int couleurChromatique(struct Graphe* graphe);
void trouver_nb_stations_colo(Graphe* graphe);
int couleurChromatiqueComposante(struct Graphe* graphe, pComposanteConnexe composante);


//lien entre toutes les contraintes
int ** BFS_temps_exlu(Graphe* grapheExclusion, Graphe* graphe_prece, int sommetInitial,int **matrice, bool* sommet_isole);
void planifier_et_calculer_temps_total(Graphe* grapheExclusion, Graphe* graphePrecOriente, Graphe* graphePrecNonOriente);

#endif
