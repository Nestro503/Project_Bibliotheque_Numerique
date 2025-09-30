
#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_USERS_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_USERS_H

typedef struct {
    int id;                 // Identifiant unique de l’utilisateur
    char name[50];          // Nom
    char surname[50];       // Prénom
    char mail[100];         // Adresse e-mail
    char idStudent[20];     // Identifiant étudiant
    int nbStudentLoans;     // Nombre de livres actuellement empruntés
} User;


#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_USERS_H
