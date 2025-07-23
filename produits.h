#ifndef PRODUITS_H_INCLUDED
#define PRODUITS_H_INCLUDED

typedef struct {
    char code[6];            // Format "MED01"
    char designation[30];    // Exemple: "Paracétamol 500mg"
    char date_peremption[9]; // Format "AAAAMMJJ"
    float prix;              // En XOF
    int quantite;            // Quantité en stock
    int id_categorie;        // Référence à la catégorie
} PRODUIT;

// Prototypes
PRODUIT saisirProduit();                       // Saisir un produit
void ajouterProduit();                         // Ajouter un produit
void modifierProduit();                        // Modifier un produit
void supprimerProduit();                       // Supprimer un produit
int rechercherProduit(const char *code);   // Chercher l'index d'un produit par code
void afficherRecherche();                      // Afficher un produit rechercher
int estPerime(const char* code);               // Vérifier si un produit est périmé
void afficherProduits();                       // Afficher tous les produits

#endif
