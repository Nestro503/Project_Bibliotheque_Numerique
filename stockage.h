
#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H

#include "books.h"
#include "users.h"
#include "library.h"

int chargerLivres(Book books[], int max);
int sauvegarderLivres(Book books[], int nb);

int chargerUtilisateurs(User users[], int max);
int sauvegarderUtilisateurs(User users[], int nb);

int chargerEmprunts(Loan loans[], int max);
int sauvegarderEmprunts(Loan loans[], int nb);

#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H