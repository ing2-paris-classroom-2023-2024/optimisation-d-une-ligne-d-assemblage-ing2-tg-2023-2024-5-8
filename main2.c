#include "definition.c"
#include "exclusion.c"
#include "precedence.c"

int main() {
    printf("Hello, World!\n");

    Graphe* graphe_exclu = lire_graphe("exclusions.txt");
    Graphe* graphe_prece = lire_graphe("precedences.txt");
    graphe_afficher(graphe_exclu);
    graphe_afficher(graphe_prece);

    lire_graphe_tps("operations.txt",graphe_prece);



    for (int i=0;i<graphe_prece->ordre;i++)
    {
        printf("%d: %f\n",i,graphe_prece->pSommet[i]->temps);
    }

    return 0;
}

//ajouter dans lire qui lise la taille du fichier avec le nombre de ligne et ensuite faire un tuc special pour le temps a la place du poids ?
