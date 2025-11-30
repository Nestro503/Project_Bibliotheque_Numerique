#ifndef PROJECT_BIBLIOTHEQUE_NUMERIQUE_BOOKS_H
#define PROJECT_BIBLIOTHEQUE_NUMERIQUE_BOOKS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "users.h"

typedef struct {
    int id;
    char title[100];
    char author[100];
    char category[50];
    char isbn[20];
    int year;
    int status;
    int nbLoans;
} Book;


// Function prototypes
void addBook(Book books[], int *nbBooks);
int generateBookID(Book books[], int nbBooks);

void displayAllBooks(Book books[], int nbBooks);

Book* searchBook(Book books[], int nbBooks, int mode, Loan loans[], int *nbLoans, User users[], int nbUsers, int idUser);
void deleteBook(Book books[], int *nbBooks, int id);
void modifyBook(Book books[], int nbBooks, int id);


#endif
