#include "produits.h"
#include "categories.h"
#include "utilisateurs.h"
#include "utils.h"
#include "ventes.h"
#include "rapports.h"
#include "menus.h"
#include "init.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void menuPrincipal() {
    int choix;
    do {
        system("cls");
        printf("========================================================\n");
        afficherSucces("        BIENVENUE DANS SUNUPHARMA       ");
        printf("========================================================\n");
        afficherInfo("1. Connexion");
        afficherInfo("0. Quitter");
        printf("-------------------------------------------------------\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        fflush(stdin);

        switch(choix) {
            case 1:
                menuConnexion();
                break;
            case 0:
                afficherInfo("Au revoir !");
                break;
            default:
                afficherErreur("Choix invalide. Veuillez reessayer.");
                Pause();
        }
    } while(choix != 0);
}


void menuConnexion() {
    char login[6];
    char password[20];
    int role = -1;
    int loginValide = 0;

    UTILISATEUR uTrouve;
    int utilisateurTrouve = 0;
    long pos = -1;

    FILE *fu = fopen("USERS.dat", "rb+");
    verifierFichier(fu);

    printf("\n=======================================\n");
    afficherSucces("           CONNEXION               ");
    printf("=======================================\n");

    // Étape 1 : Saisie du login avec validation
    do {
        printf("Saisir le login (5 lettres majuscules) : ");
        lireChaine(login, sizeof(login));

        if (strlen(login) != 5) {
            afficherErreur("Le login doit contenir exactement 5 caractères.");
            continue;
        }

        loginValide = 1;
        for (int i = 0; i < 5; i++) {
            if (login[i] < 'A' || login[i] > 'Z') {
                loginValide = 0;
                break;
            }
        }

        if (!loginValide) {
            afficherErreur("Tous les caractères doivent être des lettres majuscules (A-Z).");
        }

    } while (!loginValide);


    // Étape 2 : Recherche de l'utilisateur
    rewind(fu); // Rembobiner le fichier
    while (fread(&uTrouve, sizeof(UTILISATEUR), 1, fu) == 1) {
        if (strcmp(login, uTrouve.login) == 0) {
            utilisateurTrouve = 1;
            pos = ftell(fu) - sizeof(UTILISATEUR);
            break;
        }
    }

    if (!utilisateurTrouve) {
        fclose(fu);
        afficherErreur("Aucun utilisateur trouve avec ce login.");
        return;
    }

    // Étape 3 : Saisie du mot de passe
    printf("Entrer votre mot de passe : ");
    // Ajouter un getchar() pour consommer le \n restant
    getchar();
    lireChaine(password, sizeof(password));

    if (strcmp(password, uTrouve.motDePasse) != 0) {
        afficherErreur("Mot de passe invalide.");
        fclose(fu);
        return;
    }

    fclose(fu);

    // Étape 4 : Redirection vers le bon menu
    role = connexionUtilisateur(login, password);
    if (role == 1) {
        afficherSucces("Connexion ADMIN reussie !");
        Pause();
        menuAdministrateur(login);
    } else if (role == 2) {
        afficherSucces("Connexion PHARMACIEN reussie !");
        Pause();
        menuPharmacien(login);
    } else {
        afficherErreur("Erreur lors de la connexion.");
    }
}



