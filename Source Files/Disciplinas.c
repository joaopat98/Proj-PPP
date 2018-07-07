//
// Created by guilh on 03/05/2017.
//
#include "Disciplinas.h"
#include "Estruturas.h"

void imprimeDisciplinas(Lista_Disciplinas disciplinas){
    Lista_Disciplinas ptr = disciplinas;
    int i = 0;
    for (ptr; ptr; ptr = ptr->next, i++)
        printf("%d)\nNome - %s\nDocente responsavel - %s\n", i + 1, ptr->disciplina.nome, ptr->disciplina.docente);
}

Lista_Disciplinas pesquisaDisciplinas(Lista_Disciplinas disciplinas, char *nome){
    Lista_Disciplinas ptr = disciplinas;
    while (ptr && (strcmp(ptr->disciplina.nome, nome) != 0))
        ptr = ptr->next;
    return ptr;
}

Lista_Disciplinas insereDisciplina(Lista_Disciplinas disciplinas, Disciplina nova){
    Lista_Disciplinas no = NULL;
    Lista_Disciplinas act;
    no = (Lista_Disciplinas) malloc(sizeof(No_Disciplina));
    if (no) {
        if(pesquisaDisciplinas(disciplinas, nova.nome)) {
            printf("Disciplina ja existe! Abortando...");
            return disciplinas;
        }
        else{
            no->disciplina = nova;
            act = disciplinas;
            if (act) {
                while (act->next)
                    act = act->next;
                act->next = no;
                no->prev = act;
                no->next = NULL;
            } else {
                if (disciplinas)
                    disciplinas->prev = no;
                no->prev = NULL;
                no->next = NULL;
                disciplinas = no;
            }
        }
    }
    return disciplinas;
}

Lista_Disciplinas destroiListaDisciplinas(Lista_Disciplinas lst) {
    Lista_Disciplinas temp_ptr;
    while (lst) {
        temp_ptr = lst;
        lst = lst->next;
        free(temp_ptr->disciplina.docente);
        free(temp_ptr->disciplina.nome);
        free(temp_ptr);
    }
    return NULL;
}

Lista_Disciplinas criaDisciplina(Lista_Disciplinas disciplinas){
    Disciplina nova;
    char *nome = malloc(TAM_STR * sizeof(char));
    char *docente = malloc(TAM_STR * sizeof(char));
    fflush(stdin);
    printf("Insira o nome da Disciplina:\n");
    gets(nome);
    nova.nome = nome;
    printf("Insira o nome do Docente:\n");
    fflush(stdin);
    gets(docente);
    nova.docente = docente;
    disciplinas = insereDisciplina(disciplinas, nova);
    return disciplinas;
}

Lista_Disciplinas eliminaDisciplina(Lista_Disciplinas disciplinas, Lista_Exames *exames){
    Lista_Disciplinas no;
    Lista_Exames ptr;
    char *nome = (char *) malloc(TAM_STR * sizeof(char));
    imprimeDisciplinas(disciplinas);
    printf("Insira o nome da disciplina que deseja eliminar:\n");
    fflush(stdin);
    gets(nome);
    no = pesquisaDisciplinas(disciplinas, nome);
    fflush(stdin);
    while (no == NULL) {
        printf("Essa disciplina nao existe! Insira de novo: ");
        gets(nome);
        no = pesquisaDisciplinas(disciplinas, nome);
        fflush(stdin);
    }
    ptr = (*exames);
    while(ptr){
        Lista_Exames ptr2 = ptr;
        ptr = ptr->next;
        if (ptr2->exame.disciplina == no) {
            *exames = eliminaExame(*exames, ptr2);
        }
    }
    if (no->next != NULL)
        no->next->prev = no->prev;
    if (no->prev != NULL)
        no->prev->next = no->next;
    else
        disciplinas = no->next;
    free(no->disciplina.nome);
    free(no->disciplina.docente);
    free(no);
    free(nome);
    return disciplinas;
}

Lista_Disciplinas modificaDisciplina(Lista_Disciplinas disciplinas){
    Lista_Disciplinas no, no2;
    char *nome = (char *) malloc(TAM_STR * sizeof(char));
    char *docente = (char *) malloc(TAM_STR * sizeof(char));
    if (disciplinas == NULL) {
        printf("Nao ha exames na base de dados! Abortando...\n");
        return disciplinas;
    }
    printf("Disciplinas:\n");
    imprimeDisciplinas(disciplinas);
    printf("Insira o nome da disciplina que deseja modificar:\n");
    fflush(stdin);
    gets(nome);
    no = pesquisaDisciplinas(disciplinas, nome);
    fflush(stdin);
    while (no == NULL) {
        printf("Essa disciplina nao existe! Insira de novo: ");
        gets(nome);
        no = pesquisaDisciplinas(disciplinas, nome);
        fflush(stdin);
    }
    printf("Insira o novo nome da disciplina: \n");
    fflush(stdin);
    gets(nome);
    no2 = pesquisaDisciplinas(disciplinas, nome);
    fflush(stdin);
    while (no2) {
        printf("Essa disciplina já existe! Insira de novo: ");
        gets(nome);
        no2 = pesquisaDisciplinas(disciplinas, nome);
        fflush(stdin);
    }
    no->disciplina.nome = nome;
    printf("Insira o novo nome do docente:\n");
    fflush(stdin);
    gets(docente);
    no->disciplina.docente = docente;
    return disciplinas;
}