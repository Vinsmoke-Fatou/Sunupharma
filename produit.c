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

PRODUIT p;
FILE *fp;

// Saisie d'un nouveau produit
PRODUIT saisirProduit() {
    char dateAujourdhui[9];
    obtenirDateActuelle(dateAujourdhui);

    afficherInfo("=== Saisie d'un nouveau produit ===");

    do {
        printf("Saisir le code du produit (5 caractères) : ");
        lireChaine(p.code, sizeof(p.code));
    } while (strlen(p.code) != 5);

    printf("Saisir la designation : ");
    lireChaine(p.designation, sizeof(p.designation));

    do {
        printf("Saisir la date de peremption [AAAAMMJJ] : ");
        lireChaine(p.date_peremption, sizeof(p.date_peremption));
        if (strcmp(p.date_peremption, dateAujourdhui) <= 0) {
            afficherErreur("La date de peremption doit être superieure à aujourd'hui.");
        }
    } while (strcmp(p.date_peremption, dateAujourdhui) <= 0);

    do {
        printf("Saisir le prix : ");
        scanf("%f", &p.prix);
        fflush(stdin);
    } while (p.prix <= 0);

    do {
        printf("Saisir la quantite en stock : ");
        scanf("%d", &p.quantite);
        fflush(stdin);
    } while (p.quantite < 0);

    printf("Saisir l'ID de categorie : ");
    scanf("%d", &p.id_categorie);
    fflush(stdin);

    return p;
}

// Ajout d'un produit
void ajouterProduit() {
    fp = fopen("PRODUITS.dat", "ab");
    verifierFichier(fp);

    PRODUIT p = saisirProduit();
    fwrite(&p, sizeof(PRODUIT), 1, fp);

    fclose(fp);
    afficherSucces("Produit enregistre avec succès");
}

