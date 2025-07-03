# SunupharmaManagement - Application Console de Gestion Pharmaceutique
Présentation

Cette application console, développée en langage C, a été conçue pour la gestion des stocks et des ventes de la pharmacie SUNUPHARMA. Elle permet d’automatiser la gestion des médicaments, des utilisateurs (admins et pharmaciens), des ventes, ainsi que la génération de rapports quotidiens.

Fonctionnalités

- Gestion des Produits : 
  _Ajout, modification et suppression de médicaments.
  
  _Chaque produit est défini par un code, une désignation, un prix, une quantité en stock, une catégorie, et une date de péremption.
  
  _Les produits sont stockés dans un fichier binaire PRODUCTS.dat.

-Gestion des Catégories
  _Création et gestion de catégories (ex. : Antibiotiques, Vitamines).
  
  _ID auto-incrémenté, libellé clair.
  
  _Stockage dans CATEGORIES.dat.

- Gestion des Utilisateurs
  
  _Deux rôles sont définis :
  
    *Administrateur : gère les produits, les catégories et les comptes utilisateurs.
    
    *Pharmacien : effectue les ventes et consulte le stock.
  
  _Connexion sécurisée avec identifiants, changement de mot de passe obligatoire à la première connexion.
  
  _Données stockées dans USERS.dat.

- Gestion des Ventes

  _Chaque vente génère un identifiant unique horodaté (AAAAMMDDHHmmSS).
  
  _Mise à jour automatique du stock.
  
  _Génération d’une facture texte sauvegardée dans le dossier /BILLS/.

- Rapports Journaliers

  _Un fichier ETAT_AAAAMMDD.txt est généré chaque jour.
  
  _Contenu : total des ventes, nombre de médicaments vendus, alertes de stock critique.

-Interface & Expérience Utilisateur
  Interface console améliorée avec :
    
    *En-têtes stylisés en ASCII.
    
    *Menus interactifs avec couleurs.
    
    *Tableaux bien alignés pour l’affichage.
    
    *Messages animés (succès, erreurs, confirmations).
    
    *Système de validation avant toute suppression.

-Compilation et Exécution

  1- Compiler les fichiers source C avec gcc ou tout autre compilateur.
  
  2- Exécuter l’application dans le terminal.
  
  3- Naviguer à travers les menus pour utiliser le système.

