#ifndef RAPPORTS_H_INCLUDED
#define RAPPORTS_H_INCLUDED

// G�n�rer le rapport journalier des ventes
void genererRapportJournalier();

// Compter le nombre de ventes du jour
int compterVentesAujourdHui(const char *date);

// Calculer la somme des ventes du jour
float totalVentesAujourdHui(const char *date);

// �crire les alertes de stock dans un fichier
void ecrireAlertesStock(FILE);

#endif
