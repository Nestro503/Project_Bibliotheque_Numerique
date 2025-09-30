#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_LIBRARY_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_LIBRARY_H

typedef struct {
    int id;                 // Identifiant unique de l’utilisateur
    char name[50];          // Nom
    char surname[50];       // Prénom
    char mail[100];         // Adresse e-mail
    char idStudent[20];     // Identifiant étudiant
    int nbStudentLoans;     // Nombre de livres actuellement empruntés
} User;


typedef struct {
    int idLoan;          // Identifiant unique de l’emprunt
    int idBook;            // Référence à l’ID du livre
    int idUser;      // Référence à l’ID de l’utilisateur
    char dateLoan[11];   // Date format JJ/MM/AAAA
    char dateReturn[11];    // Date effective de retour (vide si pas encore rendu)
    int late;           // 1 si retard, 0 sinon
} Loan;



#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_LIBRARY_H