// Modification d'un produit
void modifierProduit() {
    int trouve = 0;
    char code[6];
    do {
        printf("Saisir le code du produit à modifier (5 caractères) : ");
        lireChaine(code, sizeof(code));
    } while (strlen(code) != 5);

    fp = fopen("PRODUITS.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    verifierFichier(fp);
    verifierFichier(temp);

    while (fread(&p, sizeof(PRODUIT), 1, fp) == 1) {
        if (strcmp(code, p.code) == 0) {
            trouve = 1;
            printf("\nQue souhaitez-vous modifier ?\n");
            printf("1. Code\n2. Designation\n3. Date peremption\n");
            printf("4. Prix\n5. Quantite\n6. Categorie\n");
            printf("Choix : ");

            int choix;
            scanf("%d", &choix);
            fflush(stdin);

            switch (choix) {
                case 1:
                    printf("Nouveau code : ");
                    lireChaine(p.code, sizeof(p.code));
                    break;
                case 2:
                    printf("Nouvelle designation : ");
                    lireChaine(p.designation, sizeof(p.designation));
                    break;
                case 3: {
                    char dateAujourdhui[9];
                    obtenirDateActuelle(dateAujourdhui);

                    do {
                        printf("Nouvelle date peremption [AAAAMMJJ] : ");
                        lireChaine(p.date_peremption, sizeof(p.date_peremption));
                        if (strcmp(p.date_peremption, dateAujourdhui) <= 0) {
                            afficherErreur("La nouvelle date doit être posterieure à aujourd'hui.");
                        }
                    } while (strcmp(p.date_peremption, dateAujourdhui) <= 0);
                    break;
                }
                case 4:
                    printf("Nouveau prix : ");
                    scanf("%f", &p.prix);
                    fflush(stdin);
                    break;
                case 5:
                    printf("Nouvelle quantite : ");
                    scanf("%d", &p.quantite);
                    fflush(stdin);
                    break;
                case 6:
                    printf("Nouvel ID de categorie : ");
                    scanf("%d", &p.id_categorie);
                    fflush(stdin);
                    break;
                default:
                    afficherErreur("Choix invalide.");
            }
        }
        fwrite(&p, sizeof(PRODUIT), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("PRODUITS.dat");
    rename("temp.dat", "PRODUITS.dat");

    trouve ? afficherSucces("Produit modifie") :
             afficherErreur("Produit non trouve");
}

// Suppression d'un produit
void supprimerProduit() {
    int verif = 0;
    char code[6];
    do {
        printf("Saisir le code du produit à supprimer (5 caractères) : ");
        lireChaine(code, sizeof(code));
    } while (strlen(code) != 5);

    fp = fopen("PRODUITS.dat", "rb");
    FILE *tmp = fopen("tmp.dat", "wb");
    verifierFichier(fp);
    verifierFichier(tmp);

    while (fread(&p, sizeof(PRODUIT), 1, fp) == 1) {
        if (strcmp(code, p.code) == 0) {
            verif = 1;
            char confirmer;
            afficherInfo("\nEtes-vous sûr de vouloir supprimer ce produit ? (Y/N) : ");
            scanf(" %c", &confirmer);
            fflush(stdin);
            if (confirmer == 'Y' || confirmer == 'y') {
                afficherSucces("Produit supprime avec succès");
                continue;
            } else {
                afficherInfo("Suppression annulee.");
            }
        }
        fwrite(&p, sizeof(PRODUIT), 1, tmp);
    }

    fclose(fp);
    fclose(tmp);
    remove("PRODUITS.dat");
    rename("tmp.dat", "PRODUITS.dat");

    if (!verif) {
        afficherErreur("Produit non trouvr.");
    }
}

// Recherche d'un produit (retourne 1 si trouve)
int trouverProduitParCode(const char *code) {
    fp = fopen("PRODUITS.dat", "rb");
    verifierFichier(fp);

    int trouve = 0;
    while (fread(&p, sizeof(PRODUIT), 1, fp) == 1) {
        if (strcmp(code, p.code) == 0) {
            trouve = 1;
            break;
        }
    }

    fclose(fp);
    return trouve;
}

// Affiche les infos d'un produit cherche par code
void afficherRecherche() {
    char code[6];
    do {
        printf("Saisir le code du produit a rechercher (5 caractères) : ");
        lireChaine(code, sizeof(code));
    } while (strlen(code) != 5);

    fp = fopen("PRODUITS.dat", "rb");
    verifierFichier(fp);

    int trouve = 0;
    while (fread(&p, sizeof(PRODUIT), 1, fp) == 1) {
        if (strcmp(code, p.code) == 0) {
            trouve = 1;
            printf("\n=====================================\n");
            afficherSucces("Produit trouve :");
            printf("=====================================\n");
            printf("Code : %s\n", p.code);
            printf("Designation : %s\n", p.designation);
            printf("Date peremption : %s\n", p.date_peremption);
            printf("Prix : %.2f\n", p.prix);
            printf("Quantite : %d\n", p.quantite);
            printf("ID Categorie : %d\n", p.id_categorie);
            printf("=====================================\n");
            break;
        }
    }

    if (!trouve) {
        afficherErreur("Produit non trouve.");
    }

    fclose(fp);
}

// Verifie si un produit est perime
int estPerime(const char* code) {
    char aujourd[9];
    obtenirDateActuelle(aujourd);

    fp = fopen("PRODUITS.dat", "rb");
    verifierFichier(fp);

    int perime = -1;

    while (fread(&p, sizeof(PRODUIT), 1, fp) == 1) {
        if (strcmp(code, p.code) == 0) {
            perime = (strcmp(p.date_peremption, aujourd) < 0);
            break;
        }
    }

    fclose(fp);

    return perime;
}

// Affiche tous les produits
void afficherProduits() {
    fp = fopen("PRODUITS.dat", "rb");
    verifierFichier(fp);

    printf("\n==============================================================\n");
    printf("%-6s | %-20s | %-8s | %-5s\n", "CODE", "NOM", "PRIX", "QTE");
    printf("================================================================\n");

    while (fread(&p, sizeof(PRODUIT), 1, fp)) {
        printf("%-6s | %-20s | %8.2f | %5d\n",
               p.code, p.designation, p.prix, p.quantite);
    }

    fclose(fp);
}

