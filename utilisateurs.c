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

UTILISATEUR u;
FILE *fu;

UTILISATEUR saisirUtilisateur() {
    UTILISATEUR u;

    int choixRole;

    do {
        puts("\nChoisir le role : ");
        puts("1. ADMIN");
        puts("2. PHARMACIEN");
        printf("Votre choix (1 ou 2) : ");
        scanf("%d", &choixRole);
        fflush(stdin);

        if (choixRole != 1 && choixRole != 2) {
            afficherErreur("Choix invalide, veuillez entrer 1 ou 2.");
        }
    } while (choixRole != 1 && choixRole != 2);

    if (choixRole == 1) {
        strcpy(u.role, "ADMIN");
    } else {
        strcpy(u.role, "PHARMACIEN");
    }
    fflush(stdin);

    do {
        printf("Saisir le login (5 lettres majuscules) : ");
        lireChaine(u.login, sizeof(u.login)); // ✅ pas de viderBuffer ici

        if (strlen(u.login) != 5) {
            afficherErreur("Le login doit contenir exactement 5 caractères.");
            continue;
        }

        int valide = 1;
        for (int i = 0; i < 5; i++) {
            if (u.login[i] < 'A' || u.login[i] > 'Z') {
                valide = 0;
                break;
            }
        }

        if (!valide) {
            afficherErreur("Tous les caractères doivent être des lettres majuscules (A-Z).");
        } else {
            break;
        }
    } while (1);
    fflush(stdin);

    strcpy(u.motDePasse, "pharma123");
    fflush(stdin);

    printf("\nSaisir le prenom : \n");
    lireChaine(u.prenom, sizeof(u.prenom));
    fflush(stdin);


    printf("\nSaisir le nom : \n");
    lireChaine(u.nom, sizeof(u.nom));
    fflush(stdin);

    printf("\nSaisir le telephone : \n");
    lireChaine(u.telephone, sizeof(u.telephone));
    fflush(stdin);

    u.etat = 0;

    u.premiereConnexion = 1;


    return u;
}

// Ajouter un utilisateur
UTILISATEUR ajouterUtilisateur() {
    fu = fopen("USERS.dat", "ab");
    verifierFichier(fu);

    UTILISATEUR u = saisirUtilisateur();
    fwrite(&u, sizeof(UTILISATEUR), 1, fu);

    fclose(fu);

    afficherSucces("Utilisateur enregistre avec succès.");
}

// Afficher tous les utilisateurs
void afficherUtilisateurs() {
    fu = fopen("USERS.dat", "rb");
    verifierFichier(fu);

    printf("\n=======================================================================\n");
    printf("  LOGIN   |    ROLE     |     NOM     |   PRÉNOM    |    TÉLÉPHONE   \n");
    printf("=======================================================================\n");

    int vide = 1;

    while (fread(&u, sizeof(UTILISATEUR), 1, fu) == 1) {
        if (strcmp(u.role, "ADMIN") == 0) {
            printf("\033[1;34m");
        } else {
            printf("\033[1;32m");
        }

        printf("  %-7s | %-11s | %-12s | %-12s | %-15s\n", u.login, u.role, u.nom, u.prenom, u.telephone);
        vide = 0;
    }

    printf("\033[0m");
    if (vide) {
        afficherInfo("Aucun utilisateur trouve.");
    }

    printf("═══════════════════════════════════════════════════════════════════════\n");
    fclose(fu);
}


// Supprimer un utilisateur
void supprimerUtilisateur() {
    int trouve = 0;
    char login[6];

    printf("Saisir le login de l'utilisateur à supprimer : ");
    lireChaine(login, sizeof(login));

    fu = fopen("UTILISATEURS.dat", "rb");
    FILE *tmp = fopen("tmp.dat", "wb");
    verifierFichier(fu);
    verifierFichier(tmp);

    while (fread(&u, sizeof(UTILISATEUR), 1, fu) == 1) {
        if (strcmp(login, u.login) == 0) {
            trouve = 1;

            afficherSucces("Utilisateur trouve :");
            printf("Login : %s\n", u.login);
            printf("Rôle : %s\n", u.role);
            printf("Nom : %s\n", u.nom);
            printf("Prenom : %s\n", u.prenom);
            printf("Telephone : %s\n", u.telephone);

            char confirmer;
            printf("\nÊtes-vous sûr de vouloir supprimer cet utilisateur ? (O/N) : ");
            scanf(" %c", &confirmer);
            fflush(stdin);

            if (confirmer == 'O' || confirmer == 'o') {
                afficherSucces("Utilisateur supprime.");
                continue; // Ne pas ecrire => suppression
            } else {
                afficherInfo("Suppression annulee.");
            }
        }
        fwrite(&u, sizeof(UTILISATEUR), 1, tmp);
    }

    fclose(fu);
    fclose(tmp);

    remove("USERS.dat");
    rename("tmp.dat", "USERS.dat");

    if (!trouve) {
        afficherErreur("Utilisateur introuvable.");
    }
}
;

