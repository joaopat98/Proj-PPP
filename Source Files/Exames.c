#include "Exames.h"

Lista_Exames pesquisaNumExame(Lista_Exames lst, int num) {
    Lista_Exames ptr = lst;
    Lista_Exames find;
    for (find = 0; ptr != NULL && find == 0; ptr = ptr->next)
        find = (ptr->exame.num == num) ? ptr : NULL;
    return find;
}

Lista_Ptr_Exames pesquisaNumPtrExame(Lista_Ptr_Exames lst, int num) {
    Lista_Ptr_Exames ptr = lst;
    Lista_Ptr_Exames find;
    for (find = NULL; ptr && find == NULL; ptr = ptr->next)
        find = (ptr->exame->exame.num == num) ? ptr : NULL;
    return find;
}

void procuraExame(Lista_Exames lst, Exame chave, Lista_Exames *ant, Lista_Exames *act) {
    *ant = NULL;
    *act = lst;
    while ((*act) != NULL &&
           (cmpData((*act)->exame.data, chave.data) < 0 || cmpHora((*act)->exame.hora, chave.hora) < 0)) {
        *ant = *act;
        *act = (*act)->next;
    }
    if ((*act) != NULL &&
        (cmpData((*act)->exame.data, chave.data) != 0 || cmpHora((*act)->exame.hora, chave.hora) != 0))
        *act = NULL; /* Se elemento não encontrado*/
}

void procuraPtrExame(Lista_Ptr_Exames lst, Exame chave, Lista_Ptr_Exames *ant, Lista_Ptr_Exames *act) {
    *ant = NULL;
    *act = lst;
    while ((*act) != NULL &&
           (cmpData((*act)->exame->exame.data, chave.data) < 0 || cmpHora((*act)->exame->exame.hora, chave.hora) < 0)) {
        *ant = *act;
        *act = (*act)->next;
    }
    if ((*act) != NULL &&
        (cmpData((*act)->exame->exame.data, chave.data) != 0 || cmpHora((*act)->exame->exame.hora, chave.hora) != 0))
        *act = NULL; /* Se elemento não encontrado*/
}

void procuraSala(Lista_Salas lst, char *chave, Lista_Salas *ant, Lista_Salas *act) {
    *ant = NULL;
    *act = lst;
    while ((*act) != NULL && (strcmpi((*act)->nome, chave) < 0 || strcmpi((*act)->nome, chave) < 0)) {
        *ant = *act;
        *act = (*act)->next;
    }
    if ((*act) != NULL && (strcmpi((*act)->nome, chave) != 0 || strcmpi((*act)->nome, chave) != 0))
        *act = NULL; /* Se elemento não encontrado*/
}

