//
// Created by guilh on 13/05/2017.
//

#include "Alunos.h"

Lista_Alunos pesquisaNumAluno(Lista_Alunos lst, int num) {
    Lista_Alunos ptr = lst;
    Lista_Alunos find;
    for (find = 0; ptr != NULL && find == 0; ptr = ptr->next)
        find = (ptr->aluno.num == num) ? ptr : NULL;
    return find;
}

Lista_Ptr_Alunos pesquisaNumPtrAluno(Lista_Ptr_Alunos lst, int num) {
    Lista_Ptr_Alunos ptr = lst;
    Lista_Ptr_Alunos find;
    for (find = NULL; ptr && find == NULL; ptr = ptr->next)
        find = (ptr->aluno->aluno.num == num) ? ptr : NULL;
    return find;
}

void procuraAluno(Lista_Alunos lst, Aluno chave, Lista_Alunos *ant, Lista_Alunos *act) {
    *ant = NULL;
    *act = lst;
    while ((*act) != NULL && (*act)->aluno.num < chave.num) {
        *ant = *act;
        *act = (*act)->next;
    }
    if ((*act) != NULL && (*act)->aluno.num != chave.num)
        *act = NULL; /* Se elemento não encontrado*/
}

void procuraPtrAluno(Lista_Ptr_Alunos lst, Aluno chave, Lista_Ptr_Alunos *ant, Lista_Ptr_Alunos *act) {
    *ant = NULL;
    *act = lst;
    while ((*act) != NULL && (*act)->aluno->aluno.num < chave.num) {
        *ant = *act;
        *act = (*act)->next;
    }
    if ((*act) != NULL && (*act)->aluno->aluno.num != chave.num)
        *act = NULL; /* Se elemento não encontrado*/
}

Lista_Alunos insereAluno(Lista_Alunos lst, Aluno aluno) {
    if (pesquisaNumAluno(lst, aluno.num)) {
        printf("Já existe um aluno com esse número na base de dados! Abortando...\n");
        return lst;
    }
    Lista_Alunos no;
    Lista_Alunos ant, act;
    no = (Lista_Alunos) malloc(sizeof(No_Aluno));
    if (no) {
        no->aluno = aluno;
        procuraAluno(lst, aluno, &ant, &act);
        if (ant) {
            no->next = ant->next;
            no->prev = ant;
            if (ant->next)
                ant->next->prev = no;
            ant->next = no;
        } else {
            if (lst)
                lst->prev = no;
            no->next = lst;
            no->prev = NULL;
            lst = no;
        }
    } else
        printf("Erro de memoria. Nao foi possivel adicionar aluno\n.");
    return lst;
}

Lista_Ptr_Alunos inserePtrAluno(Lista_Ptr_Alunos lst, Lista_Alunos aluno) {
    if (pesquisaNumPtrAluno(lst, aluno->aluno.num)) {
        printf("Já existe um aluno com esse número inscrito! Abortando...\n");
        return lst;
    }
    Lista_Ptr_Alunos no;
    Lista_Ptr_Alunos ant, act;
    no = (Lista_Ptr_Alunos) malloc(sizeof(No_Ptr_Aluno));
    if (no) {
        no->aluno = aluno;
        procuraPtrAluno(lst, aluno->aluno, &ant, &act);
        if (ant) {
            no->next = ant->next;
            no->prev = ant;
            if (ant->next)
                ant->next->prev = no;
            ant->next = no;
        } else {
            if (lst)
                lst->prev = no;
            no->next = lst;
            no->prev = NULL;
            lst = no;
        }
    } else
        printf("Erro de memoria. Nao foi possivel criar relacao.\n");
    return lst;
}

Lista_Ptr_Alunos destroiListaPtrAlunos(Lista_Ptr_Alunos lst) {
    Lista_Ptr_Alunos temp_ptr;
    while (lst) {
        temp_ptr = lst;
        lst = lst->next;
        free(temp_ptr);
    }
    return NULL;
}

Lista_Alunos destroiListaAlunos(Lista_Alunos lst) {
    Lista_Alunos temp_ptr;
    while (lst) {
        temp_ptr = lst;
        lst = lst->next;
        temp_ptr->aluno.exames = destroiListaPtrExames(temp_ptr->aluno.exames);
        free(temp_ptr->aluno.curso);
        free(temp_ptr->aluno.nome);
        free(temp_ptr);
    }
    return NULL;
}

Lista_Alunos criaAluno(Lista_Alunos lst) {
    Aluno novo;
    char *nome = malloc(TAM_STR * sizeof(char));
    char *curso = malloc(TAM_STR * sizeof(char));
    printf("Nome do aluno: ");
    fflush(stdin);
    p_scan_nome(nome);
    novo.nome = nome;
    printf("Numero do aluno: ");
    novo.num = p_scan_numAluno(lst);
    printf("Numero de matriculas: ");
    novo.ano = p_scan_int();
    printf("Curso do aluno: ");
    fflush(stdin);
    p_scan_nome(curso);
    novo.curso = curso;
    printf("Regime do aluno\n(n -> normal,\nt -> trabalhador-estudante,\na -> atleta,\nd -> dirigente associativo,\ne -> aluno de Erasmus): ");
    novo.regime = p_scan_char_cond("dante");
    novo.exames = NULL;
    lst = insereAluno(lst, novo);
    return lst;
}

