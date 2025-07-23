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

// Variable globale
FILE *fc;

// Obtenir le dernier ID de categorie
int obtenirDernierIDCategorie() {
    fc = fopen("CATEGORIES.dat", "rb");
    int dernierId = 0;
    verifierFichier(fc);
    CATEGORIE c;

    while (fread(&c, sizeof(CATEGORIE), 1, fc) == 1) {
        dernierId = c.idCategorie;
    }

    fclose(fc);
    return dernierId;
}

// Saisir une nouvelle categorie
CATEGORIE saisirCategorie() {
    CATEGORIE c;
    afficherInfo("=== Saisie d'une nouvelle categorie ===");
    printf("Saisir le libelle de la categorie : ");
    lireChaine(c.libelle, sizeof(c.libelle));
    fflush(stdin);

    c.idCategorie = obtenirDernierIDCategorie() + 1;

    return c;
}

// Ajouter une categorie
void ajouterCategorie() {
    fc = fopen("CATEGORIES.dat", "ab");
    verifierFichier(fc);

    CATEGORIE c = saisirCategorie();

    fwrite(&c, sizeof(CATEGORIE), 1, fc);

    fclose(fc);

    afficherSucces("Categorie enregistree avec succès.");
}

// Modifier une categorie
void modifierCategorie() {
    int trouve = 0;
    int id;

    printf("Saisir l'ID de la categorie à modifier : ");
    scanf("%d", &id);
    fflush(stdin);

    CATEGORIE c;

    fc = fopen("CATEGORIES.dat", "rb");
    FILE *tmp = fopen("tmp.dat", "wb");
    verifierFichier(fc);
    verifierFichier(tmp);

    while (fread(&c, sizeof(CATEGORIE), 1, fc) == 1) {
        if (id == c.idCategorie) {
            trouve = 1;
            int choix;
            printf("Que souhaitez-vous modifier ?\n");
            printf("1. Libelle\n");
            printf("2. ID\n");
            printf("Choix : ");
            scanf("%d", &choix);
            fflush(stdin);

            if (choix == 1) {
                printf("Nouveau libelle de la categorie : ");
                lireChaine(c.libelle, sizeof(c.libelle));
                fflush(stdin);
            } else if (choix == 2) {
                printf("Nouvel ID de la categorie : ");
                scanf("%d", &c.idCategorie);
                fflush(stdin);
            } else {
                afficherErreur("Choix invalide.");
            }
        }
        fwrite(&c, sizeof(CATEGORIE), 1, tmp);
    }

    fclose(tmp);
    fclose(fc);
    remove("CATEGORIES.dat");
    rename("tmp.dat", "CATEGORIES.dat");

    if (trouve) {
        afficherSucces("Categorie modifiee avec succès.");
    } else {
        afficherErreur("Categorie non trouvee.");
    }
}

// Supprimer une categorie
void supprimerCategorie() {
    int trouve = 0;
    int id;

    printf("Saisir l'ID de la categorie à supprimer : ");
    scanf("%d", &id);
    fflush(stdin);

    CATEGORIE c;

    fc = fopen("CATEGORIES.dat", "rb");
    FILE *tmp = fopen("tmp.dat", "wb");
    verifierFichier(fc);
    verifierFichier(tmp);

    while (fread(&c, sizeof(CATEGORIE), 1, fc) == 1) {
        if (id == c.idCategorie) {
            trouve = 1;
            char confirmer;
            afficherErreur("Attention : Cette action est irreversible !");
            afficherInfo("Êtes-vous sûr de vouloir supprimer cette categorie ? (O/N) : ");
            scanf(" %c", &confirmer);
            fflush(stdin);

            if (confirmer == 'O' || confirmer == 'o') {
                afficherSucces("Categorie supprimee avec succès.");
                // Ne pas ecrire = suppression
                continue;
            } else {
                afficherInfo("Suppression annulee.");
            }
        }
        fwrite(&c, sizeof(CATEGORIE), 1, tmp);
    }

    fclose(tmp);
    fclose(fc);
    remove("CATEGORIES.dat");
    rename("tmp.dat", "CATEGORIES.dat");

    if (!trouve) {
        afficherErreur("Categorie non trouvee.");
    }
}

// Afficher toutes les categories
void afficherCategories() {
    FILE *fc = fopen("CATEGORIES.dat", "rb");
    verifierFichier(fc);

    printf("\n==============================================================\n");
    printf("  %-5s | %-30s\n", "ID", "Libelle");
    printf("==============================================================\n");

    int vide = 1;
    CATEGORIE c;
    while (fread(&c, sizeof(CATEGORIE), 1, fc) == 1) {
        printf("  %-5d | %-30s\n", c.idCategorie, c.libelle);
        vide = 0;
    }

    if (vide) {
        afficherInfo("Aucune categorie trouvee.");
    }

    printf("===========================================\n");
    fclose(fc);
}
