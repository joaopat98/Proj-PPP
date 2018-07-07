//
// Created by Utilizador on 23/05/2017.
//

#ifndef PROJETO_PROTECOES_H
#define PROJETO_PROTECOES_H

#include <stdlib.h>
#include <stdio.h>
#include "Estruturas.h"
#include "Exames.h"
#include "Alunos.h"
#include "Disciplinas.h"
#include "Tempo.h"

long p_scan_int();

long p_scan_numAluno(Lista_Alunos );

int p_scan_numExame(Lista_Exames );

void p_scan_nome(char *);

char p_scan_char();

char p_scan_char_cond(char *);

Data p_leData();

Hora p_leHora();
#endif //PROJETO_PROTECOES_H