Lista_Exames insereExame(Lista_Exames lst, Exame exame) {
    if (pesquisaNumExame(lst, exame.num)) {
        printf("Já existe um exame com esse número na base de dados! Abortando...\n");
        return lst;
    }
    Lista_Exames no;
    Lista_Exames ant, act;
    no = malloc(sizeof(No_Exame));
    if (no) {
        no->exame = exame;
        procuraExame(lst, exame, &ant, &act);
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
        printf("Erro de memoria. Nao foi possivel adicionar exame.\n");
    return lst;
}

Lista_Ptr_Exames inserePtrExame(Lista_Ptr_Exames lst, Lista_Exames exame) {
    if (pesquisaNumPtrExame(lst, exame->exame.num)) {
        printf("Já existe um exame com esse número nas inscrições! Abortando...\n");
        return lst;
    }
    Lista_Ptr_Exames no;
    Lista_Ptr_Exames ant, act;
    no = malloc(sizeof(No_Ptr_Exame));
    if (no) {
        no->exame = exame;
        procuraPtrExame(lst, exame->exame, &ant, &act);
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

Lista_Salas insereSala(Lista_Salas lst, char *sala) {
    Lista_Salas no;
    Lista_Salas ant, act;
    procuraSala(lst, sala, &ant, &act);
    if (act) {
        printf("A sala já está reservada para este exame!\n");
        return lst;
    }
    no = malloc(sizeof(No_Sala));
    if (no != NULL) {
        no->nome = malloc(TAM_STR * sizeof(char));
        strcpy(no->nome, sala);
        if (ant != NULL) {
            no->next = ant->next;
            no->prev = ant;
            if (ant->next != NULL)
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
        printf("Erro de memoria. Nao foi possivel adicionar sala.\n");
    return lst;
}

Lista_Salas destroiListaSalas(Lista_Salas lst) {
    Lista_Salas temp_ptr;
    while (lst) {
        temp_ptr = lst;
        lst = lst->next;
        free(temp_ptr->nome);
        free(temp_ptr);
    }
    return NULL;
}

Lista_Ptr_Exames destroiListaPtrExames(Lista_Ptr_Exames lst) {
    Lista_Ptr_Exames temp_ptr;
    while (lst) {
        temp_ptr = lst;
        lst = lst->next;
        free(temp_ptr);
    }
    return NULL;
}

/*Lista_Exames destroiListaExames(Lista_Exames lst) {
    Lista_Exames temp_ptr;
    while (lst) {
        temp_ptr = lst;
        lst = lst->next;
        temp_ptr->exame.salas = destroiListaSalas(temp_ptr->exame.salas);
        temp_ptr->exame.alunos = destroiListaPtrAlunos(temp_ptr->exame.alunos);
        free(temp_ptr);
    }
    return NULL;
}*/

void atribuiSalas(Lista_Exames exame) {
    Lista_Salas salas = exame->exame.salas;
    Lista_Salas ptr_s;
    Lista_Exames ptr_e;
    char *str = malloc(TAM_STR * sizeof(char));
    printf("Insira o nome da sala pretendida: \n");
    fflush(stdin);
    gets(str);
    int conflito = 0;
    for (ptr_e = exame->next; ptr_e && conflito == 0; ptr_e = ptr_e->next) {
        if (cmpData(ptr_e->exame.data, exame->exame.data))
            conflito = 1;
        else if (verifConflito(ptr_e->exame.hora, exame->exame.hora, ptr_e->exame.duracao, exame->exame.duracao) == 0)
            conflito = 1;
        else {
            for (ptr_s = ptr_e->exame.salas; ptr_s && conflito != 2; ptr_s = ptr_s->next) {
                if (strcmp(ptr_s->nome, str) == 0)
                    conflito = 2;
            }
        }
    }
    for (ptr_e = exame->prev; ptr_e && conflito == 0; ptr_e = ptr_e->prev) {
        if (cmpData(ptr_e->exame.data, exame->exame.data))
            conflito = 1;
        else if (verifConflito(ptr_e->exame.hora, exame->exame.hora, ptr_e->exame.duracao, exame->exame.duracao) == 0)
            conflito = 1;
        else {
            for (ptr_s = ptr_e->exame.salas; ptr_s && conflito != 2; ptr_s = ptr_s->next) {
                if (strcmp(ptr_s->nome, str) == 0)
                    conflito = 2;
            }
        }
    }
    if (conflito != 2) {
        salas = insereSala(salas, str);
        exame->exame.salas = salas;
    }
    else
        printf("Sala em conflito! Nao foi adicionada.\n");
    fflush(stdin);
}

Lista_Exames criaExame(Lista_Exames exames, Lista_Disciplinas *disciplinas) {
    Exame novo;
    Lista_Disciplinas disc = NULL;
    char *str = malloc(TAM_STR * sizeof(char));
    printf("Numero do exame: ");
    novo.num = p_scan_numExame(exames);
    printf("Disciplinas:\n");
    imprimeDisciplinas(*disciplinas);
    while (disc == NULL) {
        printf("Disciplina do exame: ");
        fflush(stdin);
        gets(str);
        disc = pesquisaDisciplinas(*disciplinas, str);
        if (disc)
            novo.disciplina = disc;
        else {
            char c;
            Disciplina d;
            printf("Disciplina nao existe na base de dados! Deseja cria-la [S/N]?");
            c = p_scan_char_cond("snSN");
            switch (c) {
                case 's':
                case 'S':
                    d.nome = str;
                    d.docente = malloc(TAM_STR * sizeof(char));
                    printf("Nome do docente: ");
                    p_scan_nome(d.docente);
                    *disciplinas = insereDisciplina(*disciplinas, d);
                    novo.disciplina = pesquisaDisciplinas(*disciplinas, str);
                    disc = *disciplinas;
                    break;
                case 'n':
                case 'N':
                    disc = NULL;
                    break;
                default:
                    break;
            }
        }
    }
    fflush(stdin);
    printf("Epoca(n -> Normal, \nr-> Recurso, \ne-> Especial): ");
    novo.epoca = p_scan_char_cond("nre");
    printf("Data do exame: ");
    novo.data = p_leData();
    printf("Hora do exame: ");
    novo.hora = p_leHora();
    printf("Duracao do exame(minutos): ");
    novo.duracao = p_scan_int();
    novo.salas = NULL;
    novo.alunos = NULL;
    exames = insereExame(exames, novo);
    return exames;
}

Lista_Salas eliminaSala(Lista_Salas lst, char *str) {
    Lista_Salas ant, act;
    procuraSala(lst, str, &ant, &act);
    if (act) {
        if (act->next)
            act->next->prev = ant;
        if (ant)
            ant->next = act->next;
        else
            lst = act->next;
        free(act->nome);
        free(act);

    }
    return lst;
}

Lista_Ptr_Exames eliminaPtrExame(Lista_Ptr_Exames lst, int num) {
    Lista_Ptr_Exames ant;
    Lista_Ptr_Exames exame = pesquisaNumPtrExame(lst, num);
    if (exame != NULL) {
        ant = exame->prev;
        if (exame->next != NULL)
            exame->next->prev = ant;
        if (ant != NULL)
            ant->next = exame->next;
        else
            lst = exame->next;
        free(exame);
    }
    return lst;
}

Lista_Exames eliminaExame(Lista_Exames lst, Lista_Exames exame) {
    Lista_Ptr_Alunos ptr;
    if (exame->next != NULL)
        exame->next->prev = exame->prev;
    if (exame->prev != NULL)
        exame->prev->next = exame->next;
    else
        lst = exame->next;
    for (ptr = exame->exame.alunos; ptr; ptr = ptr->next) {
        ptr->aluno->aluno.exames = eliminaPtrExame(ptr->aluno->aluno.exames, exame->exame.num);
    }
    exame->exame.salas = destroiListaSalas(exame->exame.salas);
    exame->exame.alunos = destroiListaPtrAlunos(exame->exame.alunos);
    free(ptr);
    return lst;
}

Lista_Exames eliminaExamesAntigos(Lista_Exames exames) {
    Lista_Exames ptr;
    Data data;
    printf("Por favor insira a data até onde quer eliminar (inclusive):\n");
    data = p_leData();
    ptr = exames;
    while(ptr){
        Lista_Exames ptr2 = ptr;
        ptr = ptr->next;
        if (cmpData(data, ptr->exame.data) >= 0) {
            exames = eliminaExame(exames, ptr2);
        }
    }
    return exames;
}

Lista_Exames moveExame(Lista_Exames lst, Lista_Exames exame){
    Lista_Exames ant, act;
    if (exame->prev)
        exame->prev->next = exame->next;
    else
        lst = exame->next;
    if (exame->next)
        exame->next->prev = exame->prev;
    procuraExame(lst, exame->exame, &ant, &act);
    if (ant) {
        exame->next = ant->next;
        exame->prev = ant;
        if (ant->next)
            ant->next->prev = exame;
        ant->next = exame;
    } else {
        if (lst)
            lst->prev = exame;
        exame->next = lst;
        exame->prev = NULL;
        lst = exame;
    }
    return lst;
}

void removeConflito(Lista_Exames exame) {
    Lista_Salas ptr, ptr_s;
    Lista_Exames ptr_e;
    int conflito;
    for (ptr = exame->exame.salas; ptr; ptr = ptr->next) {
        conflito = 0;
        for (ptr_e = exame->next; ptr_e && conflito == 0; ptr_e = ptr_e->next) {
            if (cmpData(ptr_e->exame.data, exame->exame.data))
                conflito = 1;
            else if (verifConflito(ptr_e->exame.hora, exame->exame.hora, ptr_e->exame.duracao, exame->exame.duracao) ==
                     0)
                conflito = 1;
            else {
                for (ptr_s = ptr_e->exame.salas; ptr_s && conflito != 2; ptr_s = ptr_s->next) {
                    if (strcmp(ptr_s->nome, ptr->nome) == 0)
                        conflito = 2;
                }
            }
        }
        if (conflito == 1)
            conflito = 0;
        for (ptr_e = exame->prev; ptr_e && conflito == 0; ptr_e = ptr_e->prev) {
            if (cmpData(ptr_e->exame.data, exame->exame.data))
                conflito = 1;
            else if (verifConflito(ptr_e->exame.hora, exame->exame.hora, ptr_e->exame.duracao, exame->exame.duracao) ==
                     0)
                conflito = 1;
            else {
                for (ptr_s = ptr_e->exame.salas; ptr_s && conflito != 2; ptr_s = ptr_s->next) {
                    if (strcmp(ptr_s->nome, ptr->nome) == 0)
                        conflito = 2;
                }
            }
        }
        if (conflito == 2) {
            printf("Sala %s em conflito removida.\n", ptr->nome);
            exame->exame.salas = eliminaSala(exame->exame.salas, ptr->nome);
        }
    }
}

Lista_Exames modificaExame(Lista_Exames lst, Lista_Disciplinas *disciplinas) {
    Lista_Exames exame;
    Lista_Disciplinas disc = NULL;
    char *str;
    int num, escolha = 0;
    if (lst == NULL) {
        printf("Nao ha exames na base de dados! Abortando...\n");
        return lst;
    }
    printf("Numero do exame a modificar: ");
    num = p_scan_int();
    exame = pesquisaNumExame(lst, num);
    while (exame == NULL) {
        printf("Nao existe exame com esse numero! Insira de novo: ");
        num = p_scan_int();
        exame = pesquisaNumExame(lst, num);
    }
    while (escolha != 7) {
        printf("\nModificar:\n1 - Numero\n2 - Disciplina\n3 - Epoca\n4 - Data/Hora\n5 - Hora\n6 - Duracao\n\n7 - Voltar\n\nEscolha a opcao: ");
        escolha = p_scan_int();
        fflush(stdin);
        switch (escolha) {
            case 1:
                printf("Numero do exame: ");
                exame->exame.num = p_scan_numExame(lst);
                break;
            case 2:
                str = malloc(TAM_STR * sizeof(char));
                printf("Disciplinas:\n");
                imprimeDisciplinas(*disciplinas);
                while (disc == NULL) {
                    printf("Disciplina do exame: ");
                    fflush(stdin);
                    gets(str);
                    disc = pesquisaDisciplinas(*disciplinas, str);
                    if (disc) {
                        free(str);
                        exame->exame.disciplina = disc;
                    } else {
                        char c;
                        Disciplina d;
                        printf("Disciplina nao existe na base de dados! Deseja cria-la? [S/N]");
                        c = p_scan_char_cond("snSN");
                        switch (c) {
                            case 's':
                            case 'S':
                                d.nome = str;
                                d.docente = malloc(TAM_STR * sizeof(char));
                                printf("Nome do docente: ");
                                p_scan_nome(d.docente);
                                *disciplinas = insereDisciplina(*disciplinas, d);
                                exame->exame.disciplina = pesquisaDisciplinas(*disciplinas, str);
                                disc = *disciplinas;
                                break;
                            case 'n':
                            case 'N':
                                disc = NULL;
                                break;
                            default:
                                break;
                        }
                    }
                }
                break;
            case 3:
                printf("Epoca(n -> Normal, \nr-> Recurso, \ne-> Especial): ");
                exame->exame.epoca = p_scan_char_cond("nre");
                break;
            case 4:
                printf("Data do exame: ");
                exame->exame.data = p_leData();
                lst = moveExame(lst, exame);
                removeConflito(exame);
                break;
            case 5:
                printf("Hora do exame: ");
                exame->exame.hora = p_leHora();
                lst = moveExame(lst, exame);
                removeConflito(exame);
                break;
            case 6:
                printf("Duracao do exame(minutos): ");
                exame->exame.duracao = p_scan_int();
                break;
            case 7:
                break;
            default:
                printf("Opcao invalida! Escolha outra opcao...\n");
                break;
        }
    }
    return lst;
}

void imprimeExame(Exame exame) {
    printf("Numero: %d\n", exame.num);
    printf("Disciplina: %s\n", exame.disciplina->disciplina.nome);
    printf("Epoca: ");
    switch (exame.epoca) {
        case 'n':
            printf("Normal\n");
            break;
        case 'r':
            printf("Recurso\n");
            break;
        case 'e':
            printf("Especial\n");
            break;
        default:
            printf("Epoca introduzida invalida! Modifique este exame!\n");
            break;
    }
    printf("Data: ");
    imprimeData(exame.data);
    printf("\nHora: ");
    imprimeHora(exame.hora);
    printf("\nDuracao: %d\n", exame.duracao);
}

void imprimeExames(Lista_Exames exames) {
    Lista_Exames ptr;
    for (ptr = exames; ptr; ptr = ptr->next) {
        imprimeExame(ptr->exame);
    }
}

void imprimeAlunosInscritos(Exame exame) {
    Lista_Ptr_Alunos ptr;
    for (ptr = exame.alunos; ptr; ptr = ptr->next) {
        printf("%ld - %s\n", ptr->aluno->aluno.num, ptr->aluno->aluno.nome);
    }
}

void imprimeExamesAluno(Aluno aluno) {
    Lista_Ptr_Exames ptr;
    for (ptr = aluno.exames; ptr; ptr = ptr->next) {
        imprimeExame(ptr->exame->exame);
        printf("\n");
    }
}

void imprimeSalas(Exame exame){
    Lista_Salas ptr;
    for(ptr = exame.salas; ptr && ptr->next; ptr = ptr->next){
        printf("%s, ",ptr->nome);
    }
    if (exame.salas)
        printf("%s\n", ptr->nome);
}

void inscreveAluno(Lista_Exames exames, Lista_Alunos alunos) {
    int num;
    Lista_Exames exame, a;
    Lista_Alunos aluno;
    imprimeExames(exames);
    printf("Numero do exame: ");
    while (scanf("%d", &num) == 0)
        printf("Insira um NUMERO: ");
    while (pesquisaNumExame(exames, num) == NULL) {
        printf("Nao existe exame na base de dados com esse numero!\n");
        printf("Numero do exame: ");
        while (scanf("%d", &num) == 0)
            printf("Insira um NUMERO: ");
    }
    exame = pesquisaNumExame(exames, num);
    imprimeAlunos(alunos);
    printf("Numero do aluno a inscrever: ");
    while (scanf("%d", &num) == 0)
        printf("Insira um NUMERO: ");
    while (pesquisaNumAluno(alunos, num) == NULL) {
        printf("Nao existe aluno na base de dados com esse numero!\n");
        printf("Numero do aluno a inscrever: ");
        while (scanf("%d", &num) == 0)
            printf("Insira um NUMERO: ");
    }
    aluno = pesquisaNumAluno(alunos, num);
    if (exame->exame.epoca == 'e' && (((aluno->aluno.regime == 'n') && (aluno->aluno.ano != 3)) || (aluno->aluno.regime == 'e'))) {
        printf("O aluno referido nao tem acesso a epoca deste exame! Abortando...");
        return;
    }
    a = exame->next;
    aluno->aluno.exames = inserePtrExame(aluno->aluno.exames, exame); //
    exame->exame.alunos = inserePtrAluno(exame->exame.alunos, aluno);
    exame->next = a;
}

void removeInscricao(Lista_Exames exames) {
    int num_e, num_a;
    Lista_Exames exame;
    Lista_Ptr_Alunos aluno;
    imprimeExames(exames);
    printf("Numero do exame: ");
    while (scanf("%d", &num_e) == 0)
        printf("Insira um NUMERO: ");
    while (pesquisaNumExame(exames, num_e) == NULL) {
        printf("Nao existe exame na base de dados com esse numero!\n");
        printf("Numero do exame: ");
        while (scanf("%d", &num_e) == 0)
            printf("Insira um NUMERO: ");
    }
    exame = pesquisaNumExame(exames, num_e);
    printf("Exame escolhido: \n\n");
    imprimeExame(exame->exame);
    printf("Alunos inscritos:\n");
    imprimeAlunosInscritos(exame->exame);
    printf("\nNumero do aluno a desinscrever: ");
    while (scanf("%d", &num_a) == 0)
        printf("Insira um NUMERO: ");
    while (pesquisaNumPtrAluno(exame->exame.alunos, num_a) == NULL) {
        printf("Nao existe aluno na base de dados com esse numero!\n");
        printf("Numero do aluno a desinscrever: ");
        while (scanf("%d", &num_a) == 0)
            printf("Insira um NUMERO: ");
    }
    aluno = pesquisaNumPtrAluno(exame->exame.alunos, num_a);
    aluno->aluno->aluno.exames = eliminaPtrExame(aluno->aluno->aluno.exames, num_e);
    exame->exame.alunos = eliminaPtrAluno(exame->exame.alunos, num_a);
}

void verificaSalasSuficientes(Lista_Exames exames) {
    Lista_Exames ptr = exames;
    Lista_Ptr_Alunos ptr_alunos;
    int exame, extra, resto;
    int inscricoes = 0;
    int salas = 0;
    printf("Insira o numero do exame a verificar:\n");
    while (scanf("%d", &exame) == 0)
        printf("Por favor insira um NUMERO:\n");
    while (ptr->exame.num != exame)
        ptr = ptr->next;
    for (ptr_alunos = ptr->exame.alunos; ptr_alunos != NULL; ptr_alunos = ptr_alunos->next) {
        inscricoes++;
    }
    while (ptr->exame.salas != NULL) {
        salas++;
        ptr->exame.salas = ptr->exame.salas->next;
    }
    if (salas * 30 < inscricoes) {
        extra = (inscricoes - salas * 30) / 30;
        resto = (inscricoes - salas * 30) % 30;
        if (resto > 0)
            extra++;
        printf("Nao ha salas suficientes! Por favor acrescente mais %d salas\n", extra);
    } else
        printf("Estao atribuidas salas suficientes para o numero de inscritos.\n");
}
