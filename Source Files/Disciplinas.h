//
// Created by guilh on 03/05/2017.
//

#ifndef PROJETO_DISCIPLINAS_H
#define PROJETO_DISCIPLINAS_H

#include "Estruturas.h"
#include "Exames.h"

void imprimeDisciplinas(Lista_Disciplinas);

Lista_Disciplinas pesquisaDisciplinas(Lista_Disciplinas, char *);

Lista_Disciplinas insereDisciplina(Lista_Disciplinas, Disciplina);

Lista_Disciplinas destroiListaDisciplinas(Lista_Disciplinas);

Lista_Disciplinas criaDisciplina(Lista_Disciplinas);

Lista_Disciplinas modificaDisciplina(Lista_Disciplinas);

Lista_Disciplinas eliminaDisciplina(Lista_Disciplinas, Lista_Exames *);

#endif //PROJETO_DISCIPLINAS_H