Lista_Ptr_Alunos eliminaPtrAluno(Lista_Ptr_Alunos lst, int num) {
    Lista_Ptr_Alunos ant;
    Lista_Ptr_Alunos aluno = pesquisaNumPtrAluno(lst, num);
    if (aluno != NULL) {
        ant = aluno->prev;
        if (aluno->next != NULL)
            aluno->next->prev = ant;
        if (ant != NULL)
            ant->next = aluno->next;
        else
            lst = aluno->next;
        free(aluno);
    }
    return lst;
}

Lista_Alunos eliminaAluno(Lista_Alunos lst) {
    int num;
    Lista_Alunos aluno;
    Lista_Ptr_Exames ptr;
    if (lst == NULL) {
        printf("Nao ha alunos na base de dados! Abortando...\n");
        return lst;
    }
    imprimeAlunos(lst);
    printf("Numero do aluno a modificar: ");
    num = p_scan_int();
    aluno = pesquisaNumAluno(lst, num);
    while (aluno == NULL) {
        printf("Nao existe aluno com esse numero! Insira de novo: ");
        num = p_scan_int();
        aluno = pesquisaNumAluno(lst, num);
    }
    if (aluno->next != NULL)
        aluno->next->prev = aluno->prev;
    if (aluno->prev != NULL)
        aluno->prev->next = aluno->next;
    else
        lst = aluno->next;
    for (ptr = aluno->aluno.exames; ptr; ptr = ptr->next) {
        ptr->exame->exame.alunos = eliminaPtrAluno(ptr->exame->exame.alunos, aluno->aluno.num);
    }
    free(aluno->aluno.curso);
    free(aluno->aluno.nome);
    free(aluno);
    return lst;
}

Lista_Alunos modificaAluno(Lista_Alunos lst) {
    Lista_Alunos aluno, ant, act;
    int num, escolha = 0;
    if (lst == NULL) {
        printf("Nao ha alunos na base de dados! Abortando...\n");
        return lst;
    }
    imprimeAlunos(lst);
    printf("Numero do aluno a modificar: ");
    num = p_scan_int();
    aluno = pesquisaNumAluno(lst, num);
    while (aluno == NULL) {
        printf("Nao existe aluno com esse numero! Insira de novo: ");
        num = p_scan_int();
        aluno = pesquisaNumAluno(lst, num);
    }
    while (escolha != 6) {
        printf("\nModificar:\n1 - Numero\n2 - Nome\n3 - Matriculas\n4 - Curso\n5 - Regime\n\n6 - Voltar\n\nEscolha a opcao: ");
        while (scanf("%d", &escolha) == 0)
            printf("Insira um NUMERO: ");
        fflush(stdin);
        switch (escolha) {
            case 1:
                printf("Numero do aluno: ");
                aluno->aluno.num = p_scan_numAluno(lst);
                if (aluno->prev)
                    aluno->prev->next = aluno->next;
                else
                    lst = aluno->next;
                if (aluno->next)
                    aluno->next->prev = aluno->prev;
                procuraAluno(lst, aluno->aluno, &ant, &act);
                if (ant) {
                    aluno->next = ant->next;
                    aluno->prev = ant;
                    if (ant->next)
                        ant->next->prev = aluno;
                    ant->next = aluno;
                }
                else {
                    if (lst)
                        lst->prev = aluno;
                    aluno->next = lst;
                    aluno->prev = NULL;
                    lst = aluno;
                }
                break;
            case 2:
                printf("Introduza o novo nome: ");
                p_scan_nome(aluno->aluno.nome);
                break;
            case 3:
                printf("Introduza o numero de matriculas: ");
                aluno->aluno.ano = p_scan_int();
                break;
            case 4:
                printf("Introduza o nome do curso: ");
                p_scan_nome(aluno->aluno.curso);
                break;
            case 5:
                aluno->aluno.regime = p_scan_char_cond("dante");
                break;
            case 6:
                break;
            default:
                printf("Opcao invalida! Escolha outra opcao...\n");
                break;
        }
    }
    return lst;
}

void imprimeAluno(Aluno aluno) {
    printf("Numero: %ld\n", aluno.num);
    printf("Nome: %s\n", aluno.nome);
    printf("Curso: %s\n", aluno.curso);
    printf("Matriculas: %ld\n", aluno.ano);
    printf("Regime: ");
    switch (aluno.regime) {
        case 'n':
            printf("Normal\n");
            break;
        case 't':
            printf("Trabalhador-estudante\n");
            break;
        case 'a':
            printf("Atleta\n");
            break;
        case 'd':
            printf("Dirigente associativo\n");
            break;
        case 'e':
            printf("Aluno de Erasmus\n");
            break;
        default:
            printf("Regime introduzido invalido! Modifique este aluno!\n");
            break;
    }
}

void imprimeAlunos(Lista_Alunos alunos) {
    Lista_Alunos ptr = alunos;
    for (ptr; ptr != NULL; ptr = ptr->next) {
        imprimeAluno(ptr->aluno);
        printf("\n");
    }
}