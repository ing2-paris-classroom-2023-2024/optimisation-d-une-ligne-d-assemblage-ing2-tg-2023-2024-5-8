#include "graphe.h"

// créer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->poids = poids; // Stockage du poids
        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;
        sommet[s1]->degre = 1;
        return sommet;
    }

    else
    {
        pArc temp=sommet[s1]->arc;
        while(temp->arc_suivant != NULL)
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->poids=poids; // Stockage du poids
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            sommet[s1]->degre++;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        sommet[s1]->degre++;
        return sommet;
    }
}

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille et liste des arcs avec leurs poids */
Graphe* lire_graphe(char* nomFichier) {
    Graphe* graphe;
    FILE* ifs = fopen(nomFichier, "r");
    int ordre, taille, s1, s2;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);
    graphe = CreerGraphe(ordre);
    graphe->ordre = ordre;

    // Lire la taille du graphe
    fscanf(ifs, "%d", &taille);
    graphe->taille = taille;

    // Lire les arêtes du graphe
    for (int i = 0; i < taille; ++i) {
        fscanf(ifs, "%d%d", &s1, &s2);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, 0);//initialise le poids a 0 supprimer si pas besoin
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, 0);
    }

    fclose(ifs);
    return graphe;
}


Graphe* lire_graphe_oriente(char* nomFichier) {
    Graphe* graphe;
    FILE* ifs = fopen(nomFichier, "r");
    int ordre, taille, s1, s2;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);
    graphe = CreerGraphe(ordre);
    graphe->ordre = ordre;

    // Lire la taille du graphe
    fscanf(ifs, "%d", &taille);
    graphe->taille = taille;

    // Lire les arêtes du graphe
    for (int i = 0; i < taille; ++i) {
        fscanf(ifs, "%d%d", &s1, &s2);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, 0);//initialise le poids a 0 supprimer si pas besoin
    }

    fclose(ifs);
    return graphe;
}



void lire_graphe_tps(char* nomFichier,Graphe *graphe) {

    FILE* ifs = fopen(nomFichier, "r");
    int ordre, taille,s1;
    float tps;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    while (fscanf(ifs, "%d%f", &s1, &tps) == 2) {
        graphe->pSommet[s1]->temps=tps;


    }
    for (int i=0;i<graphe->ordre;i++){
        printf("\nle sommet %d a un temps de %f",i,graphe->pSommet[i]->temps);
    }
    fclose(ifs);
}

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num)
{

    printf(" sommet %d :\n",num);

    pArc arc=sommet[num]->arc;

    while(arc!=NULL)
    {
        printf("%d ",arc->sommet);
        arc=arc->arc_suivant;
    }

}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("graphe\n");

    printf("ordre = %d\n",graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}





// exclusion

