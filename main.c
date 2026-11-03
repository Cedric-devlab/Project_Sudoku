#include "Sudoku.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Lit une ligne complete, en rejetant proprement les lignes trop longues. */
static int lireLigne(char texte[], int capacite)
{
    if (!fgets(texte, capacite, stdin)) return 0;
    if (!strchr(texte, '\n') && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        texte[0] = '\0';
    }
    return 1;
}

/* Accepte exactement nombre entiers entre 1 et 9, separes par des espaces. */
static int lireEntiers(char *texte, int valeurs[], int nombre)
{
    for (int i = 0; i < nombre; i++) {
        while (isspace((unsigned char)*texte)) texte++;
        char *fin;
        errno = 0;
        long valeur = strtol(texte, &fin, 10);
        if (fin == texte || errno || valeur < 1 || valeur > 9) return 0;
        if (*fin && !isspace((unsigned char)*fin)) return 0;
        valeurs[i] = (int)valeur;
        texte = fin;
    }
    while (isspace((unsigned char)*texte)) texte++;
    return *texte == '\0';
}

static int commande(char *texte, int lettre)
{
    while (isspace((unsigned char)*texte)) texte++;
    if (tolower((unsigned char)*texte) != lettre) return 0;
    texte++;
    while (isspace((unsigned char)*texte)) texte++;
    return *texte == '\0';
}

int main(void)
{
    int solution[TAILLE][TAILLE], grille[TAILLE][TAILLE], initiale[TAILLE][TAILLE];
    char texte[128];
    int choix[1], coup[3];
    srand((unsigned int)time(NULL));
    puts("SUDOKU : chiffres 1 a 9, sans doublon par ligne, colonne et bloc.");
    puts("Les cases initiales sont protegees. Un faux chiffre coute une erreur.");
    puts("Une saisie mal formee ou une case protegee ne coute aucune erreur.");
    for (;;) {
        printf("Niveau : 1 facile, 2 moyen, 3 difficile : ");
        fflush(stdout);
        if (!lireLigne(texte, sizeof texte)) return 0;
        if (lireEntiers(texte, choix, 1) && choix[0] <= 3) break;
        puts("Choisir 1, 2 ou 3.");
    }
    puts("Generation en cours...");
    if (!genererPartie(solution, grille, choix[0])) {
        puts("Generation impossible apres 100 tentatives. Relancez le programme.");
        return 1;
    }
    copierGrille(initiale, grille);
    const int limites[] = {9, 5, 3};
    int erreurs = 0, limite = limites[choix[0] - 1];
    while (!grilleComplete(grille)) {
        afficherGrille(grille);
        printf("Erreurs : %d/%d. Entrer ligne colonne valeur (ex. 2 4 7), ou q : ", erreurs, limite);
        fflush(stdout);
        if (!lireLigne(texte, sizeof texte)) { puts("\nFin de saisie."); return 0; }
        if (commande(texte, 'q')) {
            printf("Confirmer l'abandon ? o/n : ");
            fflush(stdout);
            if (!lireLigne(texte, sizeof texte)) return 0;
            if (commande(texte, 'o')) { puts("Partie abandonnee."); return 0; }
            continue;
        }
        if (!lireEntiers(texte, coup, 3)) {
            puts("Entrer exactement trois entiers de 1 a 9.");
            continue;
        }
        int resultat = jouerCoup(grille, initiale, solution, coup[0] - 1, coup[1] - 1, coup[2]);
        if (resultat == -2) puts("Cette case initiale est protegee.");
        else if (resultat == 0) {
            erreurs++;
            puts("Ce chiffre ne correspond pas a la solution.");
            if (erreurs == limite) { puts("Defaite : limite d'erreurs atteinte."); return 0; }
        }
    }
    afficherGrille(grille);
    puts("Victoire ! La grille est complete et valide.");
    return 0;
}
