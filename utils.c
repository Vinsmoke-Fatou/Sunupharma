#include "produits.h"
#include "categories.h"
#include "utilisateurs.h"
#include "utils.h"
#include "ventes.h"
#include "rapports.h"
#include "menus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Lit une chaîne de caractères depuis l'entrée standard
void lireChaine(char *chaine, int taille) {
    fgets(chaine, taille, stdin);
    chaine[strcspn(chaine, "\n")] = '\0';  // Supprime le saut de ligne
}

//// Vide le buffer d'entrée après un scanf()
//void viderBufferEntree() {
//    int c;
//    while ((c = getchar()) != '\n' && c != EOF);
//}

// Vérifie si un fichier est ouvert correctement
void verifierFichier(FILE *fichier) {
    if (fichier == NULL) {
        afficherErreur("Impossible d'ouvrir le fichier.");
        exit(1);
    }
}

// Affichage coloré
void afficherSucces(const char* message) {
    printf("\033[32m %s\033[0m\n", message);
}

void afficherErreur(const char* message) {
    printf("\033[31m %s\033[0m\n", message);
}

void afficherInfo(const char* message) {
    printf("\033[36m %s\033[0m\n", message);
}

// Obtient la date actuelle au format AAAAMMJJ
void obtenirDateActuelle(char *dateBuffer) {
    time_t maintenant = time(NULL);
    struct tm *date = localtime(&maintenant);

    snprintf(dateBuffer, 9, "%04d%02d%02d",
             date->tm_year + 1900,
             date->tm_mon + 1,
             date->tm_mday);
}

// Met le programme en pause jusqu'à l'appui sur Entrée
void Pause() {
    printf("\nAppuyez sur Entrée pour continuer...");
    while (getchar() != '\n'); // consomme jusqu’au \n
}