void menuAdministrateur(char login[]) {
    int choix;
    do {
        system("cls");
        printf("\n=======================================\n");
        afficherSucces("        MENU ADMINISTRATEUR        \n");
        printf("=======================================\n");
        afficherInfo("1. Gestion des produits");
        afficherInfo("2. Gestion des categories");
        afficherInfo("3. Gestion des utilisateurs");
        afficherInfo("0. Deconnexion");
        printf("=======================================\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        fflush(stdin);

        switch (choix) {
            case 1:
                menuProduits();
                break;
            case 2:
                menuCategories();
                break;
            case 3:
                menuUtilisateurs();
                break;
            case 0:
                afficherInfo("Deconnexion...");
                return;
            default:
                afficherErreur("Choix invalide. Veuillez reessayer.");
                Pause();
        }
    } while (1);
}

void menuProduits() {
    int choix;
    do {
        system("cls");
        printf("\n=======================================\n");
        afficherSucces("     GESTION DES PRODUITS          ");
        printf("=======================================\n");
        afficherInfo("1. Afficher tous les produits");
        afficherInfo("2. Ajouter un produit");
        afficherInfo("3. Modifier un produit");
        afficherInfo("4. Supprimer un produit");
        afficherInfo("5. Rechercher un produit par code");
        afficherInfo("0. Retour");
        printf("=======================================\n");
        afficherInfo("Choisissez une option : ");
        scanf("%d", &choix);
        fflush(stdin);

        switch (choix) {
            case 1:
                afficherProduits();
                Pause();
                break;
            case 2:
                ajouterProduit();
                Pause();
                break;
            case 3:
                modifierProduit();
                Pause();
                break;
            case 4:
                supprimerProduit();
                Pause();
                break;
            case 5:
                afficherRecherche();
                Pause();
                break;
            case 0:
                return;
            default:
                afficherErreur("Choix invalide.");
                Pause();
        }
    } while (1);
}

void menuCategories() {
    int choix;
    do {
        system("cls");
        printf("\n=======================================\n");
        afficherSucces("     GESTION DES CATEGORIES        ");
        printf("=======================================\n");
        afficherInfo("1. Afficher toutes les categories");
        afficherInfo("2. Ajouter une categorie");
        afficherInfo("3. Modifier une categorie");
        afficherInfo("4. Supprimer une categorie");
        afficherInfo("0. Retour\n");
        printf("=======================================\n");
        afficherInfo("Choisissez une option : ");
        scanf("%d", &choix);
        fflush(stdin);

        switch (choix) {
            case 1:
                afficherCategories();
                Pause();
                break;
            case 2:
                ajouterCategorie();
                Pause();
                break;
            case 3:
                modifierCategorie();
                Pause();
                break;
            case 4:
                supprimerCategorie();
                Pause();
                break;
            case 0:
                return;
            default:
                afficherErreur("Choix invalide.");
                Pause();
        }
    } while (1);
}

void menuUtilisateurs() {
    int choix;
    do {
        system("cls");
        printf("\n=======================================\n");
        afficherSucces("     GESTION DES UTILISATEURS      ");
        printf("=======================================\n");
        afficherInfo("1. Afficher tous les utilisateurs");
        afficherInfo("2. Ajouter un utilisateur");
        afficherInfo("3. Supprimer un utilisateur");
        afficherInfo("4. Bloquer ou debloquer un utilisateur");
        afficherInfo("5. Modifier un utilisateur");
        afficherInfo("0. Retour\n");
        printf("=======================================\n");
        afficherInfo("Choisissez une option : ");
        scanf("%d", &choix);
        fflush(stdin);

        switch (choix) {
            case 1:
                afficherUtilisateurs();
                Pause();
                break;
            case 2:
                ajouterUtilisateur();
                Pause();
                break;
            case 3:
                supprimerUtilisateur();
                Pause();
                break;
            case 4:
                ChangerEtatUtilisateur();
                Pause();
                break;
            case 5:
                modifierUtilisateur();
                break;
            case 0:
                return;
            default:
                afficherErreur("Choix invalide.");
                Pause();
        }
    } while (1);
}

void menuPharmacien(char login[]) {
    int choix;
    do {
        system("cls");
        printf("\n=======================================\n");
        afficherSucces("         MENU PHARMACIEN           ");
        printf("=======================================\n");
        afficherInfo("1. Vendre un produit");
        afficherInfo("2. Consulter le stock");
        afficherInfo("3. Generer rapport journalier");
        afficherInfo("0. Deconnexion\n");
        printf("=======================================");
        afficherInfo("Choisissez une option : ");
        scanf("%d", &choix);
        fflush(stdin);

        switch (choix) {
            case 1:
                vendreProduit(login);
                Pause();
                break;
            case 2:
                afficherProduits();
                Pause();
                break;
            case 3:
                genererRapportJournalier();
                Pause();
                break;
            case 0:
                afficherInfo("Deconnexion...");
                return;
            default:
                afficherErreur("Choix invalide.");
                Pause();
        }
    } while (1);
}
