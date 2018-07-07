//
// Created by guilh on 13/05/2017.
//

#ifndef PROJETO_ESTRUTURAS_H
#define PROJETO_ESTRUTURAS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_STR 100

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int horas;
    int minutos;
} Hora;

typedef struct {
    char *nome;
    char *docente;
} Disciplina;

typedef struct no_disc *Lista_Disciplinas;

typedef struct no_disc {
    Disciplina disciplina;
    Lista_Disciplinas prev;
    Lista_Disciplinas next;
} No_Disciplina;

typedef struct no_s *Lista_Salas;

typedef struct no_s {
    char *nome;
    Lista_Salas prev;
    Lista_Salas next;
} No_Sala;

typedef struct no_aluno *Lista_Alunos; // definir o no de uma suposta lista de alunos

typedef struct no_ptr_aluno *Lista_Ptr_Alunos;

typedef struct no_exame *Lista_Exames; // definir o no de uma suposta lista de alunos

typedef struct no_ptr_exame *Lista_Ptr_Exames;

typedef struct no_ptr_aluno {
    Lista_Alunos aluno;
    Lista_Ptr_Alunos prev;
    Lista_Ptr_Alunos next;
} No_Ptr_Aluno;

typedef struct no_ptr_exame {
    Lista_Exames exame;
    Lista_Ptr_Exames prev;
    Lista_Ptr_Exames next;
} No_Ptr_Exame;

typedef struct aluno {
    char *nome;
    long num;
    long ano;
    char *curso;
    char regime;// n -> normal, t -> trabalhador-estudante, a -> atleta, d -> dirigente associativo, e -> aluno de Erasmus
    Lista_Ptr_Exames exames;
} Aluno;

typedef struct exame {
    Lista_Disciplinas disciplina;
    char epoca;// n -> Normal, r-> Recurso, e-> Especial
    Data data;
    Hora hora;
    int num;
    int duracao;// em minutos
    Lista_Salas salas;
    Lista_Ptr_Alunos alunos; //adicionar funcao para contar nos da lista
} Exame;

typedef struct no_aluno {
    Aluno aluno;
    Lista_Alunos prev;
    Lista_Alunos next;
} No_Aluno;

typedef struct no_exame {
    Exame exame;
    Lista_Exames prev;
    Lista_Exames next;
} No_Exame;

#endif //PROJETO_ESTRUTURAS_H