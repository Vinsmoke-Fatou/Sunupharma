#include "init.h"

#include "utilisateurs.h"

#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>

void initialiserAdmin() {
    UTILISATEUR a;
    FILE *fu = NULL;

    // Initialisation des champs par defaut
    strcpy(a.role, "ADMIN");
    a.etat = 0;
    a.premiereConnexion = 0;
    fflush(stdin);

    // Ouverture en mode append binaire
    fu = fopen("USERS.dat", "ab");
    verifierFichier(fu);

    // Saisie et validation du login
    do {
        printf("Saisir le login (5 lettres majuscules) : ");
        lireChaine(a.login, sizeof(a.login));

        if (strlen(a.login) != 5) {
            afficherErreur("Le login doit contenir exactement 5 caractères.");
            continue;
        }

        int valide = 1;
        for (int i = 0; i < 5; i++) {
            if (a.login[i] < 'A' || a.login[i] > 'Z') {
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

    // Saisie du mot de passe
    printf("Entrer votre mot de passe : ");
    lireChaine(a.motDePasse, sizeof(a.motDePasse));
    fflush(stdin);

    // Saisie des informations personnelles
    printf("\nSaisir le prenom : ");
    lireChaine(a.prenom, sizeof(a.prenom));
    fflush(stdin);

    printf("\nSaisir le nom : ");
    lireChaine(a.nom, sizeof(a.nom));
    fflush(stdin);

    printf("\nSaisir le telephone : ");
    lireChaine(a.telephone, sizeof(a.telephone));
    fflush(stdin);

    // Écriture dans le fichier
    fwrite(&a, sizeof(UTILISATEUR), 1, fu);
    fclose(fu);

    afficherSucces("Administrateur enregistre avec succes !");
}



