#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
    int donnee;
    struct noeud *suivant;
    struct noeud *precedent;
} Noeud;
typedef Noeud* Pointeur_Noeud;


// --------------------------------------------------
// Fonctions de base et d'insertion compactes
// --------------------------------------------------

Pointeur_Noeud creer_noeud(int donnee) {
    Pointeur_Noeud nouveau = (Pointeur_Noeud)malloc(sizeof(Noeud));
    if (!nouveau) { perror("Erreur d'allocation memoire"); exit(EXIT_FAILURE); }
    nouveau->donnee = donnee;
    nouveau->suivant = nouveau->precedent = NULL;
    return nouveau;
}

// Fonction pour libérer toute la mémoire allouée (plus courte)
void liberer_liste(Pointeur_Noeud tete) {
    if (!tete) return;
    Pointeur_Noeud courant = tete, prochain;
    tete->precedent->suivant = NULL; // Rompre la circularite
    while (courant) {
        prochain = courant->suivant;
        free(courant);
        courant = prochain;
    }
}

// Fonction d'insertion en tête (début) - Version compacte
Pointeur_Noeud inserer_tete(Pointeur_Noeud tete, int donnee) {
    Pointeur_Noeud nouveau = creer_noeud(donnee);
    
    // Cas 1 : Liste vide
    if (!tete) {
        nouveau->suivant = nouveau->precedent = nouveau;
        return nouveau; // La nouvelle tête est le nouveau nœud
    }
    
    // Cas 2 : Liste non vide
    Pointeur_Noeud queue = tete->precedent; 

    // Mettre à jour les liens des trois nœuds (Nouveau, Tete, Queue)
    nouveau->suivant = tete;
    nouveau->precedent = queue;
    
    tete->precedent = nouveau; 
    queue->suivant = nouveau;
    
    printf("--> Insertion de %d en TETE reussie.\n", donnee);
    return nouveau; // La nouvelle tête est le nouveau nœud
}

// Fonction d'insertion en queue (fin) - Version compacte
Pointeur_Noeud inserer_queue(Pointeur_Noeud tete, int donnee) {
    Pointeur_Noeud nouveau = creer_noeud(donnee);

    // Cas 1 : Liste vide (identique à l'insertion en tête)
    if (!tete) {
        nouveau->suivant = nouveau->precedent = nouveau;
        printf("--> Insertion de %d en QUEUE (liste vide) reussie.\n", donnee);
        return nouveau; // La nouvelle tête est le nouveau nœud
    }

    // Cas 2 : Liste non vide
    Pointeur_Noeud queue = tete->precedent;

    // Mettre à jour les liens
    nouveau->suivant = tete;
    nouveau->precedent = queue;

    tete->precedent = nouveau;       
    queue->suivant = nouveau;        
    
    printf("--> Insertion de %d en QUEUE reussie.\n", donnee);
    return tete; // La tête reste la même
}


// --------------------------------------------------
// Fonctions d'interaction utilisateur (Inchangées pour la clarté)
// --------------------------------------------------

void afficher_liste(Pointeur_Noeud tete) {
    if (!tete) { printf("La liste est vide.\n"); return; }
    Pointeur_Noeud courant = tete;
    printf("\n[ETAT ACTUEL DE LA LISTE (TETE -> ... -> QUEUE)]\n");
    printf("--------------------------------------------------\n");
    do {
        printf("[%d] ", courant->donnee);
        if (courant->suivant != tete) {
            printf("<-> ");
        }
        courant = courant->suivant;
    } while (courant != tete);
    printf("\n--------------------------------------------------\n");
    printf("(Tete: %d / Queue: %d)\n", tete->donnee, tete->precedent->donnee);
}

Pointeur_Noeud creer_liste_interactive() {
    Pointeur_Noeud tete = NULL;
    int donnee, reponse;
    printf("--- INITIALISATION DE LA LISTE DOUBLEMENT CHAINEE CIRCULAIRE ---\n");
    do {
        printf("Veuillez entrer un element a ajouter (entier) : ");
        if (scanf("%d", &donnee) != 1) {
            printf("Entree invalide.\n");
            while (getchar() != '\n');
            continue;
        }
        // Utilisation de la nouvelle signature (tete = inserer_queue(tete, donnee))
        tete = inserer_queue(tete, donnee);
        afficher_liste(tete);
        printf("Voulez-vous ajouter un autre element ? (1 pour OUI, 0 pour NON) : ");
        if (scanf("%d", &reponse) != 1) { reponse = 0; }
    } while (reponse == 1);
    return tete;
}

// --------------------------------------------------
// Fonction principale (main)
// --------------------------------------------------

int main() {
    Pointeur_Noeud ma_liste = creer_liste_interactive();
    int choix;
    int donnee;
    
    do {
        printf("\n\n--- OPERATIONS D'INSERTION ---\n");
        printf("1. Inserer en TETE\n");
        printf("2. Inserer en QUEUE\n");
        printf("0. Quitter et liberer la memoire\n");
        printf("Votre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            printf("Choix invalide.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choix == 1 || choix == 2) {
            printf("Element a inserer (entier) : ");
            if (scanf("%d", &donnee) != 1) {
                printf("Entree invalide.\n");
                while (getchar() != '\n');
                continue;
            }
            
            // L'appel utilise le type de retour pour mettre à jour ma_liste
            if (choix == 1) {
                ma_liste = inserer_tete(ma_liste, donnee);
            } else { // choix == 2
                ma_liste = inserer_queue(ma_liste, donnee);
            }
            afficher_liste(ma_liste);
        } else if (choix != 0) {
            printf("Option non reconnue.\n");
        }
        
    } while (choix != 0);

    liberer_liste(ma_liste);
    return 0;
}
