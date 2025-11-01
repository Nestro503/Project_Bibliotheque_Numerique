//
// Created by CAMFI on 01/11/2025.
//


/* Format par ligne :
   id;title;author;category;isbn;year;status;nbLoans
*/


#include "stockage.h"
#include <stdio.h>
#include <string.h>

#define BOOKS_FILE "txt/books.txt"
#define USERS_FILE "txt/users.txt"
#define LOANS_FILE "txt/loans.txt"


/* mise en forme */
static void rstrip(char *s){
    size_t n = strlen(s);
    while (n>0 && (s[n-1]=='\n' || s[n-1]=='\r' || s[n-1]==' ' || s[n-1]=='\t')) {
        s[--n] = '\0';
    }
}



int chargerLivres(Book books[], int max) {
    FILE *f = fopen(BOOKS_FILE, "r");
    if (!f) return 0; // pas bloquant si le fichier n'existe pas encore

    char line[512];
    int count = 0;

    while (count < max && fgets(line, sizeof line, f)) {
        rstrip(line);
        if (line[0] == '\0') continue; // ignore lignes vides

        Book b = {0};
        char *tok;

        tok = strtok(line, ";"); if (!tok) continue; b.id = atoi(tok);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(b.title, tok, sizeof b.title - 1);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(b.author, tok, sizeof b.author - 1);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(b.category, tok, sizeof b.category - 1);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(b.isbn, tok, sizeof b.isbn - 1);
        tok = strtok(NULL, ";"); if (!tok) continue; b.year   = atoi(tok);
        tok = strtok(NULL, ";"); if (!tok) continue; b.status = atoi(tok);
        tok = strtok(NULL, ";"); if (!tok) continue; b.nbLoans = atoi(tok);

        books[count++] = b;
    }

    fclose(f);
    return count;
}

int sauvegarderLivres(Book books[], int nb) {
    FILE *f = fopen(BOOKS_FILE, "w");
    if (!f) {
        perror("sauvegarderLivres fopen");
        return -1;
    }

    for (int i = 0; i < nb; i++) {
        /* ISBN peut contenir des '-' : OK, séparateur = ';' */
        fprintf(f, "%d;%s;%s;%s;%s;%d;%d;%d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].category,
                books[i].isbn,
                books[i].year,
                books[i].status,
                books[i].nbLoans);
    }

    fclose(f);
    return nb;
}