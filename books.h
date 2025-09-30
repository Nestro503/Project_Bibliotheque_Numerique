#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_BOOKS_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_BOOKS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char title[100];
    char author[100];
    char category[50];
    char isbn[20];
    int year;
    int status;             // 1 = available, 0 = borrowed
    int nbLoans;
} Book;

// Function prototypes
void addBook(Book books[], int *nbBooks);
void displayBooks(Book books[], int nbBooks);
Book* searchBookByTitle(Book books[], int nbBooks, const char* title);
Book* searchBookByISBN(Book books[], int nbBooks, const char* isbn);
void deleteBook(Book books[], int *nbBooks, int id);
void modifyBook(Book books[], int nbBooks, int id);
void sortBooks(Book books[], int nbBooks, int criterion); // 0 = by title, 1 = by year

#endif //PROJECT_BIBLIOTHEQUE_NUMERIQUE_BOOKS_H
