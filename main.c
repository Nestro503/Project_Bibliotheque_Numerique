#include "library.h"
#include "books.h"
#include "stockage.h"


#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_LOANS 100


// 0 = admin, 1 = user
void adminMenu(Book books[], int *nbBooks) {
    int choice;

    while (1) {
        displayAllBooks(books, *nbBooks);

        printf("=== MENU ADMIN ===\n");
        printf("1. Ajouter un livre\n");
        printf("2. Rechercher un livre\n");
        printf("0. Deconnexion\n");
        printf("Choix : ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0) {
            printf("Deconnexion...\n");
            break;
        }

        switch (choice) {
            case 1:
                addBook(books, nbBooks);
                break;

            case 2:
                searchBook(books, *nbBooks, 0); // mode admin
                break;

            default:
                printf("Option invalide.\n");
        }
    }
}

void userMenu(Book books[], int nbBooks) {
    int choice;

    while (1) {
        displayAllBooks(books, nbBooks);

        printf("=== MENU UTILISATEUR ===\n");
        printf("1. Rechercher un livre\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0) {
            printf("Deconnexion...\n");
            break;
        }

        switch (choice) {
            case 1:
                searchBook(books, nbBooks, 1); // mode user
                break;

            default:
                printf("Option invalide.\n");
        }
    }
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

    printf("=== Login ===\n");
    printf("0 = Admin\n1 = Utilisateur\n");
    printf("Choix : ");
    scanf("%d", &mode);
    getchar();

    if (mode == 0) adminMenu(books, &nbBooks);
    else userMenu(books, nbBooks);


    sauvegarderLivres(books, nbBooks);
    sauvegarderUtilisateurs(users, nbUsers);
    sauvegarderEmprunts(loans, nbLoans);



    printf("\nMerci, a bientot ! \n");
    return 0;
}
