#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_BIBLIOTHEQUE_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_BIBLIOTHEQUE_H


typedef struct {
    int id;                 // Identifiant unique du livre (généré automatiquement)
    char title[100];        // Titre du livre
    char author[100];       // Auteur du livre
    char category[50];      // Catégorie (roman, science, etc.)
    char isbn[20];          // ISBN du livre
    int year;               // Année de publication
    int status;             // 1 = disponible, 0 = emprunté
    int nbLoans;            // Nombre total d’emprunts (utile pour les statistiques)
} Book;


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



#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_BIBLIOTHEQUE_H
