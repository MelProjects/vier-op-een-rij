#ifndef GAME_LOGICA_H
#define GAME_LOGICA_H

#include "main.h"

void initialiserenBord(BordToestand *toestand);
void printBord(const BordToestand *toestand);
int zetZetten(BordToestand *toestand, int kol);
bool checkWin(const BordToestand *toestand, char speler);
bool gelijkspel(const BordToestand *toestand);

#endif