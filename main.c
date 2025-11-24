
#include "library.h"
#include "books.h"
#include "stockage.h"
#include "users.h"

#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_LOANS 100

// Menu administrateur
void adminMenu(Book books[], int *nbBooks, User users[], int *nbUsers, Loan loans[], int *nbLoans) {
    int choice;

    do {
        displayAllBooks(books, *nbBooks);

        printf("\n===== MENU ADMIN =====\n");
        printf("1. Ajouter un livre\n");
        printf("2. Rechercher / Modifier / Supprimer un livre\n");
        printf("3. Afficher la liste des utilisateurs\n");
        printf("4. Ajouter / Modifier / supprimer un utilisateur\n");
        printf("5. Emprunts en retard\n");
        printf("0. Deconnexion\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                getchar();
                addBook(books, nbBooks);
                break;

            case 2:
                getchar();
                searchBook(books, *nbBooks, 0, loans, nbLoans, users, *nbUsers,-1);
                break;

            case 3:
                getchar();
                afficherUtilisateurs(users, *nbUsers);
                break;

            case 4 :
                getchar();
                searchUtilisateur(users, nbUsers);

            case 5: {
                // nbLoans est un int* dans ce menu -> il faut le déréférencer
                mettreAJourRetards(loans, *nbLoans, NULL);
                printf("=== Emprunts en retard ===\n");
                for (int i = 0; i < *nbLoans; i++) {
                    if (loans[i].late == 1 && loans[i].dateReturn[0] == '\0') {
                        printf("#%d | Livre %d | Utilisateur %d | depuis %s\n",
                               loans[i].idLoan, loans[i].idBook, loans[i].idUser, loans[i].dateLoan);
                    }
                }
                break;
            }

            case 0:
                printf("Deconnexion...\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 0);
}

// Menu utilisateur
void userMenu(Book books[], int nbBooks, User users[], int *nbUsers, int monIndex, Loan loans[], int *nbLoans) {
    int choice;

    do {
        displayAllBooks(books, nbBooks);

        printf("\n===== MENU UTILISATEUR =====\n");
        printf("1. Rechercher un livre\n");
        printf("2. Modifier mon compte\n");
        printf("3. Supprimer mon compte\n");
        printf("4. Emprunter un livre\n");
        printf("5. Rendre un livre\n");
        printf("6. Mes emprunts et retards\n");
        printf("0. Deconnexion\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchBook(books, nbBooks, 1, loans, nbLoans, users, *nbUsers,users[monIndex].id);  // mode utilisateur
                break;

            case 2:
                modifierMonCompte(users, monIndex);
                break;

            case 3:
                supprimerMonCompte(users, nbUsers, &monIndex);
                break;

            case 4: {
                int idBook;
                printf("ID livre a emprunter: ");
                scanf("%d", &idBook);
                // nbLoans est un int* dans ce menu -> on passe nbLoans tel quel (int*)
                int code = enregistrerEmprunt(loans, nbLoans, books, nbBooks, users, *nbUsers, idBook, users[monIndex].id, NULL);
                if (code == 0) printf("Emprunt enregistre.\n");
                else if (code == -2) printf("Livre déjà emprunte.\n");
                else if (code == -3) printf("Limite de prets atteinte (max 3).\n");
                else printf("Erreur.\n");
                break;
            }

            case 5: {
                int idBook;
                printf("ID livre a rendre: ");
                scanf("%d", &idBook);
                // enregistrerRetour attend un int nbLoans -> passer *nbLoans
                int code = enregistrerRetour(loans, *nbLoans, books, nbBooks, users, *nbUsers, idBook, NULL);
                if (code == 0) printf("Retour enregistre.\n");
                else printf("Erreur: pas d'emprunt actif pour ce livre.\n");
                break;
            }

            case 6: {
                // Mise à jour des retards du jour
                mettreAJourRetards(loans, *nbLoans, NULL);
                printf("=== Mes emprunts ===\n");
                for (int i = 0; i < *nbLoans; i++) {
                    if (loans[i].idUser == users[monIndex].id) {
                        printf("#%d | Livre %d | du %s | retour: %s | %s\n",
                               loans[i].idLoan, loans[i].idBook, loans[i].dateLoan,
                               loans[i].dateReturn[0] ? loans[i].dateReturn : "(en cours)",
                               loans[i].late ? "EN RETARD" : "OK");
                    }
                }
                break;
            }

            case 0:
                printf("Deconnexion...\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choice != 0 && monIndex != -1);
}

int main() {
    Book books[MAX_BOOKS];
    User users[MAX_USERS];
    Loan loans[MAX_LOANS];

    int nbBooks = 0;
    int nbUsers = 0;
    int nbLoans = 0;

    int mode;

    nbUsers = chargerUtilisateurs(users, MAX_USERS);
    nbBooks = chargerLivres(books, MAX_BOOKS);
    nbLoans = chargerEmprunts(loans, MAX_LOANS);

    int choix;
    int monIndex = -1;

    while (1) {
        printf("\n===== Bibliotheque Numerique =====\n");
        printf("1. Je suis deja utilisateur\n");
        printf("2. Creer un compte\n");
        printf("3. Connexion administrateur\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 0) break;

        switch (choix) {
            case 1:
                monIndex = connexionUtilisateur(users, nbUsers);
                if (monIndex == -1) {
                    char c;
                    printf("Utilisateur introuvable. Voulez-vous creer un compte ? (o/n) : ");
                    scanf(" %c", &c);
                    if (c == 'o' || c == 'O')
                        monIndex = creerCompte(users, &nbUsers);
                    else
                        continue;
                }
                // Passer loans et &nbLoans aux menus
                userMenu(books, nbBooks, users, &nbUsers, monIndex, loans, &nbLoans);
                break;

            case 2:
                monIndex = creerCompte(users, &nbUsers);
                printf("Compte cree, vous pouvez maintenant vous connecter.\n");
                break;

            case 3:
                if (connexionAdmin())
                    // Passer loans et &nbLoans aux menus
                    adminMenu(books, &nbBooks, users, &nbUsers, loans, &nbLoans);
                else
                    printf("Identifiants incorrects.\n");
                break;

            default:
                printf(" Choix invalide.\n");
        }
    }

    sauvegarderLivres(books, nbBooks);
    sauvegarderUtilisateurs(users, nbUsers);
    sauvegarderEmprunts(loans, nbLoans);

    printf("\nMerci, a bientot ! \n");
    return 0;
}