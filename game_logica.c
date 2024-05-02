#include "game_logica.h"
#include "main.h"

// Initialiseren van het speelbord
void initialiserenBord(BordToestand *toestand) {
    for (int i = 0; i < RIJEN; i++) {
        for (int j = 0; j < KOLOMMEN; j++) {
           toestand->bord[i][j] = ' ';
        }
    }
    toestand->huidigeSpeler = 1; // Speler 1 begint
}

// Printen van het speelbord
void printBord(const BordToestand *toestand) {
// Onderaan het speelbord bevind zich een rij met getallen
// Hierdoor is het meer overzichtelijk waar de X of O wordt geplaatst
int kolNummers[7] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < RIJEN; i++) {
        for (int j = 0; j < KOLOMMEN; j++) {
            printf("| %c ", toestand->bord[i][j]);
        }
        printf("|\n");
    }
    // Spelboord eindigen met ----
    for (int j = 0; j < KOLOMMEN; j++) {
        printf("----");
    }
    printf("-\n");

    // Rij met nummers van kolommen printen
    for (int j = 0; j < KOLOMMEN; j++) {
      printf("  %d ", kolNummers[j]);
    }
    printf("\n");
}

// Zet zetten op het speelbord
int zetZetten(BordToestand *toestand, int kol) {
    if (kol < 0 || kol >= KOLOMMEN || toestand->bord[0][kol] != ' ') {
        // Ongeldige zet
        return 0;
    }

    // Zet zetten en invullen op het speelbord
    int speler = toestand->huidigeSpeler;
    for (int i = RIJEN - 1; i >= 0; i--) {
        if (toestand->bord[i][kol] == ' ') {
            toestand->bord[i][kol] = (speler == 1) ? 'X' : 'O'; // Juiste teken plaatsen X of O
            toestand->huidigeSpeler = (speler + 1) % 2; // Wisselen tussen spelers
            return 1;
        }
    }

    return 0; // Kolom is vol
}

// Checken of een speler gewonnen heeft
bool checkWin(const BordToestand *toestand, char speler) {
    // Check horizontaal
    for (int rij = 0; rij < RIJEN; rij++) {
        for (int kol = 0; kol <= KOLOMMEN - WINNENDE_LENGTE; kol++) {
            int teller = 0;
            for (int i = 0; i < WINNENDE_LENGTE; i++) {
                if (toestand->bord[rij][kol + i] == speler) {
                    teller++;
                }
            }
            if (teller == WINNENDE_LENGTE) {
                return true;
            }
        }
    }

    // Check verticaal
    for (int kol = 0; kol < KOLOMMEN; kol++) {
        for (int rij = 0; rij <= RIJEN - WINNENDE_LENGTE; rij++) {
            int teller = 0;
            for (int i = 0; i < WINNENDE_LENGTE; i++) {
                if (toestand->bord[rij + i][kol] == speler) {
                    teller++;
                }
            }
            if (teller == WINNENDE_LENGTE) {
                return true;
            }
        }
    }

    // Check diagonaal (linksboven naar rechtsonder)
    for (int rij = 0; rij <= RIJEN - WINNENDE_LENGTE; rij++) {
        for (int kol = 0; kol <= KOLOMMEN - WINNENDE_LENGTE; kol++) {
            int teller = 0;
            for (int i = 0; i < WINNENDE_LENGTE; i++) {
                if (toestand->bord[rij + i][kol + i] == speler) {
                    teller++;
                }
            }
            if (teller == WINNENDE_LENGTE) {
                return true;
            }
        }
    }

    // Check diagonaal (rechtsboven naar linksonder)
    for (int rij = 0; rij <= RIJEN - WINNENDE_LENGTE; rij++) {
        for (int kol = WINNENDE_LENGTE - 1; kol < KOLOMMEN; kol++) {
            int teller = 0;
            for (int i = 0; i < WINNENDE_LENGTE; i++) {
                if (toestand->bord[rij + i][kol - i] == speler) {
                    teller++;
                }
            }
            if (teller == WINNENDE_LENGTE) {
                return true;
            }
        }
    }
    // Wanneer er nog geen winnaar is return false
    return false;
}

// Controleren of het bord vol is (gelijkspel)
bool gelijkspel(const BordToestand *toestand) {
    for (int kol = 0; kol < KOLOMMEN; kol++) {
        if (toestand->bord[0][kol] == ' ') {
            return false; // Tenminste één kolom heeft een geldige zet
        }
    }
    return true; // Geen geldige zetten meer, het is gelijkspel
}
