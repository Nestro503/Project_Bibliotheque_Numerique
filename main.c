#include "library.c"
#include "library.h"
#include "books.h"
#include "books.c"

#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

void adminMenu(Book books[], int *nbBooks) {
    int choice;
    char searchTitle[100];

    while (1) {
        displayAllBooks(books, *nbBooks);

        printf("=== ADMIN MENU ===\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("0. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0) break;

        if (choice == 1) {
            addBook(books, nbBooks);
        }
        else if (choice == 2) {
            printf("Enter title: ");
            fgets(searchTitle, 100, stdin);
            searchTitle[strcspn(searchTitle, "\n")] = '\0';

            Book *b = searchBookByTitle(books, *nbBooks, searchTitle);

            if (b) {
                printf("\nBook found: %s by %s\n", b->title, b->author);
                printf("1. Modify\n2. Delete\n0. Cancel\n");
                int action;
                scanf("%d", &action);
                getchar();

                if (action == 1) modifyBook(books, *nbBooks, b->id);
                else if (action == 2) deleteBook(books, nbBooks, b->id);
            } else {
                printf("Not found.\n");
            }
        }
    }
}

void userMenu(Book books[], int nbBooks) {
    int choice;
    char searchTitle[100];

    while (1) {
        displayAllBooks(books, nbBooks);

        printf("=== USER MENU ===\n");
        printf("1. Search Book\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0) break;

        if (choice == 1) {
            printf("Enter title: ");
            fgets(searchTitle, 100, stdin);
            searchTitle[strcspn(searchTitle, "\n")] = '\0';

            Book *b = searchBookByTitle(books, nbBooks, searchTitle);

            if (b) {
                printf("\n%s — %s (%d)\n", b->title, b->author, b->year);
            } else {
                printf("Not found.\n");
            }
        }
    }
}

int main() {
    Book books[MAX_BOOKS];
    int nbBooks = 0;
    int mode;

    printf("=== Login ===\n0 = Admin\n1 = User\nChoice: ");
    scanf("%d", &mode);
    getchar();

    if (mode == 0) adminMenu(books, &nbBooks);
    else userMenu(books, nbBooks);

    printf("\nBye!\n");
    return 0;
}