/* recherche en largeur (BFS) à partir d'un sommet donné */
int BFS(Graphe* graphe, int sommetInitial)
{
    // initialisation des structures de données pour BFS
    bool* visite = (bool*)malloc(graphe->ordre * sizeof(bool));
    pChemin chemin = NULL;
    pChemin chemin_temp = NULL;

    station resultat;
    resultat.station = (int*)malloc(sizeof(int) * graphe->ordre);
    resultat.taille = 0;

    for (int i = 0; i < graphe->ordre; i++)
        visite[i] = false;

    // file pour BFS
    int* file = (int*)malloc(graphe->ordre * sizeof(int));
    int debut = 0;
    int fin = 0;
    int etape = 0; // Variable pour suivre l'étape actuelle du BFS

    // ajouter le sommet initial à la file
    file[fin++] = sommetInitial;
    visite[sommetInitial] = true;

    while (debut < fin)
    {
        int tailleNiveau = fin - debut;
        printf("Etape %d : ", etape);

        for (int i = 0; i < tailleNiveau; i++)
        {
            int sommetCourant = file[debut++];
            printf("%d ", sommetCourant);

            // Ajouter les successeurs du sommet courant à la file
            pArc arc = graphe->pSommet[sommetCourant]->arc;
            while (arc != NULL)
            {
                int successeur = graphe->pSommet[arc->sommet]->valeur;
                if (!visite[successeur])
                {
                    visite[successeur] = true;
                    file[fin++] = successeur;
                }
                arc = arc->arc_suivant;
            }
        }

        printf("\n");
        etape++;
    }

    //libérer la mémoire
    free(visite);
    free(file);
    liberer_chemin(chemin);
    free(resultat.station);
    return etape;
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
void trouver_nb_stations(Graphe* graphe) {
    bool *visite = (bool *) malloc(graphe->ordre * sizeof(bool));
    int numero = 1;
    int etape_maximale = 0;//le nombre d'étape maximal de tous les bfs
    //creation de autant de tableau que d'ordre pour les differentes sommets a traiter dans les même stations

    for (int i = 0; i < graphe->ordre; i++)
        visite[i] = false;

    for (int sommet = 0; sommet < graphe->ordre; sommet++) {
        if (!visite[sommet]) {
            // nouvelle composante connexe
            pComposanteConnexe composante = init_composante(graphe->ordre);
            dfs_composante(graphe, visite, composante, sommet);

            // afficher le contenu de la composante
            printf("Composante connexe %d : ", numero++);
            afficher_composante(composante);

            // appliquer BFS sur la composante connexe
            printf("BFS sur la composante connexe : ");
            BFS(graphe, sommet);

            //trouver l'étape max du bfs en cours
            int etapes_composante = BFS(graphe, sommet);

            // Mettre à jour l'étape maximale
            if (etapes_composante > etape_maximale) {
                etape_maximale = etapes_composante;
            }

            // libérer la mémoire de la composante
            free(composante->sommets);
            free(composante);
            printf("\n");
        }
    }

    printf("le nombre de station necessaire est de %d\n", etape_maximale);
    free(visite);
}

//exclusion optimise


// Fonction pour trouver la couleur minimale non utilisée par les voisins
int trouverCouleurMinimale(struct Graphe* graphe, int sommetIndex) {
    int* couleursVoisins = (int*)malloc(graphe->ordre * sizeof(int));
    for (int i = 0; i < graphe->ordre; i++) {
        couleursVoisins[i] = -1;
    }

    struct Arc* arc = graphe->pSommet[sommetIndex]->arc;
    while (arc != NULL) {
        int couleurVoisin = graphe->pSommet[arc->sommet]->couleur;
        if (couleurVoisin != -1) {
            couleursVoisins[couleurVoisin] = couleurVoisin;
        }
        arc = arc->arc_suivant;
    }

    int couleur;
    for (couleur = 0; couleur < graphe->ordre; couleur++) {
        if (couleursVoisins[couleur] == -1) {
            break;
        }
    }

    free(couleursVoisins);
    return couleur;
}

// Fonction pour trouver la couleur chromatique du graphe
int couleurChromatique(struct Graphe* graphe) {

    // Initialiser les couleurs de tous les sommets
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->pSommet[i]->arc == NULL) {
            // Sommet isolé, peut être coloré avec 0
            graphe->pSommet[i]->couleur = 0;
        } else {
            graphe->pSommet[i]->couleur = -1;
        }
    }

    // Attribuer les couleurs
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->pSommet[i]->couleur == -1) {
            int couleur = trouverCouleurMinimale(graphe, i);
            graphe->pSommet[i]->couleur = couleur;
        }
    }

    int couleurMax = 0;
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->pSommet[i]->couleur > couleurMax) {
            couleurMax = graphe->pSommet[i]->couleur;
        }
    }

    return couleurMax + 1;
}

// Fonction pour trouver la couleur chromatique d'une composante connexe
int couleurChromatiqueComposante(struct Graphe* graphe, pComposanteConnexe composante) {
    // Réinitialiser les couleurs des sommets dans la composante connexe
    for (int i = 0; i < composante->taille; i++) {
        graphe->pSommet[composante->sommets[i]]->couleur = -1;
    }

    // Attribuer les couleurs
    for (int i = 0; i < composante->taille; i++) {
        int sommetIndex = composante->sommets[i];
        if (graphe->pSommet[sommetIndex]->couleur == -1) {
            int couleur = trouverCouleurMinimale(graphe, sommetIndex);
            graphe->pSommet[sommetIndex]->couleur = couleur;
        }
    }

    int couleurMax = 0;
    for (int i = 0; i < composante->taille; i++) {
        int sommetIndex = composante->sommets[i];
        if (graphe->pSommet[sommetIndex]->couleur > couleurMax) {
            couleurMax = graphe->pSommet[sommetIndex]->couleur;
        }
    }

    return couleurMax + 1;
}


