// gcc -std=c99 -Wall -Wextra -Wpedantic -Wconversion -o vier vier-op-een-rij.c game_logica.c cpu_logica.c
#include "cpu_logica.h"
#include "game_logica.h"
#include "main.h"

int main() {
    BordToestand gameToestand;
    initialiserenBord(&gameToestand);
    char spelerKeuze;
    char CPUmode[10];
    int isGeldig = 0;

    printf("Welkom bij vier op een rij!\n");
    printf("Regels: Spelers plaatsen hun X of O (een per "
            "beurt) op het speelbord. De X of O kan op "
            "de onderste rij geplaatst worden of direct bovenop "
            "een andere X of O. De eerste speler die verticaal, "
            "horizontaal of diagonaal vier op een rij krijgt, wint.\n");

    while (!isGeldig) {
            printf("Wil je tegen CPU spelen? (j/n): ");
            scanf("%c", &spelerKeuze);

            if (spelerKeuze == 'j' || spelerKeuze == 'n') {
            isGeldig = 1;
            } else {
            printf("Ongeldige invoer. Voer 'j' of 'n' in.\n");
            }
            // input buffer legen
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    // isGeldig resetten voor de volgende input controle
    isGeldig = 0;

    // Gekozen om tegen lokale speler te spelen
    if (spelerKeuze == 'n') {
        printf("Speler 1: X\nSpeler 2: O\n");
    }
    // Gekozen om tegen CPU te spelen
    if (spelerKeuze == 'j') {
        while (!isGeldig) {
            printf("Wil je easy of hard mode spelen? (easy/hard)\n ");
            scanf("%s", CPUmode);

            if (strcmp(CPUmode, "easy") == 0 || strcmp(CPUmode, "hard") == 0) {
            isGeldig = 1;
            } else {
            printf("Ongeldige input. Voer 'easy' of 'hard' in.\n");
            }
        }
    printf("Jij bent speler 1: X\nCPU is speler 2: O\n");
    }

    while (1) {
        printf("\n");
        printBord(&gameToestand);

        // Zet zetten voor Speler X en lokale speler O
        if (gameToestand.huidigeSpeler == 1 || spelerKeuze == 'n') {
            int zet;
            printf("Speler %c, voer jouw zet in (1-%d): ", (gameToestand.huidigeSpeler == 1) ? 'X' : 'O', KOLOMMEN);
    
            // Controleren of de input correct is
            if (scanf("%d", &zet) != 1) {
                // Wanneer scanf iets anders dan 1 terug geeft, is de input verkeerd
                printf("Ongeldige invoer. Voer een geldig getal in.\n");
                // Input buffer legen
                while (getchar() != '\n');
            } else {
                zet--; // Pas zet aan naar array indexing
        
                // Controleren of het ingevoerde getal binnen de juiste waarde is
                if (zet < 0 || zet >= KOLOMMEN) {
                    printf("Ongeldige zet. Voer een zet in tussen 1 en %d.\n", KOLOMMEN);
                } else {
                    // Input uitvoeren
                    if (zetZetten(&gameToestand, zet) == 0) {
                    printf("Ongeldige zet. Probeer opnieuw.\n");
                    }
                }
            }
        } else {
        // CPU zet een zet op basis van de gekozen mode
            printf("CPU is aan het denken...\n");
            if (strcmp(CPUmode, "easy") == 0) {
                CPUzet(&gameToestand);
            }
            else if (strcmp(CPUmode, "hard") == 0) {
                CPUzetSlim(&gameToestand);
            }
        }
        
        // Wanneer er voor lokale speler gekozen is, controleren of iemand gewonnen heeft 
        // en bijbehorende tekst printen
        if (spelerKeuze == 'n') {
            if (checkWin(&gameToestand, 'X')) {
                printf("\n");
                printBord(&gameToestand);
                printf("Speler X wint!\n");
                break;
        } else if (checkWin(&gameToestand, 'O')) {
                printf("\n");
                printBord(&gameToestand);
                printf("Speler O wint!\n");
                break;
            }
        } 
        // Wanneer er voor CPU mode gekozen is, controleren of iemand gewonnen heeft
        // en bijbehorende tekst printen
        else if (spelerKeuze == 'j') {
            if (checkWin(&gameToestand, 'O')) {
                printf("\n");
                printBord(&gameToestand);
                printf("Speler O (CPU) wint!\n");
                break;
            } else if (checkWin(&gameToestand, 'X')) {
                printf("\n");
                printBord(&gameToestand);
                printf("Je hebt gewonnen!\n");
                break;
            }
        }

        // Controleren op gelijkspel
        if (gelijkspel(&gameToestand)) {
            printf("\n");
            printBord(&gameToestand);
            printf("Het is gelijkspel!\n");
            break;
        }
    }
    // Wanneer er een winnaar is het spel afsluiten
    return 0; 
}