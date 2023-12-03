#include "definition.c"

int main() {

    Graphe* graphe_exclu = lire_graphe("exclusions.txt");
    Graphe* graphe_prece = lire_graphe_oriente("precedences.txt");
    Graphe* graphe_prece_no = lire_graphe("precedences.txt");
    //graphe_afficher(graphe_exclu);
    //graphe_afficher(graphe_prece);
    //graphe_afficher(graphe_prece_no);

    lire_graphe_tps("operations.txt",graphe_prece);

    //exclusion
    printf("\n===============            contrainte Exclsuion :            ===============  \n");
    trouver_nb_stations_colo(graphe_exclu);

    //precedence
    printf("\n===============            contrainte precedence :            ===============  \n");

    res_source sommet_source=trouver_sources(graphe_prece,graphe_prece_no);
    printf("Tableau sommet_source : ");
    for (int i = 0; i < graphe_prece->ordre; i++) {//le nombre de sommet source max est forcement l'ordre du graphe
        printf("%d ", sommet_source.source[i]);

    }
    printf("\nles sommets isoles sont : ");
    for (int i = 0; i < graphe_prece->ordre; i++){
        if (sommet_source.source_isole[i]==1)
        printf("%d ",i);
    }

    printf("\n");

    float temps= temps_total(graphe_prece,sommet_source.source,sommet_source.source_isole);
    printf("le temps total du cycle est de %f\n\n",temps);

    printf("\n===============            liaison de toutes les contraintes :            ===============  \n");


    planifier_et_calculer_temps_total(graphe_exclu,graphe_prece,graphe_prece_no);

    return 0;
}

