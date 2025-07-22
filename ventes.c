#include "produits.h"
#include "categories.h"
#include "utilisateurs.h"
#include "utils.h"
#include "ventes.h"
#include "rapports.h"
#include "menus.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

PRODUIT p;
FILE *fp;

// Obtenir la date et l'heure actuelles
char* obtenirHeureActuelle() {
    static char horodatage[15];
    time_t t = time(NULL);
    struct tm *maintenant = localtime(&t);
    snprintf(
        horodatage, sizeof(horodatage), "%04d%02d%02d%02d%02d%02d",
        maintenant->tm_year + 1900,
        maintenant->tm_mon + 1,
        maintenant->tm_mday,
        maintenant->tm_hour,
        maintenant->tm_min,
        maintenant->tm_sec
    );
    return horodatage;
}

// Generer un reçu
void genererFacture(char login[], PRODUIT prod, int quantite, float prixTotal) {
    const char* horodatage = obtenirHeureActuelle();

    char nomFichier[70];
    snprintf(nomFichier, sizeof(nomFichier), "BILLS/RECU_%s_%s_%s.txt", horodatage, prod.code, login);

    FILE *fFacture = fopen(nomFichier, "w");
    verifierFichier(fFacture);

    fprintf(fFacture, "===============================================================\n");
    fprintf(fFacture, "               RECU DE LA PHARMACIE                   \n");
    fprintf(fFacture, "===============================================================\n");
    fprintf(fFacture, "Date        : %s\n", horodatage);
    fprintf(fFacture, "Vendu par   : %s\n", login);
    fprintf(fFacture, "---------------------------------------------------------------------------------------------------\n");
    fprintf(fFacture, " Code produit : %-5s\n", prod.code);
    fprintf(fFacture, " Designation  : %-25s\n", prod.designation);
    fprintf(fFacture, " Prix unitaire: %8.2f XOF\n", prod.prix);
    fprintf(fFacture, " Quantite     : %8d\n", quantite);
    fprintf(fFacture, "---------------------------------------------------------------------------------------------------\n");
    fprintf(fFacture, " TOTAL À PAYER: %8.2f XOF\n", prixTotal);
    fprintf(fFacture, "===============================================================\n");
    fprintf(fFacture, "       Merci pour votre achat et votre confiance!     \n");
    fprintf(fFacture, "===============================================================\n");

    fclose(fFacture);

    afficherSucces("Facture generee avec succès.");
}

// Vendre un produit
void vendreProduit(char login[]) {
    char code[6];
    int trouve = 0;

    do {
        printf("Saisir le code du produit (5 caractères) : ");
        lireChaine(code, sizeof(code));
    } while (strlen(code) != 5);

    fp = fopen("PRODUITS.dat", "rb+");
    verifierFichier(fp);

    PRODUIT prod;

    while (fread(&prod, sizeof(PRODUIT), 1, fp) == 1) {
        if (strcmp(code, prod.code) == 0) {
            trouve = 1;

            afficherSucces("Produit trouve");
            printf("Code        : %s\n", prod.code);
            printf("Designation : %s\n", prod.designation);
            printf("Date peremption : %s\n", prod.date_peremption);
            printf("Prix       : %.2f\n", prod.prix);
            printf("Quantite   : %d\n", prod.quantite);
            printf("ID Categorie : %d\n", prod.id_categorie);

            // Verifier la peremption
            if (estPerime(prod.code)) {
                afficherErreur("Ce produit est perime.");
                fclose(fp);
                return;
            } else {
                afficherSucces("Ce produit est encore valide.");
            }

            // Saisie quantite
            int quantite;
            do {
                printf("Saisir la quantite à vendre : ");
                scanf("%d", &quantite);
                viderBufferEntree();
                if (quantite > prod.quantite) {
                    afficherInfo("Stock insuffisant.");
                }
            } while (quantite <= 0 || quantite > prod.quantite);

            // Calcul total
            float total = quantite * prod.prix;
            printf("Montant total : %.2f XOF\n", total);

            // Mise à jour du stock
            prod.quantite -= quantite;

            // Revenir en arrière pour reecrire l'enregistrement
            fseek(fp, -sizeof(PRODUIT), SEEK_CUR);
            fwrite(&prod, sizeof(PRODUIT), 1, fp);

            afficherSucces("Stock mis à jour avec succès.");

            fclose(fp);
            genererFacture(login, prod, quantite, total);
            return;
        }
    }

    fclose(fp);

    if (!trouve) {
        afficherErreur("Produit introuvable.");
    }
}

