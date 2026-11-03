# Sudoku en C

Dans CLion : ouvrir ce dossier `moteur` comme projet CMake, puis lancer la cible `sudoku`.
Les fichiers main.c, Sudoku.c et Sudoku.h doivent rester ensemble.
La cible test_sudoku execute les tests du moteur (avec assertions actives).

## Organisation

- Sudoku.h : constantes, prototypes, contrats des fonctions.
- Sudoku.c : verification, backtracking, generation, comptage, coups et affichage.
- main.c : saisie console et deroulement de la partie.
- test_sudoku.c : verification sur 60 parties reproductibles.

Les coordonnees saisies vont de 1 a 9 ; celles du moteur de 0 a 8.
Saisir trois nombres separes par des espaces, par exemple `2 4 7`.
`q` puis `o` permet d'abandonner. Une autre reponse annule l'abandon.

## Choix a expliquer dans le rapport

Grille 9x9, blocs 3x3. Generation par backtracking aleatoire :
selection de la premiere case vide en parcourant les lignes puis les colonnes,
essai des candidats dans un ordre melange, appel recursif et retour en arriere
en cas d'impasse. Aucune heuristique MRV.
Apres chaque retrait, le compteur de solutions s'arrete a 2 ; le retrait
est conserve seulement si le compteur vaut 1.

Niveaux : 45, 35 et 28 indices ; minimum respectif de 4, 3 et 2 indices
dans CHAQUE ligne, colonne et bloc. Ce minimum est notre definition
operationnelle de la repartition equilibree ; il ne garantit pas a lui seul
une difficulte logique precise. Maximum de 100 tentatives de generation.

Un faux chiffre par rapport a la solution unique est refuse et compte comme
une erreur. Limites : 9, 5 et 3. Les erreurs de syntaxe et tentatives de
modifier les indices initiaux sont refusees sans penalite.

Bibliotheques standard : stdio.h (affichage/saisie), stdlib.h (rand, srand,
strtol), time.h (time), ctype.h (isspace, tolower), errno.h (conversion),
string.h (recherche de fin de ligne). Pas de bibliotheque Sudoku.

Le moteur est livre pour le Sudoku 9x9 : les niveaux, saisies et affichage
ne sont pas generalises a d'autres tailles. L'interface console est dans
main.c et afficherGrille ; le reste du moteur peut servir a une autre interface.
