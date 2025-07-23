#ifndef UTILISATEURS_H_INCLUDED
#define UTILISATEURS_H_INCLUDED

typedef struct {
    char login[6];         // Identifiant de connexion (5 lettres)
    char motDePasse[20];   // Mot de passe
    char prenom[30];       // Pr�nom
    char nom[30];          // Nom
    char telephone[15];    // Num�ro de t�l�phone
    char role[15];         // "ADMIN" ou "PHARMACIEN"
    int etat;              // 0 actif / -1 bloqu�
    int premiereConnexion; // 1 = jamais connect� (doit changer le mdp), 0 = d�j� connect�
} UTILISATEUR;


// Saisie d'un utilisateur
UTILISATEUR saisirUtilisateur();

// Ajouter un utilisateur
UTILISATEUR ajouterUtilisateur();

// Afficher tous les utilisateurs
void afficherUtilisateurs();

// Modifier un utilisateur
void modifierUtilisateur();

// Supprimer un utilisateur
void supprimerUtilisateur();

// V�rifier les identifiants et retourner le r�le (1=Admin, 2=Pharmacien, 0=�chec)
int connexionUtilisateur(char login[6], char motDePasse[20]);

// Changer le mot de passe
char changerMotDePasse(char login[]);


int ChangerEtatUtilisateur();





#endif
