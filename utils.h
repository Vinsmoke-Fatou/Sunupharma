#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

// Fonctions d'affichage color�
void afficherSucces(const char* message);
void afficherErreur(const char* message);
void afficherInfo(const char* message);

// Gestion des entr�es
void lireChaine(char *chaine, int taille);
//void viderBufferEntree();

// Utilitaires
void verifierFichier(FILE);
void obtenirDateActuelle(char *dateBuffer);
void Pause();
void viderBuffer(void);

#endif
