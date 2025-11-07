
/* Format par ligne :
   id;title;author;category;isbn;year;status;nbLoans
*/


#include "stockage.h"

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


// Books


int chargerLivres(Book books[], int max) {
    FILE *f = fopen(BOOKS_FILE, "r");
    if (!f) return 0;

    char line[512];
    int count = 0;

    while (count < max && fgets(line, sizeof line, f)) {
        rstrip(line);
        if (line[0] == '\0') continue; // lignes vides

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



// Users


int chargerUtilisateurs(User users[], int max) {
    FILE *f = fopen(USERS_FILE, "r");
    if (!f) return 0;

    char line[512];
    int count = 0;

    while (count < max && fgets(line, sizeof line, f)) {
        rstrip(line);
        if (line[0] == '\0') continue;

        User u = (User){0};
        char *tok;

        tok = strtok(line, ";"); if (!tok) continue; u.id = atoi(tok);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(u.name,     tok, sizeof u.name     - 1);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(u.surname,  tok, sizeof u.surname  - 1);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(u.mail,     tok, sizeof u.mail     - 1);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(u.idStudent,tok, sizeof u.idStudent- 1);
        tok = strtok(NULL, ";"); if (!tok) continue; u.nbStudentLoans = atoi(tok);

        users[count++] = u;
    }

    fclose(f);
    return count;
}

int sauvegarderUtilisateurs(User users[], int nb) {
    FILE *f = fopen(USERS_FILE, "w");
    if (!f) { perror("sauvegarderUtilisateurs fopen"); return -1; }

    for (int i = 0; i < nb; i++) {
        fprintf(f, "%d;%s;%s;%s;%s;%d\n",
                users[i].id,
                users[i].name,
                users[i].surname,
                users[i].mail,
                users[i].idStudent,
                users[i].nbStudentLoans);
    }

    fclose(f);
    return nb;
}


// Loans

int chargerEmprunts(Loan loans[], int max) {
    FILE *f = fopen(LOANS_FILE, "r");
    if (!f) return 0;

    char line[256];
    int count = 0;

    while (count < max && fgets(line, sizeof line, f)) {
        rstrip(line);
        if (line[0] == '\0') continue;

        Loan L = (Loan){0};
        char *tok;

        tok = strtok(line, ";"); if (!tok) continue; L.idLoan = atoi(tok);
        tok = strtok(NULL, ";"); if (!tok) continue; L.idBook = atoi(tok);
        tok = strtok(NULL, ";"); if (!tok) continue; L.idUser = atoi(tok);
        tok = strtok(NULL, ";"); if (!tok) continue; strncpy(L.dateLoan, tok, sizeof L.dateLoan - 1);
        tok = strtok(NULL, ";");                     /* peut être vide */
        if (!tok) tok = "";
        strncpy(L.dateReturn, tok, sizeof L.dateReturn - 1);
        tok = strtok(NULL, ";"); if (!tok) continue; L.late = atoi(tok);

        loans[count++] = L;
    }

    fclose(f);
    return count;
}

int sauvegarderEmprunts(Loan loans[], int nb) {
    FILE *f = fopen(LOANS_FILE, "w");
    if (!f) { perror("sauvegarderEmprunts fopen"); return -1; }

    for (int i = 0; i < nb; i++) {
        /* dateReturn peut être "" si pas encore rendu */
        fprintf(f, "%d;%d;%d;%s;%s;%d\n",
                loans[i].idLoan,
                loans[i].idBook,
                loans[i].idUser,
                loans[i].dateLoan,
                loans[i].dateReturn,
                loans[i].late);
    }

    fclose(f);
    return nb;
}