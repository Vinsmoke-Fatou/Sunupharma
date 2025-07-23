#ifndef VENTES_H_INCLUDED
#define VENTES_H_INCLUDED

// Récupérer la date et l'heure actuelles
char* obtenirHeureActuelle();

// Générer une facture d'achat
void genererFacture(char login[], PRODUIT prod, int quantiteVendue, float prixTotal);

// Vendre un produit (saisie + traitement)
void vendreProduit(char login[]);

#endif
