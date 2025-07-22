#ifndef CATEGORIES_H_INCLUDED
#define CATEGORIES_H_INCLUDED

typedef struct {
    int idCategorie;          // Identifiant unique de la cat�gorie
    char libelle[30];         // Nom de la cat�gorie (ex: Antibiotiques)
} CATEGORIE;

// Saisie d'une cat�gorie
CATEGORIE saisirCategorie();

// Obtenir le dernier ID enregistr�
int obtenirDernierIDCategorie();

// Afficher toutes les cat�gories
void afficherCategories();

// Ajouter une cat�gorie
void ajouterCategorie();

// Modifier une cat�gorie
void modifierCategorie();

// Supprimer une cat�gorie
void supprimerCategorie();

#endif
