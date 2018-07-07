//
// Created by Utilizador on 15/05/2017.
//

#ifndef PROJETO_TEMPO_H
#define PROJETO_TEMPO_H

#include "Estruturas.h"

int cmpData(Data, Data);

int cmpHora(Hora, Hora);

Hora adicionaMinutos(Hora, int);

int verifConflito(Hora, Hora, int, int);

Data leData();

Hora leHora();

void imprimeData(Data);

void imprimeHora(Hora);

#endif //PROJETO_TEMPO_H
