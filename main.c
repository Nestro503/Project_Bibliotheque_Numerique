#include "library.c"
#include "library.h"
#include "books.h"
#include "books.c"

#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

int main() {
    Book books[MAX_BOOKS];
    int nbBooks = 0;
    int choice;

    do {
        printf("\n=== Library Management ===\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book by Title\n");
        printf("4. Search Book by ISBN\n");
        printf("5. Modify Book\n");
        printf("6. Delete Book\n");
        printf("7. Sort Books by Title\n");
        printf("8. Sort Books by Year\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Remove leftover newline

        switch(choice) {
            case 1:
                addBook(books, &nbBooks);
                break;
            case 2:
                displayBooks(books, nbBooks);
                break;
            case 3: {
                char title[100];
                printf("Enter title to search: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';
                Book* b = searchBookByTitle(books, nbBooks, title);
                if (b) printf("Found: ID %d | %s by %s\n", b->id, b->title, b->author);
                else printf("Book not found.\n");
                break;
            }
            case 4: {
                char isbn[20];
                printf("Enter ISBN to search: ");
                fgets(isbn, 20, stdin);
                isbn[strcspn(isbn, "\n")] = '\0';
                Book* b = searchBookByISBN(books, nbBooks, isbn);
                if (b) printf("Found: ID %d | %s by %s\n", b->id, b->title, b->author);
                else printf("Book not found.\n");
                break;
            }
            case 5: {
                int id;
                printf("Enter book ID to modify: ");
                scanf("%d", &id);
                getchar();
                modifyBook(books, nbBooks, id);
                break;
            }
            case 6: {
                int id;
                printf("Enter book ID to delete: ");
                scanf("%d", &id);
                getchar();
                deleteBook(books, &nbBooks, id);
                break;
            }
            case 7:
                sortBooks(books, nbBooks, 0);
                break;
            case 8:
                sortBooks(books, nbBooks, 1);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }

    } while (choice != 0);

    return 0;
}