#ifndef PROJETO_EXAMES_H
#define PROJETO_EXAMES_H

#include "Estruturas.h"
#include "Alunos.h"
#include "Tempo.h"
#include "Disciplinas.h"

Lista_Exames pesquisaNumExame(Lista_Exames, int);

Lista_Ptr_Exames pesquisaNumPtrExame(Lista_Ptr_Exames, int);

void procuraExame(Lista_Exames, Exame, Lista_Exames *, Lista_Exames *);

void procuraPtrExame(Lista_Ptr_Exames, Exame, Lista_Ptr_Exames *, Lista_Ptr_Exames *);

void procuraSala(Lista_Salas, char *, Lista_Salas *, Lista_Salas *);

Lista_Exames insereExame(Lista_Exames, Exame);

Lista_Ptr_Exames inserePtrExame(Lista_Ptr_Exames, Lista_Exames);

Lista_Salas insereSala(Lista_Salas, char *);

Lista_Salas destroiListaSalas(Lista_Salas);

Lista_Ptr_Exames destroiListaPtrExames(Lista_Ptr_Exames);

Lista_Exames destroiListaExames(Lista_Exames);

void atribuiSalas(Lista_Exames);

Lista_Exames criaExame(Lista_Exames, Lista_Disciplinas *);

Lista_Salas eliminaSala(Lista_Salas, char *);

Lista_Ptr_Exames eliminaPtrExame(Lista_Ptr_Exames, int);

Lista_Exames eliminaExame(Lista_Exames, Lista_Exames);

Lista_Exames eliminaExamesAntigos(Lista_Exames);

Lista_Exames moveExame(Lista_Exames, Lista_Exames);

void removeConflito(Lista_Exames);

Lista_Exames modificaExame(Lista_Exames, Lista_Disciplinas *);

void imprimeExame(Exame);

void imprimeExames(Lista_Exames);

void imprimeAlunosInscritos(Exame);

void imprimeExamesAluno(Aluno);

void imprimeSalas(Exame);

void inscreveAluno(Lista_Exames, Lista_Alunos);

void removeInscricao(Lista_Exames);

void verificaSalasSuficientes(Lista_Exames);

#endif //PROJETO_EXAMES_H