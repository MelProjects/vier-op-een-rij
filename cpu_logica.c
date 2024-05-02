#include "cpu_logica.h"
#include "game_logica.h"
#include "main.h"

// Zet zetten voor de CPU-speler (willekeurige zet)
int CPUzet(BordToestand *toestand) {
    int geldigeZet[KOLOMMEN];
    int geldigeZetTeller = 0;

    for (int kol = 0; kol < KOLOMMEN; kol++) {
        if (toestand->bord[0][kol] == ' ') {
            geldigeZet[geldigeZetTeller] = kol;
            geldigeZetTeller++;
        }
    }

    if (geldigeZetTeller == 0) {
        return 0; // Geen geldige zetten meer, speelbord is vol
    }
    int willekeurigeZet = geldigeZet[rand() % geldigeZetTeller]; // rand() voor pseudo-willekeurigheid
    return zetZetten(toestand, willekeurigeZet);
}

// Zet zetten voor de CPU-speler (slimme zet)
int CPUzetSlim(BordToestand *toestand) {
    for (int kol = 0; kol < KOLOMMEN; kol++) {
        for (int rij = 0; rij < RIJEN; rij++) {
            // Controleren of de plek waar de zet gezet wordt leeg is en er beneden gevuld is
            if (toestand->bord[rij][kol] == ' ' && (rij == RIJEN - 1 || toestand->bord[rij + 1][kol] != ' ')) {
                // Controleren of de CPU kan winnen door een O in deze kolom te plaatsen
                toestand->bord[rij][kol] = 'O';
                if (checkWin(toestand, 'O')) {
                    toestand->huidigeSpeler = 1; // Wisselen naar de tegenstander
                    return 1;
                }
                toestand->bord[rij][kol] = ' '; // Zet ongedaan maken

                // Controleren of de tegenstander kan winnen door een stuk in deze kolom te plaatsen
                toestand->bord[rij][kol] = 'X';
                if (checkWin(toestand, 'X')) {
                    toestand->bord[rij][kol] = 'O'; // Zet van de tegenstander blokkeren
                    toestand->huidigeSpeler = 1; // Wisselen naar de tegenstander
                    return 1;
                }
                toestand->bord[rij][kol] = ' '; // Zet ongedaan maken
            }
        }
    }

    // Als er geen winnende of blokkerende zet is, maak dan een willekeurige zet
    return CPUzet(toestand);
}
