#include "books.h"

// Helper function to generate a unique ID
int generateBookID(Book books[], int nbBooks) {
    int maxID = 0;
    for (int i = 0; i < nbBooks; i++) {
        if (books[i].id > maxID) maxID = books[i].id;
    }
    return maxID + 1;
}

// Add a new book
void addBook(Book books[], int *nbBooks) {
    Book newBook;
    newBook.id = generateBookID(books, *nbBooks);

    printf("Enter title: ");
    fgets(newBook.title, 100, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Remove newline

    printf("Enter author: ");
    fgets(newBook.author, 100, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter category: ");
    fgets(newBook.category, 50, stdin);
    newBook.category[strcspn(newBook.category, "\n")] = '\0';

    printf("Enter ISBN: ");
    fgets(newBook.isbn, 20, stdin);
    newBook.isbn[strcspn(newBook.isbn, "\n")] = '\0';

    printf("Enter year: ");
    scanf("%d", &newBook.year);
    getchar(); // remove leftover newline

    newBook.status = 1; // available
    newBook.nbLoans = 0;

    books[*nbBooks] = newBook;
    (*nbBooks)++;

    printf("Book added successfully! ID = %d\n", newBook.id);
}

// Display all books
void displayBooks(Book books[], int nbBooks) {
    if (nbBooks == 0) {
        printf("No books available.\n");
        return;
    }
    printf("List of books:\n");
    for (int i = 0; i < nbBooks; i++) {
        printf("ID: %d | Title: %s | Author: %s | Year: %d | Status: %s\n",
               books[i].id, books[i].title, books[i].author,
               books[i].year, books[i].status ? "Available" : "Borrowed");
    }
}

// Search book by title
Book* searchBookByTitle(Book books[], int nbBooks, const char* title) {
    for (int i = 0; i < nbBooks; i++) {
        if (strcmp(books[i].title, title) == 0) {
            return &books[i];
        }
    }
    return NULL; // not found
}

// Search book by ISBN
Book* searchBookByISBN(Book books[], int nbBooks, const char* isbn) {
    for (int i = 0; i < nbBooks; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            return &books[i];
        }
    }
    return NULL; // not found
}

// Delete a book by ID
void deleteBook(Book books[], int *nbBooks, int id) {
    int found = 0;
    for (int i = 0; i < *nbBooks; i++) {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < *nbBooks - 1; j++) {
                books[j] = books[j+1];
            }
            (*nbBooks)--;
            printf("Book with ID %d deleted.\n", id);
            break;
        }
    }
    if (!found) printf("Book with ID %d not found.\n", id);
}

// Modify a book by ID
void modifyBook(Book books[], int nbBooks, int id) {
    Book* b = NULL;
    for (int i = 0; i < nbBooks; i++) {
        if (books[i].id == id) {
            b = &books[i];
            break;
        }
    }
    if (!b) {
        printf("Book not found.\n");
        return;
    }

    printf("Enter new title (current: %s): ", b->title);
    fgets(b->title, 100, stdin);
    b->title[strcspn(b->title, "\n")] = '\0';

    printf("Enter new author (current: %s): ", b->author);
    fgets(b->author, 100, stdin);
    b->author[strcspn(b->author, "\n")] = '\0';

    printf("Enter new category (current: %s): ", b->category);
    fgets(b->category, 50, stdin);
    b->category[strcspn(b->category, "\n")] = '\0';

    printf("Enter new ISBN (current: %s): ", b->isbn);
    fgets(b->isbn, 20, stdin);
    b->isbn[strcspn(b->isbn, "\n")] = '\0';

    printf("Enter new year (current: %d): ", b->year);
    scanf("%d", &b->year);
    getchar();

    printf("Book modified successfully.\n");
}

// Sort books: criterion 0 = title, 1 = year
void sortBooks(Book books[], int nbBooks, int criterion) {
    for (int i = 0; i < nbBooks - 1; i++) {
        for (int j = i + 1; j < nbBooks; j++) {
            int swap = 0;
            if (criterion == 0 && strcmp(books[i].title, books[j].title) > 0) swap = 1;
            if (criterion == 1 && books[i].year > books[j].year) swap = 1;
            if (swap) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    printf("Books sorted successfully.\n");
}
