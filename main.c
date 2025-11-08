#include <stdio.h>
#include <string.h>

#include "library.h"
#include "books.h"
#include "stockage.h"
#include "users.h"

#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_LOANS 100

// Menu administrateur
void adminMenu(Book books[], int *nbBooks, User users[], int *nbUsers) {
    int choice;

    do {
        printf("\n===== MENU ADMIN =====\n");
        printf("1. Ajouter un livre\n");
        printf("2. Rechercher / Modifier / Supprimer un livre\n");
        printf("3. Afficher la liste des utilisateurs\n");
        printf("4. Ajouter un utilisateur\n");
        printf("5. Modifier un utilisateur\n");
        printf("6. Supprimer un utilisateur\n");
        printf("0. Deconnexion\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, nbBooks);
                break;

            case 2:
                searchBook(books, *nbBooks, 0);
                break;

            case 3:
                afficherUtilisateurs(users, *nbUsers);
                break;

            case 4:
                ajouterUtilisateur(users, nbUsers);
                break;

            case 5:
                modifierUtilisateur(users, *nbUsers);
                break;

            case 6:
                supprimerUtilisateur(users, nbUsers);
                break;

            case 0:
                printf("Deconnexion...\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 0);
}



//Menu utilisateur
void userMenu(Book books[], int nbBooks, User users[], int *nbUsers, int monIndex) {
    int choice;

    do {
        printf("\n===== MENU UTILISATEUR =====\n");
        printf("1. Rechercher un livre\n");
        printf("2. Modifier mon compte\n");
        printf("3. Supprimer mon compte\n");
        printf("0. Deconnexion\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchBook(books, nbBooks, 1);  // mode utilisateur
                break;

            case 2:
                modifierMonCompte(users, monIndex);
                break;

            case 3:
                supprimerMonCompte(users, nbUsers, &monIndex);
                break;

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
                userMenu(books, nbBooks, users, &nbUsers, monIndex);
                break;

            case 2:
                monIndex = creerCompte(users, &nbUsers);
                printf("Compte cree, vous pouvez maintenant vous connecter.\n");
                break;

            case 3:
                if (connexionAdmin())
                    adminMenu(books, &nbBooks, users, &nbUsers);
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