// fonction pour déterminer les composantes connexes d'un graphe
void trouver_nb_stations_colo(Graphe* graphe) {
    bool *visite = (bool *) malloc(graphe->ordre * sizeof(bool));
    int numero = 1;
    int etape_maximale = 0;

    for (int i = 0; i < graphe->ordre; i++)
        visite[i] = false;

    for (int sommet = 0; sommet < graphe->ordre; sommet++) {
        if (!visite[sommet]) {
            pComposanteConnexe composante = init_composante(graphe->ordre);
            dfs_composante(graphe, visite, composante, sommet);

            printf("Composante connexe %d : ", numero++);
            afficher_composante(composante);

            // Calculer la couleur chromatique pour la composante connexe
            int couleurComposante = couleurChromatiqueComposante(graphe, composante);
            if (couleurComposante > etape_maximale) {
                etape_maximale = couleurComposante;
            }

            free(composante->sommets);
            free(composante);
            printf("\n");
        }
    }

    printf("Le nombre de couleurs maximal nécessaire est de %d\n", etape_maximale);
    free(visite);
}


//contrainte de precedence
bool* trouver_sources(Graphe* graphe, Graphe* graphe1) {
    // Tableau pour compter le nombre de prédécesseurs de chaque sommet
    int* comptePred = (int*)malloc(graphe->ordre * sizeof(int));
    for (int i = 0; i < graphe->ordre; i++) {
        comptePred[i] = 0;
    }

    // Tableau pour suivre les sommets déjà visités
    bool* dejaVu = (bool*)malloc(graphe->ordre * sizeof(bool));
    for (int i = 0; i < graphe->ordre; i++) {
        dejaVu[i] = false;
    }

    // Parcourir tous les sommets pour compter les prédécesseurs
    for (int i = 0; i < graphe->ordre; i++) {
        pArc arc = graphe->pSommet[i]->arc;
        while (arc != NULL) {
            comptePred[arc->sommet]++;
            arc = arc->arc_suivant;
        }
    }

    // Afficher les sommets sans prédécesseur (sources)
    printf("Les sommets sources du graphe sont : ");
    for (int i = 0; i < graphe->ordre; i++) {
        if (comptePred[i] == 0) {
            printf("%d ", i);
            dejaVu[i] = true;
        }
    }

    printf("\n");

    // Vérifier les successeurs dans le graphe non orienté
    for (int i = 0; i < graphe->ordre; i++) {
        if (dejaVu[i]) {
            pArc arc = graphe->pSommet[i]->arc;

            // Vérifier si le sommet n'a pas d'arc sortant
            if (arc == NULL) {
                dejaVu[i] = true;
                printf("le sommet %d est source 1\n",i);
            } else {
                // Vérifier si le successeur a un seul prédécesseur dans le graphe non orienté

                int successeur = arc->sommet;
                printf("le sucesseur de %d est %d\n",i,successeur);
                if(graphe->pSommet[successeur]->degre+1!=graphe1->pSommet[successeur]->degre)
                {
                    dejaVu[i]=false;
                    printf("le sommet %d n'est pas source\n",i);
                }

            }
        }
    }
    printf("les sommets sources sont : ");
    for (int i=0;i< graphe->ordre;i++){
        if (dejaVu[i]){
            printf("%d ",i);
        }
    }
    // Libérer la mémoire
    free(comptePred);
    printf("\n");
    return dejaVu;
}

float BFS_temps(Graphe* graphe, int sommetInitial)
{
    // initialisation des structures de données pour BFS
    bool* visite = (bool*)malloc(graphe->ordre * sizeof(bool));
    pChemin chemin = NULL;
    pChemin chemin_temp = NULL;
    float temps_total=0;

    for (int i = 0; i < graphe->ordre; i++)
        visite[i] = false;

    // file pour BFS
    int* file = (int*)malloc(graphe->ordre * sizeof(int));
    int debut = 0;
    int fin = 0;
    int etape = 0; // Variable pour suivre l'étape actuelle du BFS

    // ajouter le sommet initial à la file
    file[fin++] = sommetInitial;
    visite[sommetInitial] = true;

    while (debut < fin)
    {
        int tailleNiveau = fin - debut;

        float temps_max_etape = 0;

        for (int i = 0; i < tailleNiveau; i++)
        {
            int sommetCourant = file[debut++];

            // Ajouter les successeurs du sommet courant à la file
            pArc arc = graphe->pSommet[sommetCourant]->arc;
            while (arc != NULL)
            {
                int successeur = graphe->pSommet[arc->sommet]->valeur;
                if (!visite[successeur])
                {
                    visite[successeur] = true;
                    file[fin++] = successeur;
                }

                // Mettre à jour le temps maximal trouvé à chaque étape
                float temps_successeur = graphe->pSommet[arc->sommet]->temps;
                if (temps_successeur > temps_max_etape) {
                    temps_max_etape = temps_successeur;
                }

                arc = arc->arc_suivant;
            }
        }
        temps_total += temps_max_etape;
        etape++;
    }

    //libérer la mémoire
    free(visite);
    free(file);
    liberer_chemin(chemin);

    return temps_total;
}


