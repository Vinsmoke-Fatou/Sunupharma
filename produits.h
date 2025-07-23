#ifndef PRODUITS_H_INCLUDED
#define PRODUITS_H_INCLUDED

typedef struct {
    char code[6];            // Format "MED01"
    char designation[30];    // Exemple: "Parac�tamol 500mg"
    char date_peremption[9]; // Format "AAAAMMJJ"
    float prix;              // En XOF
    int quantite;            // Quantit� en stock
    int id_categorie;        // R�f�rence � la cat�gorie
} PRODUIT;

// Prototypes
PRODUIT saisirProduit();                       // Saisir un produit
void ajouterProduit();                         // Ajouter un produit
void modifierProduit();                        // Modifier un produit
void supprimerProduit();                       // Supprimer un produit
int rechercherProduit(const char *code);   // Chercher l'index d'un produit par code
void afficherRecherche();                      // Afficher un produit rechercher
int estPerime(const char* code);               // V�rifier si un produit est p�rim�
void afficherProduits();                       // Afficher tous les produits

#endif
