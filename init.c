#include "utilisateurs.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UTILISATEUR u;
FILE *fu;

void initialiserUtilisateurs() {
    fu = fopen("USERS.dat", "rb");

    // S'il n'existe pas encore d'utilisateurs (fichier vide ou inexistant)
    if (fu == NULL) {
        fu = fopen("USERS.dat", "wb");

        UTILISATEUR admin;

        strcpy(admin.login, "ADMIN");
        strcpy(admin.motDePasse, "admin1"); // Tu peux crypter plus tard si besoin
        strcpy(admin.prenom, "Bachar");
        strcpy(admin.nom, "Sandal");
        strcpy(admin.telephone, "787691261");
        strcpy(admin.role, "ADMIN");  // 1 = ADMIN ADMIN
        admin.etat = 0;
        admin.premiereConnexion = 0;

        fwrite(&admin, sizeof(UTILISATEUR), 1, fu);
        fclose(fu);

        afficherSucces("Administrateur de base créé avec succès.\n");
    } else {
        fclose(fu); // Fermer si le fichier existe
    }
}