float temps_total(Graphe *graphe, bool *source)
{
    float temps_total=0;
    for (int i =0;i< graphe->ordre;i++)
    {
        if(source[i]==1){
            float tempsbfs = BFS_temps(graphe,i);
            printf("le temps du bfs a partir du somment %d est de %f\n",i,tempsbfs);
            temps_total+=tempsbfs;
        }
    }
    return temps_total;
}

//liaison de toutes les fonctions

ResultatBFS BFS_temps_exlu(Graphe* grapheExclusion, Graphe* graphe_prece, int sommetInitial)
{
    // initialisation des structures de données pour BFS
    bool* visite = (bool*)malloc(graphe_prece->ordre * sizeof(bool));
    pChemin chemin = NULL;
    pChemin chemin_temp = NULL;
    int station = 0;
    float temps_total = 0;
    int sommetCourant = sommetInitial; // Déclarer la variable à l'extérieur de la boucle

    for (int i = 0; i < graphe_prece->ordre; i++)
        visite[i] = false;

    // file pour BFS
    int* file = (int*)malloc(graphe_prece->ordre * sizeof(int));
    int debut = 0;
    int fin = 0;
    int etape = 0; // Variable pour suivre l'étape actuelle du BFS

    // ajouter le sommet initial à la file
    file[fin++] = sommetInitial;
    visite[sommetInitial] = true;

    // Couleur du sommet initial dans le graphe d'exclusion
    int couleurInitiale = grapheExclusion->pSommet[sommetInitial]->couleur;

    while (debut < fin) {
        int tailleNiveau = fin - debut;
        float temps_max_etape = 0;

        for (int i = 0; i < tailleNiveau; i++) {
            sommetCourant = file[debut++];

            // Considérer aussi le temps du sommetCourant
            if (graphe_prece->pSommet[sommetCourant]->temps > temps_max_etape) {
                temps_max_etape = graphe_prece->pSommet[sommetCourant]->temps;
            }

            // Ajouter les successeurs du sommet courant à la file
            pArc arc = graphe_prece->pSommet[sommetCourant]->arc;
            while (arc != NULL) {
                int successeur = graphe_prece->pSommet[arc->sommet]->valeur;
                if (!visite[successeur]) {
                    visite[successeur] = true;
                    file[fin++] = successeur;

                    // Mettre à jour le temps maximal trouvé à chaque étape seulement pour les sommets non visités
                    if (graphe_prece->pSommet[successeur]->temps > temps_max_etape) {
                        temps_max_etape = graphe_prece->pSommet[successeur]->temps;
                    }
                }
                arc = arc->arc_suivant;
            }
        }

        // Vérifier la couleur du sommet actuel dans le graphe d'exclusion
        if (grapheExclusion->pSommet[sommetCourant]->couleur == couleurInitiale) {
            station++; // Augmenter le nombre de stations si la couleur est la même
            couleurInitiale = grapheExclusion->pSommet[sommetCourant]->couleur;
        }
        temps_total += temps_max_etape;
        etape++;
    }

    // libérer la mémoire
    free(visite);
    free(file);
    liberer_chemin(chemin);

    ResultatBFS resultat;
    resultat.temps_total = temps_total;
    resultat.nombre_stations = station;

    return resultat;
}


void planifier_et_calculer_temps_total(Graphe* grapheExclusion, Graphe* graphePrecOriente, Graphe* graphePrecNonOriente) {
    trouver_nb_stations_colo(grapheExclusion);

    bool* sources = trouver_sources(graphePrecOriente, graphePrecNonOriente);

    float tempsTotal = 0;
    int nombreStationsTotal = 0;

    for (int i = 0; i < graphePrecNonOriente->ordre; i++) {
        if (sources[i]) {
            printf("application du bfs sur le sommet %d\n",i);
            ResultatBFS resultat = BFS_temps_exlu(grapheExclusion, graphePrecOriente, i);
            printf("le temps de la source %d est %f\n",i,resultat.temps_total);
            tempsTotal += resultat.temps_total;
            nombreStationsTotal += resultat.nombre_stations;
        }
    }

    printf("Temps total nécessaire : %f\n", tempsTotal);
    printf("Nombre total de stations nécessaires : %d\n", nombreStationsTotal);

    free(sources);
}



