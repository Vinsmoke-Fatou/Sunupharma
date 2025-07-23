#ifndef CATEGORIES_H_INCLUDED
#define CATEGORIES_H_INCLUDED

typedef struct {
    int idCategorie;          // Identifiant unique de la catégorie
    char libelle[50];         // Nom de la catégorie (ex: Antibiotiques)
} CATEGORIE;

// Saisie d'une catégorie
CATEGORIE saisirCategorie();

// Obtenir le dernier ID enregistré
int obtenirDernierIDCategorie();

// Afficher toutes les catégories
void afficherCategories();

// Ajouter une catégorie
void ajouterCategorie();

// Modifier une catégorie
void modifierCategorie();

// Supprimer une catégorie
void supprimerCategorie();

#endif
