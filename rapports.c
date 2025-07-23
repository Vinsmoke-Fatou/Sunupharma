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

// Compter le nombre de factures générées aujourd'hui
int compterVentesAujourdHui(const char *date) {
    WIN32_FIND_DATA trouverFichier;
    HANDLE hFind;
    char rechercheModele[MAX_PATH];
    int compteur = 0;

    // Vérification du format de la date
    if (strlen(date) != 8) {
        afficherErreur("Format de date invalide");
        return 0;
    }

    snprintf(rechercheModele, sizeof(rechercheModele), "BILLS\\RECU_%s*.txt", date);

    hFind = FindFirstFile(rechercheModele, &trouverFichier);
    if (hFind == INVALID_HANDLE_VALUE) {
        return 0;
    }

    do {
        if (!(trouverFichier.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            compteur++;
        }
    } while (FindNextFile(hFind, &trouverFichier) != 0);

    FindClose(hFind);
    return compteur;
}

// Calculer le montant total des ventes du jour
float totalVentesAujourdHui(const char *date) {
    WIN32_FIND_DATA trouverFichier;
    HANDLE hFind;
    char rechercheModele[MAX_PATH];
    char ligne[256];
    float total = 0.0;

    // Vérification du format de la date
    if (strlen(date) != 8) {
        afficherErreur("Format de date invalide");
        return 0.0;
    }

    snprintf(rechercheModele, sizeof(rechercheModele), "BILLS\\RECU_%s*.txt", date);

    hFind = FindFirstFile(rechercheModele, &trouverFichier);
    if (hFind == INVALID_HANDLE_VALUE) {
        return 0.0;
    }

    do {
        if (!(trouverFichier.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char chemin[MAX_PATH];
            snprintf(chemin, sizeof(chemin), "BILLS\\%s", trouverFichier.cFileName);

            FILE *f = fopen(chemin, "r");
            if (f == NULL) {
                continue;
            }

            while (fgets(ligne, sizeof(ligne), f)) {
                if (strstr(ligne, "TOTAL") != NULL) {
                    float montant = 0.0;
                    sscanf(ligne, "TOTAL TO PAY : %f", &montant);
                    total += montant;
                    break;
                }
            }

            fclose(f);
        }
    } while (FindNextFile(hFind, &trouverFichier) != 0);

    FindClose(hFind);
    return total;
}

// Écrire les alertes de stock
void ecrireAlertesStock(FILE *rapport) {
    FILE *fp = fopen("PRODUITS.dat", "rb");
    verifierFichier(fp);

    int seuil = 5;  // Seuil de stock critique
    int alerteTrouvee = 0;

    fprintf(rapport, "======================================================================\n");
    fprintf(rapport, " ALERTES DE STOCK CRITIQUE (< %d unites)\n", seuil);
    fprintf(rapport, "----------------------------------------------------------------------------------------\n");
    fprintf(rapport, " Code   | Designation                 | Stock restant\n");
    fprintf(rapport, "----------------------------------------------------------------------------------------\n");

    PRODUIT p;
    while (fread(&p, sizeof(PRODUIT), 1, fp) == 1) {
        if (p.quantite < seuil) {
            fprintf(rapport, " %-6s | %-25s |     %3d\n", p.code, p.designation, p.quantite);
            alerteTrouvee = 1;
        }
    }

    if (!alerteTrouvee) {
        fprintf(rapport, " Aucune alerte de stock.\n");
    }

    fprintf(rapport, "----------------------------------------------------------------------------------------\n");
    fclose(fp);
}

// Générer le rapport journalier
void genererRapportJournalier() {
    // Création du dossier DAILY si inexistant
    if (_mkdir("DAILY") == -1 && errno != EEXIST) {
        afficherErreur("Erreur de création du dossier DAILY");
        return;
    }

    char date[9];
    obtenirDateActuelle(date);

    // Vérification du format de la date
    if (strlen(date) != 8) {
        afficherErreur("Format de date invalide");
        return;
    }

    char nomFichier[50];
    snprintf(nomFichier, sizeof(nomFichier), "DAILY\\ETAT_%s.txt", date);

    // Calcul des totaux une seule fois
    int ventes = compterVentesAujourdHui(date);
    float montantTotal = totalVentesAujourdHui(date);

    FILE *rapport = fopen(nomFichier, "w");
    verifierFichier(rapport);

    fprintf(rapport, "======================================================================\n");
    fprintf(rapport, "            RAPPORT JOURNALIER DE VENTES - %s\n", date);
    fprintf(rapport, "======================================================================\n\n");

    fprintf(rapport, "Nombre total de ventes :         %d\n", ventes);
    fprintf(rapport, "Montant total des ventes :   %.2f XOF\n\n", montantTotal);

    ecrireAlertesStock(rapport);

    fclose(rapport);
    afficherSucces("Le rapport journalier a été créé avec succès.");
}
