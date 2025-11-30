
#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H

#include "books.h"
#include "users.h"

int chargerLivres(Book books[], int max);
int sauvegarderLivres(Book books[], int nb);

int chargerUtilisateurs(User users[], int max);
int sauvegarderUtilisateurs(User users[], int nb);

int chargerEmprunts(Loan loans[], int max);
int sauvegarderEmprunts(Loan loans[], int nb);

// === Emprunts & retards (ajouts) ===
int trouverLivreParId(Book books[], int nbBooks, int idBook);
int trouverUtilisateurParId(User users[], int nbUsers, int idUser);
int trouverEmpruntActif(Loan loans[], int nbLoans, int idBook);
int verifierLimitePrets(User users[], int idxUser); // 0 = OK, -1 = limite atteinte

int enregistrerEmprunt(
        Loan loans[], int *nbLoans,
        Book books[], int nbBooks,
        User users[], int nbUsers,
        int idBook, int idUser,
        const char *dateLoan // jj/mm/aaaa
);

int enregistrerRetour(
        Loan loans[], int nbLoans,
        Book books[], int nbBooks,
        User users[], int nbUsers,
        int idBook,
        const char *dateReturn // jj/mm/aaaa
);

// Met à jour late=1 pour les emprunts actifs dont dateLoan > 15 jours (vs todayDate)
int mettreAJourRetards(Loan loans[], int nbLoans, const char *todayDate);

#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_STOCKAGE_H