#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "books.h"      // contient Book + prototype searchBook
#include "stockage.h"   // pour enregistrerEmprunt / sauvegardes

// Génère un ID unique (max existant + 1)
int generateBookID(Book books[], int nbBooks) {
    int maxID = 0;
    for (int i = 0; i < nbBooks; i++) {
        if (books[i].id > maxID) maxID = books[i].id;
    }
    return maxID + 1;
}

int validateDate(char *date) {
    int j, m, a;

    if (sscanf(date, "%d/%d/%d", &j, &m, &a) != 3) return 0;

    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    int currentYear = now.tm_year + 1900;

    if (a < 1000 || a > currentYear + 1) return 0;
    if (m < 1 || m > 12) return 0;
    if (j < 1 || j > 31) return 0;

    // Mois avec 30 jours
    if ((m==4 || m==6 || m==9 || m==11) && j > 30) return 0;

    // Fevrier (pas check bissextile pour simplifier, ok pour projet)
    if (m == 2 && j > 28) return 0;

    return 1;
}

int validateISBN(char *isbn) {
    if (strlen(isbn) != 13) return 0;
    for (int i = 0; i < 13; i++) {
        if (!isdigit((unsigned char)isbn[i])) return 0;
    }
    return 1;
}

int validateCategory(char *cat) {
    const char *validCategories[] = {
            "roman", "bd", "manga", "biographie", "science", "fantasy", "histoire"
    };
    int size = (int)(sizeof(validCategories) / sizeof(validCategories[0]));

    for (int i = 0; i < size; i++) {
        if (strcmp(cat, validCategories[i]) == 0)
            return 1;
    }
    return 0;
}

// Ajoute un livre (status=1 disponible, nbLoans=0)
void addBook(Book books[], int *nbBooks) {
    Book newBook;
    newBook.id = generateBookID(books, *nbBooks);

    // Titre
    while (1) {
        printf("Titre (1-20 caracteres) : ");
        fgets(newBook.title, 100, stdin);
        newBook.title[strcspn(newBook.title, "\n")] = '\0';

        if (strlen(newBook.title) >= 1 && strlen(newBook.title) <= 20) break;
        printf("Erreur : le titre doit contenir 1 a 20 caracteres.\n\n");
    }

    // Auteur
    while (1) {
        printf("Auteur (1-20 caracteres) : ");
        fgets(newBook.author, 100, stdin);
        newBook.author[strcspn(newBook.author, "\n")] = '\0';

        if (strlen(newBook.author) >= 1 && strlen(newBook.author) <= 20) break;
        printf("Erreur : l'auteur doit contenir 1 a 20 caracteres.\n\n");
    }

    // Categorie
    while (1) {
        printf("Categorie, parmi les suivantes :\n");
        printf("   roman, bd, manga, science, fantasy, histoire, biographie\n");
        printf("Votre choix : ");
        fgets(newBook.category, 50, stdin);
        newBook.category[strcspn(newBook.category, "\n")] = '\0';

        if (validateCategory(newBook.category)) break;
        printf("Erreur : categorie invalide. Choisissez parmis la liste.\n\n");
    }

    // ISBN
    while (1) {
        printf("ISBN (13 chiffres) : ");
        fgets(newBook.isbn, 20, stdin);
        newBook.isbn[strcspn(newBook.isbn, "\n")] = '\0';

        if (validateISBN(newBook.isbn)) break;
        printf("Format ISBN invalide. Exemple : 9781234567890\n\n");
    }

    // Date (pour récupérer l'année)
    char date[20];
    while (1) {
        printf("Date (jj/mm/aaaa) : ");
        fgets(date, 20, stdin);
        date[strcspn(date, "\n")] = '\0';

        if (validateDate(date)) break;
        printf("Date invalide. Format attendu jj/mm/aaaa, ex : 25/11/2024\n\n");
    }

    // On recupère juste l'annee du champ date
    int j, m, a;
    sscanf(date, "%d/%d/%d", &j, &m, &a);
    newBook.year = a;

    newBook.status  = 0; // disponible
    newBook.nbLoans = 0; // aucun emprunt

    books[*nbBooks] = newBook;
    (*nbBooks)++;

    printf("\n Livre ajoute avec succes ! (ID %d)\n\n", newBook.id);
}

// Affiche tous les livres
void displayAllBooks(Book books[], int nbBooks) {

    if (nbBooks == 0) {
        printf("\nLa bibliotheque est vide.\n\n");
        return;
    }

    printf("\n==================== BIBLIOTHEQUE ====================\n\n");

    // Table headers
    printf("%-5s | %-25s | %-20s | %-18s | %-12s | %-10s | %-10s\n",
           "ID", "Titre", "Auteur", "ISBN", "Categorie", "Statut", "Emprunts");
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    // Books rows
    for (int i = 0; i < nbBooks; i++) {
        printf("%-5d | %-25s | %-20s | %-18s | %-12s | %-10s | %-10d\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].isbn,
               books[i].category,
               (books[i].status == 0) ? "Disponible" : "Emprunte",
               books[i].nbLoans);
    }

    printf("\n=======================================================\n\n");
}


