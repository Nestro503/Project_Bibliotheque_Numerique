
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

static int parseDate(const char *s, struct tm *out) {
    if (!s || strlen(s) < 8) return -1;
    int d, m, y;
    if (sscanf(s, "%d/%d/%d", &d, &m, &y) != 3) return -1;
    memset(out, 0, sizeof(*out));
    out->tm_mday = d;
    out->tm_mon  = m - 1;
    out->tm_year = y - 1900;
    out->tm_isdst = -1;
    // mktime normalise la date
    if (mktime(out) == (time_t)-1) return -1;
    return 0;
}

static int daysDiff(const char *d1, const char *d2) {
    struct tm t1, t2;
    if (parseDate(d1, &t1) != 0 || parseDate(d2, &t2) != 0) return 0;
    time_t a = mktime(&t1), b = mktime(&t2);
    double diff = difftime(b, a) / (60*60*24);
    if (diff < 0) diff = -diff;
    return (int)(diff + 0.5);
}

static void todayStr(char buf[11]) {
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    snprintf(buf, 11, "%02d/%02d/%04d", lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
}

// === Recherches ===
int trouverLivreParId(Book books[], int nbBooks, int idBook) {
    for (int i = 0; i < nbBooks; i++) if (books[i].id == idBook) return i;
    return -1;
}

int trouverUtilisateurParId(User users[], int nbUsers, int idUser) {
    for (int i = 0; i < nbUsers; i++) if (users[i].id == idUser) return i;
    return -1;
}

int trouverEmpruntActif(Loan loans[], int nbLoans, int idBook) {
    for (int i = 0; i < nbLoans; i++) {
        if (loans[i].idBook == idBook && loans[i].dateReturn[0] == '\0') return i;
    }
    return -1;
}

int verifierLimitePrets(User users[], int idxUser) {
    if (idxUser < 0) return -1;
    if (users[idxUser].nbStudentLoans >= MAX_EMPRUNTS_PAR_USER) return -1;
    return 0;
}

// === Emprunter ===
int enregistrerEmprunt(Loan loans[], int *nbLoans, Book books[], int nbBooks, User users[], int nbUsers, int idBook, int idUser, const char *dateLoan){
    int ib = trouverLivreParId(books, nbBooks, idBook);
    int iu = trouverUtilisateurParId(users, nbUsers, idUser);
    if (ib < 0 || iu < 0) return -1; // introuvable

    if (books[ib].status != 0) return -2; // déjà emprunté
    if (verifierLimitePrets(users, iu) != 0) return -3; // limite atteinte

    // Date par défaut = aujourd'hui si NULL ou vide
    char dBuf[11];
    const char *useDate = dateLoan && dateLoan[0] ? dateLoan : (todayStr(dBuf), dBuf);

    // Crée l’emprunt
    Loan L = {0};
    int maxId = 0;
    for (int i = 0; i < *nbLoans; i++) if (loans[i].idLoan > maxId) maxId = loans[i].idLoan;
    L.idLoan = maxId + 1;
    L.idBook = idBook;
    L.idUser = idUser;
    strncpy(L.dateLoan, useDate, sizeof L.dateLoan - 1);
    L.dateReturn[0] = '\0';
    L.late = 0;

    loans[*nbLoans] = L;
    (*nbLoans)++;

    // MàJ livre & utilisateur
    books[ib].status = 0;
    books[ib].nbLoans += 1;
    users[iu].nbStudentLoans += 1;

    return 0;
}

// === Retour ===
int enregistrerRetour(
        Loan loans[], int nbLoans,
        Book books[], int nbBooks,
        User users[], int nbUsers,
        int idBook,
        const char *dateReturn
) {
    int ie = trouverEmpruntActif(loans, nbLoans, idBook);
    if (ie < 0) return -1; // pas d'emprunt actif pour ce livre

    int ib = trouverLivreParId(books, nbBooks, idBook);
    if (ib < 0) return -2;

    int iu = trouverUtilisateurParId(users, nbUsers, loans[ie].idUser);
    if (iu < 0) return -3;

    // Date de retour
    char dBuf[11];
    const char *useDate = dateReturn && dateReturn[0] ? dateReturn : (todayStr(dBuf), dBuf);
    strncpy(loans[ie].dateReturn, useDate, sizeof loans[ie].dateReturn - 1);

    // Retard > 15 jours ?
    int diff = daysDiff(loans[ie].dateLoan, useDate);
    loans[ie].late = (diff > 15) ? 1 : 0;

    // MàJ livre & utilisateur
    books[ib].status = 1;
    if (users[iu].nbStudentLoans > 0) users[iu].nbStudentLoans -= 1;

    return 0;
}

// === Détection de retards (sur emprunts actifs) ===
int mettreAJourRetards(Loan loans[], int nbLoans, const char *todayDate) {
    char dBuf[11];
    const char *ref = (todayDate && todayDate[0]) ? todayDate : (todayStr(dBuf), dBuf);
    int nb = 0;
    for (int i = 0; i < nbLoans; i++) {
        if (loans[i].dateReturn[0] == '\0') {
            int diff = daysDiff(loans[i].dateLoan, ref);
            if (diff > 15) { loans[i].late = 1; nb++; }
        }
    }
    return nb;
}