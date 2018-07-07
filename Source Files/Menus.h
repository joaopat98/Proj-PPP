//
// Created by guilh on 01/05/2017.
//

#ifndef PROJETO_MENUS_H
#define PROJETO_MENUS_H

#include "Estruturas.h"
#include "Exames.h"
#include "Alunos.h"
#include "Disciplinas.h"
#include "Tempo.h"


void menuAlunos(Lista_Alunos *);

void menuDisciplinas(Lista_Disciplinas *, Lista_Exames *);

void menuExames(Lista_Alunos , Lista_Exames *, Lista_Disciplinas *);

void menuSalas(Lista_Exames );

void menuInscricoes(Lista_Exames , Lista_Alunos );

void menuPrincipal(Lista_Alunos *, Lista_Exames *, Lista_Disciplinas *);

#endif //PROJETO_MENUS_H