// Connexion utilisateur
int connexionUtilisateur(char login[6], char motDePasse[20]) {
    fu = fopen("USERS.dat", "rb");
    verifierFichier(fu);

    while (fread(&u, sizeof(UTILISATEUR), 1, fu) == 1) {
        if (strcmp(login, u.login) == 0 && strcmp(motDePasse, u.motDePasse) == 0) {
            fclose(fu);
            if (strcmp(u.role, "ADMIN") == 0) return 1;
            else return 2;
        }
    }

    fclose(fu);
    return -1;
}

// Changer le mot de passe
void changerMotDePasse(char login[6]) {
    int trouve = 0;

    fu = fopen("USERS.dat", "rb");
    FILE *tmp = fopen("tmp.dat", "wb");
    verifierFichier(fu);
    verifierFichier(tmp);

    while (fread(&u, sizeof(UTILISATEUR), 1, fu) == 1) {
        if (strcmp(login, u.login) == 0) {
            trouve = 1;
            char nouveau[20];

            do {
                printf("Saisir le nouveau mot de passe (pas 'pharma123') : ");
                lireChaine(nouveau, sizeof(nouveau));
                if (strcmp(nouveau, "pharma123") == 0) {
                    afficherInfo("Vous devez changer le mot de passe par defaut.");
                } else {
                    strcpy(u.motDePasse, nouveau);
                    u.premiereConnexion = 0; // ✅ marque que le mot de passe a été changé
                    break;
                }
            } while (1);
        }
        fwrite(&u, sizeof(UTILISATEUR), 1, tmp);
    }

    fclose(fu);
    fclose(tmp);

    remove("USERS.dat");
    rename("tmp.dat", "USERS.dat");

    if (trouve) {
        afficherSucces("Mot de passe changé avec succès.");
    } else {
        afficherErreur("Login introuvable.");
    }
}


int ChangerEtatUtilisateur() {
    char login[6];
    int trouve = 0;

    // 1. Saisie et validation du login
    do {
        printf("Saisir le login (5 lettres majuscules) : ");
        lireChaine(login, sizeof(login));

        if (strlen(login) != 5) {
            afficherErreur("Le login doit contenir exactement 5 caractères.");
            continue;
        }

        int valide = 1;
        for (int i = 0; i < 5; i++) {
            if (login[i] < 'A' || login[i] > 'Z') {
                valide = 0;
                break;
            }
        }

        if (!valide) {
            afficherErreur("Tous les caractères doivent être des lettres majuscules (A-Z).");
        } else {
            break;
        }
    } while (1);

    // 2. Ouverture du fichier USERS.dat
    fu = fopen("USERS.dat", "rb+");
    verifierFichier(fu);

    // 3. Recherche et mise à jour
    while (fread(&u, sizeof(UTILISATEUR), 1, fu) == 1) {
        if (strcmp(u.login, login) == 0) {
            trouve = 1;

            // Inversion de l'état
            if (u.etat == 0) {
                u.etat = -1;
            } else {
                u.etat = 0;
            }

            // Réécriture dans le fichier
            fseek(fu, -sizeof(UTILISATEUR), SEEK_CUR);
            fwrite(&u, sizeof(UTILISATEUR), 1, fu);
            fclose(fu);

            (u.etat == -1)?afficherSucces("Utilisateur bloquer avec succes"):afficherSucces("Utilisateur debloquer avec succes");
            return u.etat; // Retourne l'état final
        }
    }

    fclose(fu);

    // 4. Utilisateur introuvable
    if (!trouve) {
        afficherErreur("Utilisateur introuvable.");
    }

    return -2; // Code spécial pour erreur
}

UTILISATEUR rechercherUtilisateur(char *login) {
    int trouve = 0;


    fu = fopen("USERS.dat", "rb");
    verifierFichier(fu);

    while (fread(&u, sizeof(UTILISATEUR), 1, fu) == 1) {
        if (strcmp(login, u.login) == 0) {
              return u;
        }
    }

    fclose(fu);

    if (!trouve) {
        afficherErreur("Utilisateur introuvable.");
    }
}





