//
// Created by CAMFI on 01/11/2025.
//

#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H

#include "books.h"
#include "users.h"
#include "library.h"

int chargerLivres(Book tabBooks[], int max);
int sauvegarderLivres(Book tabBooks[], int nb);

int chargerUtilisateurs(User tabUsers[], int max);
int sauvegarderUtilisateurs(User tabUsers[], int nb);

int chargerEmprunts(Loan tabLoans[], int max);
int sauvegarderEmprunts(Loan tabLoans[], int nb);

#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H