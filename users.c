
#include "users.h"
#include <stdio.h>
#include <string.h>
#include "stockage.h"

void lireChaineValidee(char *buffer, int tailleMax, const char *invite, int (*validator)(const char *), const char *msgErreur) {
    while (1) {
        printf("%s", invite);
        fgets(buffer, tailleMax, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) {
            printf("Erreur : la valeur ne peut pas etre vide.\n");
            continue;
        }
        if (validator && !validator(buffer)) {
            printf("Erreur : %s\n", msgErreur);
            continue;
        }
        break;
    }
}

int valideEmail(const char *mail) {
    return strchr(mail, '@') != NULL;
}

void searchUtilisateur(User users[], int *nbUsers) {
    int choix = -1;

    do {
        printf("\n===== GESTION UTILISATEURS =====\n");
        printf("1. Ajouter un utilisateur\n");
        printf("2. Modifier un utilisateur\n");
        printf("3. Supprimer un utilisateur\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar(); // consommer le '\n' avant d'utiliser fgets dans users.c

        switch (choix) {
            case 1:
                ajouterUtilisateur(users, nbUsers);      // void(User*, int*)
                break;
            case 2:
                modifierUtilisateur(users, *nbUsers);    // void(User*, int)
                break;
            case 3:
                supprimerUtilisateur(users, nbUsers);    // void(User*, int*)
                break;
            case 0:
                printf("Retour au menu administrateur...\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choix != 0);
}

//Fonction Admin
void ajouterUtilisateur(User *users, int *nbUsers) {
    User newUser;
    newUser.id = *nbUsers + 1;

    lireChaineValidee(newUser.name, sizeof(newUser.name), "Nom (max 20 caracteres) : ", NULL, "");
    lireChaineValidee(newUser.surname, sizeof(newUser.surname), "Prenom (max 20 caracteres) : ", NULL, "");
    lireChaineValidee(newUser.idStudent, sizeof(newUser.idStudent), "ID etudiant (max 20 caracteres) : ", NULL, "");
    lireChaineValidee(newUser.mail, sizeof(newUser.mail), "Email (max 70 caracteres, doit contenir '@') : ", valideEmail, "doit contenir '@'");

    newUser.nbStudentLoans = 0;

    users[*nbUsers] = newUser;
    (*nbUsers)++;

    sauvegarderUtilisateurs(users, *nbUsers);

    printf("Utilisateur ajoute !\n");
}

void afficherUtilisateurs(User *users, int nbUsers) {
    printf("\n=== Liste des utilisateurs ===\n");

    if (nbUsers == 0) {
        printf("Aucun utilisateur enregistre.\n");
        return;
    }

    for (int i = 0; i < nbUsers; i++) {
        printf("%d) %s %s | ID etudiant: %s | Email: %s\n",
               users[i].id, users[i].name, users[i].surname,
               users[i].idStudent, users[i].mail);
    }
}

void modifierUtilisateur(User *users, int nbUsers) {
    char idRecherche[20];
    printf("\nID etudiant a modifier : ");
    fgets(idRecherche, sizeof(idRecherche), stdin);
    idRecherche[strcspn(idRecherche, "\n")] = '\0';

    for (int i = 0; i < nbUsers; i++) {
        if (strcmp(users[i].idStudent, idRecherche) == 0) {
            lireChaineValidee(users[i].name, sizeof(users[i].name), "Nouveau nom (max 20 caracteres) : ", NULL, "");
            lireChaineValidee(users[i].surname, sizeof(users[i].surname), "Nouveau prenom (max 20 caracteres) : ", NULL, "");
            lireChaineValidee(users[i].mail, sizeof(users[i].mail), "Nouvel email (max 70 caracteres, doit contenir '@') : ", valideEmail, "doit contenir '@'");

            sauvegarderUtilisateurs(users, nbUsers);

            printf("Utilisateur modifie !\n");
            return;
        }
    }
    printf("Aucun utilisateur trouve avec cet ID.\n");
}

void supprimerUtilisateur(User *users, int *nbUsers) {
    char idRecherche[20];
    printf("\nID etudiant a supprimer : ");
    scanf("%s", idRecherche);

    for (int i = 0; i < *nbUsers; i++) {
        if (strcmp(users[i].idStudent, idRecherche) == 0) {

            for (int j = i; j < *nbUsers - 1; j++) {
                users[j] = users[j + 1];
            }
            (*nbUsers)--;

            sauvegarderUtilisateurs(users, *nbUsers);

            printf("Utilisateur supprime !\n");
            return;
        }
    }

    printf("Aucun utilisateur trouve.\n");
}

// === Fonctions Utilisateur ===
int creerCompte(User *users, int *nbUsers) {
    getchar();
    printf("\n=== Creer un compte ===\n");

    User newUser;
    newUser.id = *nbUsers + 1;

    lireChaineValidee(newUser.name, sizeof(newUser.name), "Nom (max 20 caracteres) : ", NULL, "");
    lireChaineValidee(newUser.surname, sizeof(newUser.surname), "Prenom (max 20 caracteres) : ", NULL, "");
    lireChaineValidee(newUser.idStudent, sizeof(newUser.idStudent), "ID etudiant (max 20 caracteres) : ", NULL, "");
    lireChaineValidee(newUser.mail, sizeof(newUser.mail), "Email (max 70 caracteres, doit contenir '@') : ", valideEmail, "doit contenir '@'");

    newUser.nbStudentLoans = 0;

    users[*nbUsers] = newUser;
    (*nbUsers)++;

    sauvegarderUtilisateurs(users, *nbUsers);

    printf("Compte cree avec succes !\n");
    return *nbUsers - 1;
}

int connexionUtilisateur(User *users, int nbUsers) {
    char idRecherche[20];
    printf("\n=== Connexion utilisateur ===\n");
    printf("Entrez votre ID etudiant : ");
    scanf("%s", idRecherche);

    for (int i = 0; i < nbUsers; i++) {
        if (strcmp(users[i].idStudent, idRecherche) == 0) {
            printf("Bienvenue %s %s !\n", users[i].surname, users[i].name);
            return i;
        }
    }

    printf("Aucun utilisateur trouve.\n");
    return -1;
}

void modifierMonCompte(User *users, int monIndex, int nbUsers) {
    printf("\n=== Modifier mon compte ===\n");
    lireChaineValidee(users[monIndex].name, sizeof(users[monIndex].name), "Nouveau nom (max 20 caracteres) : ", NULL, "");
    lireChaineValidee(users[monIndex].surname, sizeof(users[monIndex].surname), "Nouveau prenom (max 20 caracteres) : ", NULL, "");
    lireChaineValidee(users[monIndex].mail, sizeof(users[monIndex].mail), "Nouvel email (max 70 caracteres, doit contenir '@') : ", valideEmail, "doit contenir '@'");

    sauvegarderUtilisateurs(users, nbUsers);

    printf("Compte mis a jour !\n");
}

void supprimerMonCompte(User *users, int *nbUsers, int *monIndex) {
    for (int i = *monIndex; i < *nbUsers - 1; i++) {
        users[i] = users[i + 1];
    }
    (*nbUsers)--;
    *monIndex = -1;

    sauvegarderUtilisateurs(users, *nbUsers);

    printf("Votre compte a ete supprime.\n");
}

// === Connexion admin ===
int connexionAdmin() {
    char login[20], motDePasse[20];

    printf("\n=== Connexion Administrateur ===\n");
    printf("Nom d'utilisateur : "); scanf("%s", login);
    printf("Mot de passe : ");      scanf("%s", motDePasse);

    return (strcmp(login, "admin") == 0 && strcmp(motDePasse, "admin123") == 0);
}