Book* searchBook(Book books[], int nbBooks, int mode, Loan loans[], int *nbLoans,
                 User users[], int nbUsers,
                 int idUser) {
    // Vider le buffer avant fgets pour éviter les sauts
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    char title[100] = "";
    char author[100] = "";
    char isbn[20] = "";
    char category[50] = "";

    printf("\n=== Recherche multi-criteres ===\n");
    printf("Laisser vide si critere non utilise...\n");

    printf("ISBN : ");
    fgets(isbn, 20, stdin); isbn[strcspn(isbn, "\n")] = '\0';

    printf("  Titre : ");
    fgets(title, 100, stdin); title[strcspn(title, "\n")] = '\0';

    printf("    Auteur : ");
    fgets(author, 100, stdin); author[strcspn(author, "\n")] = '\0';

    printf("       Categorie : ");
    fgets(category, 50, stdin); category[strcspn(category, "\n")] = '\0';

    Book *found = NULL;
    int foundCount = 0;

    printf("\nResultats :\n");

    for (int i = 0; i < nbBooks; i++) {
        int match = 0;

        if ((strlen(title) == 0 || strcmp(books[i].title, title) == 0) &&
            (strlen(author) == 0 || strcmp(books[i].author, author) == 0) &&
            (strlen(isbn) == 0 || strcmp(books[i].isbn, isbn) == 0) &&
            (strlen(category) == 0 || strcmp(books[i].category, category) == 0)) {
            match = 1;
        }

        if (match) {
            printf("-----------------------------------------------\n");
            printf("ID : %d\nTitre : %s\nAuteur : %s\nISBN : %s\nCategorie : %s\nStatut : %s\nEmprunts : %d\n",
                   books[i].id, books[i].title, books[i].author, books[i].isbn,
                   books[i].category, (books[i].status == 1 ? "Disponible" : "Emprunte"),
                   books[i].nbLoans);

            found = &books[i];  // Dernier livre trouvé
            foundCount++;
        }
    }

    if (foundCount == 0) {
        printf("\nAucun livre trouve\n\n");
        return NULL;
    }

    printf("-----------------------------------------------\n");

    // Mode Admin : actions si un seul livre trouvé
    if (mode == 0 && foundCount == 1) {
        printf("\nActions possibles :\n");
        printf("1. Modifier le livre\n");
        printf("2. Supprimer le livre\n");
        printf("0. Retour\n");
        printf("Votre choix : ");

        int action;
        scanf("%d", &action);
        getchar();

        if (action == 1) modifyBook(books, nbBooks, found->id);
        else if (action == 2) deleteBook(books, &nbBooks, found->id);
        else printf("Retour au menu.\n");
    }
        // Mode Utilisateur : emprunt si livre disponible
    else if (mode == 1 && foundCount == 1) {
        if (found->status == 0) {
            printf("\nCe livre est disponible\n");
            printf("Souhaitez-vous l'emprunter ? (y/n) : ");
            char c; scanf(" %c", &c); getchar();

            if (c == 'y' || c == 'Y') {
                int code = enregistrerEmprunt(loans, nbLoans,
                                              books, nbBooks,
                                              users, nbUsers,
                                              found->id, idUser,
                                              NULL); // date du jour auto
                if (code == 0) {
                    printf("Emprunt enregistre.\n");
                    sauvegarderEmprunts(loans, *nbLoans);
                    sauvegarderLivres(books, nbBooks);
                    sauvegarderUtilisateurs(users, nbUsers);
                } else if (code == -2) {
                    printf("Livre deja emprunte.\n");
                } else if (code == -3) {
                    printf("Limite de prets atteinte (max 3).\n");
                } else {
                    printf("Erreur lors de l'emprunt.\n");
                }
            }
        } else {
            printf("\nCe livre est deja emprunte\n\n");
        }
    }

    return found;
}


// Modify book
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

    printf("Enter new title (%s): ", b->title);
    fgets(b->title, 100, stdin); b->title[strcspn(b->title, "\n")] = '\0';

    printf("Enter new author (%s): ", b->author);
    fgets(b->author, 100, stdin); b->author[strcspn(b->author, "\n")] = '\0';

    printf("Enter new category (%s): ", b->category);
    fgets(b->category, 50, stdin); b->category[strcspn(b->category, "\n")] = '\0';

    printf("Enter new ISBN (%s): ", b->isbn);
    fgets(b->isbn, 20, stdin); b->isbn[strcspn(b->isbn, "\n")] = '\0';

    printf("Enter new year (%d): ", b->year);
    scanf("%d", &b->year);
    getchar();

    printf("\nBook updated!\n\n");
}

// Supprimer un livre (interdit si emprunté)
void deleteBook(Book books[], int *nbBooks, int id) {
    int index = -1;

    for (int i = 0; i < *nbBooks; i++) {
        if (books[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Livre introuvable.\n");
        return;
    }

    // Empêcher suppression si le livre est emprunté (status==0)
    if (books[index].status == 0) {
        printf("Impossible de supprimer ce livre : il est actuellement emprunte.\n");
        printf("Veuillez attendre son retour avant suppression.\n\n");
        return;
    }

    // Demande de confirmation
    printf("\nEtes-vous sur de vouloir supprimer le livre suivant ?\n");
    printf("ID: %d | %s %s\n", books[index].id, books[index].title, books[index].author);
    printf("Cette action est definitive. (y/n) : ");

    char confirm;
    scanf(" %c", &confirm);
    getchar(); // nettoyer buffer

    if (confirm != 'y' && confirm != 'Y') {
        printf("Suppression annulee. Aucun changement effectue.\n\n");
        return;
    }

    // Suppression
    for (int j = index; j < *nbBooks - 1; j++) {
        books[j] = books[j + 1];
    }
    (*nbBooks)--;

    printf("Livre supprime avec succes.\n");
    printf("Le livre n'apparaitra plus dans la bibliotheque ni dans les recherches.\n\n");
}
