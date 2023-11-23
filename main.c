#include "Graphe.h"
#include <stdbool.h> // pour utiliser des booléens
#include "definition.c"
#include "exclusion.c"
#include "precedence.c"





/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num)
{
    printf("\n  sommet[%d]= %d",num,sommet[num]->valeur);
    //pArc arc=sommet[sommet[num]->valeur]->arc;
    pArc arc=sommet[num]->arc;
    while(arc!=NULL)
    {
        printf("\n    successeurs[%d]= %d",arc->sommet,sommet[arc->sommet]->valeur);
        arc=arc->arc_suivant;
    }
}



/* recherche en largeur (BFS) à partir d'un sommet donné */
void BFS(Graphe* graphe, int sommetInitial)
{
    printf("\nBFS : Debut du traitement BFS, sommet initial = %d",sommetInitial);
    // initialisation des structures de données pour BFS
    bool* visite = (bool*)malloc(graphe->ordre * sizeof(bool));
    pChemin chemin = NULL;
    pChemin chemin_temp = NULL;

    for (int i = 0; i < graphe->ordre; i++)
        visite[i] = false;

    // file pour BFS
    int* file = (int*)malloc(graphe->ordre * sizeof(int));
    int debut = 0;
    int fin = 0;

    // ajouter le sommet initial à la file
    file[fin++] = sommetInitial;
    visite[sommetInitial] = true;

    int sommetCourant = file[debut++];
    visite[sommetCourant] = true;
    printf("\nBFS :      sommet initial = %d, sommets relies : ",sommetCourant);
    // ajouter le sommet courant au chemin
    pChemin nouveau_chemin = (pChemin)malloc(sizeof(struct Chemin));
    nouveau_chemin->sommet = sommetCourant;
    nouveau_chemin->suivant = chemin;
    chemin = nouveau_chemin;

    // parcourir les successeurs du sommet courant
    pArc arc = graphe->pSommet[sommetCourant]->arc;

    while (arc != NULL)
    {
        int successeur = graphe->pSommet[arc->sommet]->valeur;
        if (!visite[successeur])
        {
            printf(" > %d",successeur);
            visite[successeur] = true;
            file[fin++] = successeur;
        }
        arc = arc->arc_suivant;
    }
    //libérer la mémoire
    free(visite);
    free(file);
    liberer_chemin(chemin);
}


//ajouter l'arête entre les sommets s1 et s2 du graphe

pSommet* CreerArete(pSommet* sommet,int s1,int s2, int premierSommet)
{
    //printf("\nCreer arrete (%d,%d) premierSommet=%d",s1,s2,premierSommet);
    if(sommet[s1-premierSommet]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2-premierSommet;
        sommet[s2-premierSommet]->valeur=s2;
        Newarc->arc_suivant=NULL;
        sommet[s1-premierSommet]->arc=Newarc;
        sommet[s1-premierSommet]->valeur=s1;
        return sommet;
    }
    else
    {
        pArc temp=sommet[s1-premierSommet]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2-premierSommet;
        sommet[s2-premierSommet]->valeur=s2;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2-premierSommet)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2-premierSommet;
            sommet[temp->sommet]->valeur=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

//créer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i; ///bizarre
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}




/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("\n================ Graphe ================ ");

    if(graphe->orientation)
        printf("\noriente\n");
    else
        printf("\nnon oriente\n");

    printf("ordre = %d\n",graphe->ordre);
    printf("taille = %d\n",graphe->taille);
    printf("listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}

/* fonction utilitaire pour afficher un chemin */
void afficher_chemin(pChemin chemin)
{
    if (chemin != NULL)
    {
        afficher_chemin(chemin->suivant);
        printf("%d -> ", chemin->sommet);
    }
}

/* fonction utilitaire pour libérer la mémoire d'un chemin */
void liberer_chemin(pChemin chemin)
{
    if (chemin != NULL)
    {
        liberer_chemin(chemin->suivant);
        free(chemin);
    }
}



// fonction pour initialiser une composante connexe
pComposanteConnexe init_composante(int taille)
{
    pComposanteConnexe composante = (pComposanteConnexe)malloc(sizeof(struct ComposanteConnexe));
    composante->sommets = (int*)malloc(taille * sizeof(int));
    composante->taille = 0;
    return composante;
}

// fonction pour ajouter un sommet à une composante connexe
void ajouter_sommet(pComposanteConnexe composante, int sommet)
{
    composante->sommets[composante->taille] = sommet;
    composante->taille++;
}

// fonction pour afficher le contenu d'une composante connexe
void afficher_composante(pComposanteConnexe composante)
{

    for (int i = 0; i < composante->taille; i++)
    {
        printf("%d ", composante->sommets[i]);
    }
    printf("\n");
}

//-----------------------------------------fonction DFS pour trouver une composante connexe----------------------------------------
void dfs_composante(Graphe* graphe, bool* visite, pComposanteConnexe composante, int sommetCourant)
{
    visite[sommetCourant] = true;
    ajouter_sommet(composante, sommetCourant);
    pArc arc = graphe->pSommet[sommetCourant]->arc;

    while (arc != NULL)
    {
        int successeur = arc->sommet;
        if (!visite[successeur])
        {
            dfs_composante(graphe, visite, composante, successeur);
        }
        arc = arc->arc_suivant;
    }
}

// fonction pour déterminer les composantes connexes d'un graphe
void trouver_composantes_connexes(Graphe* graphe)
{
    bool* visite = (bool*)malloc(graphe->ordre * sizeof(bool));
    int numero=1;
    for (int i = 0; i < graphe->ordre; i++)
        visite[i] = false;

    for (int sommet = 0; sommet < graphe->ordre; sommet++)
    {
        if (!visite[sommet])
        {
            // nouvelle composante connexe
            pComposanteConnexe composante = init_composante(graphe->ordre);
            dfs_composante(graphe, visite, composante, sommet);

            // afficher le contenu de la composante
            printf("Composante connexe %d : ",numero++);
            afficher_composante(composante);

            // libérer la mémoire de la composante
            free(composante->sommets);
            free(composante);
        }
    }
    free(visite);
}


int main() {
    
    Graphe* graphe_exclu = lire_graphe("exclusions.txt");
    Graphe* graphe_prece = lire_graphe("precedences.txt");
    graphe_afficher(graphe_exclu);
    graphe_afficher(graphe_prece);

    lire_graphe_tps("operations.txt",graphe_prece);



    for (int i=0;i<graphe_prece->ordre;i++)
    {
        printf("%d: %f\n",i,graphe_prece->pSommet[i]->temps);
    }


    ////////////////


    Graphe * g;

    char nom_fichier[100];

    printf("entrer le nom du fichier :");
    gets(nom_fichier);

    g = lire_graphe(nom_fichier);

    // affichage du graphe
    graphe_afficher(g);

    
    printf("\n===============            Composantes Connexes :            ===============  \n");
    trouver_composantes_connexes(g); //que pour le graphe pas oriente

    return 0;
}



