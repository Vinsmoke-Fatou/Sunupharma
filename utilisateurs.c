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

// Saisir un nouvel utilisateur
UTILISATEUR saisirUtilisateur() {
    UTILISATEUR u;

    int choixRole;

    do {
        puts("\nChoisir le role : ");
        puts("1. ADMIN");
        puts("2. PHARMACIEN");
        printf("Votre choix (1 ou 2) : ");
        scanf("%d", &choixRole);

        if (choixRole != 1 && choixRole != 2) {
            afficherErreur("Choix invalide, veuillez entrer 1 ou 2.");
        }
    } while (choixRole != 1 && choixRole != 2);
    fflush(stdin);

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

    printf("\n======================================================================================\n");
    printf("  LOGIN   |    ROLE     |     NOM     |   PRENOM    |    TELEPHONE   |    ETAT   \n");
    printf("=========================================================================================\n");

    int vide = 1;
    char statut[8];

    while (fread(&u, sizeof(UTILISATEUR), 1, fu) == 1) {
        if (strcmp(u.role, "ADMIN") == 0) {
            printf("\033[1;34m");
        } else {
            printf("\033[1;32m");
        }

        if (u.etat == 0) {
            strcpy(statut, "actif");
        } else {
            strcpy(statut, "bloquer");
        }
        printf("  %-7s | %-11s | %-12s | %-12s | %-15s | %-9s\n", u.login, u.role, u.nom, u.prenom, u.telephone, statut);
        vide = 0;
    }

    printf("\033[0m");
    if (vide) {
        afficherInfo("Aucun utilisateur trouve.");
    }

    printf("==========================================\n");
    fclose(fu);
}

// Supprimer un utilisateur
void supprimerUtilisateur() {
    int trouve = 0;
    char login[6];

    do {
        printf("Saisir le login (5 lettres majuscules) : ");
        lireChaine(login, sizeof(login)); // ✅ pas de viderBuffer ici
        if (strlen(login) != 5) {
            afficherErreur("Le login doit contenir exactement 5 caractères.");
            continue;
        }

        int valide = 1;
        for (int i = 0; i < 5; i++) {
            if (login[i] < 'A' || u.login[i] > 'Z') {
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

// Connexion utilisateur
int connexionUtilisateur(char login[6], char motDePasse[20]) {
    FILE *fu = fopen("USERS.dat", "rb");
    verifierFichier(fu);

    UTILISATEUR u;

    while (fread(&u, sizeof(UTILISATEUR), 1, fu) == 1) {
        printf("Comparaison avec: %s\n", u.login);
        if (strcmp(login, u.login) == 0) {
            if (strcmp(motDePasse, u.motDePasse) == 0) {
                printf("Mot de passe correct !\n");
                fclose(fu);
                if (strcmp(u.role, "ADMIN") == 0) return 1;
                else return 2;
            }
        }
    }

    fclose(fu);
    printf("Connexion échouée\n");
    return -1;
}

// Modifier l'utilisateur
void modifierUtilisateur() {
    int trouve = 0;
    char login[6];

    do {
        printf("Saisir le login (5 lettres majuscules) : ");

        lireChaine(login, sizeof(login)); // ✅ pas de viderBuffer ici

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
    fflush(stdin);

    FILE *f = fopen("UTILISATEURS.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    verifierFichier(f);
    verifierFichier(temp);

    UTILISATEUR u;
    char statut [8];

    while (fread(&u, sizeof(UTILISATEUR), 1, f) == 1) {
        if (strcmp(login, u.login) == 0) {
            trouve = 1;
            if (u.etat == 0) {
                strcpy(statut, "actif");
            } else {
                strcpy(statut, "bloquer");
            }
            printf("\n=====================================\n");
            afficherSucces("Utilisateur trouve :");
            printf("=====================================\n");
            printf("Login : %s\n", u.login);
            printf("role : %s\n", u.role);
            printf("nom: %s\n", u.nom);
            printf("Prenom : %s\n", u.prenom);
            printf("Telephone : %s\n", u.telephone);
            printf("Mot de passe : %s\n", u.motDePasse);
            printf("Etat : %s\n", statut);
            printf("=====================================\n");
            printf("\nQue souhaitez-vous modifier ?\n");
            printf("1. Mot de passe\n2. Prénom\n3. Nom\n4. Téléphone\n");
            printf("5. Rôle\n6. Etat (0 actif / -1 bloqué)\n");
            printf("Choix : ");

            int choix;
            scanf("%d", &choix);
            fflush(stdin);

            switch (choix) {
                case 1:
                    printf("Nouveau mot de passe : ");
                    lireChaine(u.motDePasse, sizeof(u.motDePasse));
                    u.premiereConnexion = 0; // il a changé son mdp
                    fflush(stdin);
                    break;
                case 2:
                    printf("Nouveau prénom : ");
                    lireChaine(u.prenom, sizeof(u.prenom));
                    fflush(stdin);
                    break;
                case 3:
                    printf("Nouveau nom : ");
                    lireChaine(u.nom, sizeof(u.nom));
                    fflush(stdin);
                    break;
                case 4:
                    printf("Nouveau téléphone : ");
                    lireChaine(u.telephone, sizeof(u.telephone));
                    fflush(stdin);
                    break;
                case 5:
                    printf("Nouveau rôle (ADMIN ou PHARMACIEN) : ");
                    lireChaine(u.role, sizeof(u.role));
                    fflush(stdin);
                    break;
                case 6:
                    do {
                        printf("Nouvel état (0 = actif, -1 = bloqué) : ");
                        scanf("%d", &u.etat);
                        if (u.etat != 0 && u.etat != -1) {
                            afficherErreur("La valeur doit etre 0 ou -1");
                        } else break;
                    } while (1);
                    fflush(stdin);
                    break;
                default:
                    afficherErreur("Choix invalide.");
            }
        }

        fwrite(&u, sizeof(UTILISATEUR), 1, temp);
    }

    fclose(f);
    fclose(temp);
    remove("UTILISATEURS.dat");
    rename("temp.dat", "UTILISATEURS.dat");

    trouve ? afficherSucces("Utilisateur modifié.") :
             afficherErreur("Utilisateur non trouvé.");
}

// Modifier l'état d'un utilisateur
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
    fflush(stdin);

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




