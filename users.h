
#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_USERS_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_USERS_H

#define MAX_EMPRUNTS_PAR_USER 3

typedef struct {
    int id;                 // Identifiant unique de l’utilisateur
    char name[20];          // Nom
    char surname[20];       // Prénom
    char mail[70];         // Adresse e-mail
    char idStudent[20];     // Identifiant étudiant
    int nbStudentLoans;     // Nombre de livres empruntés
    int livresEmpruntes[MAX_EMPRUNTS_PAR_USER];
    /*time_t datesEmprunt[MAX_EMPRUNTS_PAR_USER];*/
} User;

// --- Fonctions pour l’administrateur ---
void ajouterUtilisateur(User *users, int *nbUsers);
void searchUtilisateur(User users[], int *nbUsers);
void afficherUtilisateurs(User *users, int nbUsers);
void modifierUtilisateur(User *users, int nbUsers);
void supprimerUtilisateur(User *users, int *nbUsers);

// --- Fonctions pour l’utilisateur simple ---
int creerCompte(User *users, int *nbUsers);
int connexionUtilisateur(User *users, int nbUsers);
void modifierMonCompte(User *users, int monIndex);
void supprimerMonCompte(User *users, int *nbUsers, int *monIndex);

// --- Authentification admin ---
int connexionAdmin();
#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_USERS_H
