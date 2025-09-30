#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_LIBRARY_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_LIBRARY_H


typedef struct {
    int idLoan;          // Identifiant unique de l’emprunt
    int idBook;            // Référence à l’ID du livre
    int idUser;      // Référence à l’ID de l’utilisateur
    char dateLoan[11];   // Date format JJ/MM/AAAA
    char dateReturn[11];    // Date effective de retour (vide si pas encore rendu)
    int late;           // 1 si retard, 0 sinon
} Loan;



#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_LIBRARY_H
