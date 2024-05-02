#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define RIJEN 6
#define KOLOMMEN 7
#define WINNENDE_LENGTE 4

// Struct voor het speelbord
typedef struct {
    char bord[RIJEN][KOLOMMEN];
    int huidigeSpeler; // 1 voor speler 1 (X), 2 voor speler 2 (O)
} BordToestand;

#endif