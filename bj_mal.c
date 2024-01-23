#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARDS 52
#define CARD_VALUES 13
#define MAX_HAND 10

// Représentation des cartes
char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *suits[] = {"Cœurs", "Carreaux", "Piques", "Trèfles"};

struct carte {
    char *valeur;
    char *couleur;
    int valeurNumerique;
};

// Fonctions pour la gestion du jeu
void initialiserDeck(struct carte deck[]) {
    for (int i = 0; i < TOTAL_CARDS; i++) {
        deck[i].valeur = values[i % CARD_VALUES];
        deck[i].couleur = suits[i / CARD_VALUES];
        deck[i].valeurNumerique = (i % CARD_VALUES) + 1;
        if (deck[i].valeurNumerique > 10) deck[i].valeurNumerique = 10;
        if (i % CARD_VALUES == CARD_VALUES - 1) deck[i].valeurNumerique = 11;
    }
}

void melangerDeck(struct carte deck[]) {
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARDS; i++) {
        int j = rand() % TOTAL_CARDS;
        struct carte temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void afficherCarte(struct carte c) {
    printf("  %s de %s\n", c.valeur, c.couleur);
}

int sommeMain(struct carte main[], int numCartes) {
    int somme = 0;
    for (int i = 0; i < numCartes; i++) {
        somme += main[i].valeurNumerique;
    }
    return somme;
}

void distribuerCartesInitiales(struct carte deck[], struct carte mainJoueur[], int *numCartesJoueur, int *sommeJoueur) {
    mainJoueur[*numCartesJoueur++] = deck[0];
    mainJoueur[*numCartesJoueur++] = deck[1];
    *sommeJoueur = sommeMain(mainJoueur, *numCartesJoueur);
}

void tirerCarte(struct carte deck[], struct carte mainJoueur[], int *numCartesJoueur, int *sommeJoueur) {
    mainJoueur[*numCartesJoueur] = deck[*numCartesJoueur + 1];
    *sommeJoueur = sommeMain(mainJoueur, ++(*numCartesJoueur));

    printf("Nouvelle carte :\n");
    afficherCarte(mainJoueur[*numCartesJoueur - 2]);
    printf("Somme totale : %d\n", *sommeJoueur);
}

int main() {
    struct carte deck[TOTAL_CARDS];
    struct carte mainJoueur[MAX_HAND];
    int numCartesJoueur = 0;
    int sommeJoueur = 0;
    char choix;

    initialiserDeck(deck);
    melangerDeck(deck);

    printf("Bienvenue au Blackjack !\n");

    distribuerCartesInitiales(deck, mainJoueur, &numCartesJoueur, &sommeJoueur);

    printf("Vos cartes :\n");
    afficherCarte(mainJoueur[0]);
    afficherCarte(mainJoueur[1]);
    printf("Somme totale : %d\n", sommeJoueur);

    while (sommeJoueur < 21) {
        printf("Voulez-vous une autre carte ? (o/n) : ");
        scanf(" %c", &choix);

        if (choix == 'o' || choix == 'O') {
            tirerCarte(deck, mainJoueur, &numCartesJoueur, &sommeJoueur);
        } else {
            break;
        }
    }

    // Reste du jeu et résultats

    return 0;
}
