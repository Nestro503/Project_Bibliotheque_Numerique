
#include "users.h"
#include <stdio.h>
#include <string.h>


//Fonction Admin
void ajouterUtilisateur(User *users, int *nbUsers) {
    printf("\n=== Ajouter un utilisateur ===\n");
    users[*nbUsers].id = *nbUsers + 1;
    printf("Nom : ");        scanf("%s", users[*nbUsers].name);
    printf("Prenom : ");     scanf("%s", users[*nbUsers].surname);
    printf("ID etudiant : "); scanf("%s", users[*nbUsers].idStudent);
    printf("Email : ");      scanf("%s", users[*nbUsers].mail);

    users[*nbUsers].nbStudentLoans = 0;  // aucun emprunt au début

    (*nbUsers)++;
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
    scanf("%s", idRecherche);

    for (int i = 0; i < nbUsers; i++) {
        if (strcmp(users[i].idStudent, idRecherche) == 0) {
            printf("Nouveau nom : ");     scanf("%s", users[i].name);
            printf("Nouveau prenom : ");  scanf("%s", users[i].surname);
            printf("Nouvel email : ");    scanf("%s", users[i].mail);
            printf("Utilisateur modifier !\n");
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

            printf("Utilisateur supprime !\n");
            return;
        }
    }

    printf("Aucun utilisateur trouve.\n");
}

// === Fonctions Utilisateur ===
int creerCompte(User *users, int *nbUsers) {
    printf("\n=== Creer un compte ===\n");

    users[*nbUsers].id = *nbUsers + 1;

    printf("Nom : ");        scanf("%s", users[*nbUsers].name);
    printf("Prenom : ");     scanf("%s", users[*nbUsers].surname);
    printf("ID etudiant : "); scanf("%s", users[*nbUsers].idStudent);
    printf("Email : ");      scanf("%s", users[*nbUsers].mail);

    users[*nbUsers].nbStudentLoans = 0;

    (*nbUsers)++;
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

void modifierMonCompte(User *users, int monIndex) {
    printf("\n=== Modifier mon compte ===\n");
    printf("Nouveau nom : ");     scanf("%s", users[monIndex].name);
    printf("Nouveau prenom : ");  scanf("%s", users[monIndex].surname);
    printf("Nouvel email : ");    scanf("%s", users[monIndex].mail);
    printf("Compte mis a jour !\n");
}

void supprimerMonCompte(User *users, int *nbUsers, int *monIndex) {
    for (int i = *monIndex; i < *nbUsers - 1; i++) {
        users[i] = users[i + 1];
    }
    (*nbUsers)--;
    *monIndex = -1;
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
