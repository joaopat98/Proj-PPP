//
// Created by guilh on 01/05/2017.
//

#include "Menus.h"

void menuAlunos(Lista_Alunos *alunos) {
    int opcao = 0;
    int num;
    Lista_Alunos aluno;
    while (1) {
        printf("Gestao de alunos \n Insira o numero da opcao desejada:\n");
        printf("1 - Adicionar aluno\n");
        printf("2 - Modificar aluno\n");
        printf("3 - Eliminar aluno\n");
        printf("4 - Listar exames do aluno\n");
        printf("5 - Listar todos os alunos\n");
        printf("6 - Voltar\n");
        opcao = p_scan_int();
        while (opcao < 1 || opcao > 6) {
            printf("Por favor, insira o numero da operacao desejada (de 1 a 6):");
            opcao = p_scan_int();
        }
        switch (opcao) {
            case 1:
                *alunos = criaAluno(*alunos);
                break;
            case 2:
                *alunos = modificaAluno(*alunos);
                break;
            case 3:
                *alunos = eliminaAluno(*alunos);
                break;
            case 4:
                if (*alunos == NULL) {
                    printf("Nao ha alunos na base de dados! Abortando...\n");
                    break;
                }
                printf("Numero do aluno: ");
                num = p_scan_int();
                aluno = pesquisaNumAluno(*alunos, num);
                while (aluno == NULL) {
                    printf("Nao existe aluno com esse numero! Insira de novo: ");
                    num = p_scan_int();
                    aluno = pesquisaNumAluno(*alunos, num);
                }
                imprimeExamesAluno(aluno->aluno);
                break;
            case 5:
                imprimeAlunos(*alunos);
                break;
            case 6:
                return;
            default:
                break;
        }
    }
}

void menuDisciplinas(Lista_Disciplinas *disciplinas, Lista_Exames *exames) {
    int opcao;
    while (1) {
        printf("Gestao de disciplinas \n Insira o numero da opcao desejada:\n");
        printf("1 - Adicionar disciplina\n");
        printf("2 - Modificar disciplina\n");
        printf("3 - Eliminar disciplina\n");
        printf("4 - Listar todas as disciplinas\n");
        printf("5 - Voltar\n");
        opcao = p_scan_int();
        while (opcao < 1 || opcao > 5) {
            printf("Por favor, insira o numero da operacao desejada (de 1 a 5):");
            opcao = p_scan_int();
        }
        switch (opcao) {
            case 1:
                *disciplinas = criaDisciplina(*disciplinas);
                break;
            case 2:
                modificaDisciplina(*disciplinas);
                break;
            case 3:
                *disciplinas = eliminaDisciplina(*disciplinas, exames);
                break;
            case 4:
                imprimeDisciplinas(*disciplinas);
                break;
            case 5:
                return;
            default:
                break;
        }
    }
}

void menuSalas(Lista_Exames exames) {
    int opcao;
    int num;
    char *str = malloc(TAM_STR * sizeof(char));
    Lista_Exames exame = NULL;
    Lista_Salas ant, act;
    while (1) {
        printf("Gestao de salas \n Por favor insira a opcao desejada:\n");
        printf("1 - Atribuir salas a exame\n");
        printf("2 - Remover sala de um exame\n");
        printf("3 - Listar salas de um exame\n");
        printf("4 - Verificar salas suficientes\n");
        printf("5 - Voltar\n");
        opcao = p_scan_int();
        while (opcao < 1 || opcao > 5) {
            printf("Por favor, insira o numero da operacao desejada (de 1 a 5):");
            opcao = p_scan_int();
        }
        switch (opcao) {
            case 1:
                if (exames == NULL)
                    printf("Nao ha exames! Abortando...");
                else {
                    imprimeExames(exames);
                    printf("Numero do exame: ");
                    num = p_scan_int();
                    exame = pesquisaNumExame(exames, num);
                    while (exame == NULL) {
                        printf("Nao existe exame com esse numero! Insira de novo: ");
                        num = p_scan_int();
                        exame = pesquisaNumExame(exames, num);
                    }
                    imprimeSalas(exame->exame);
                    atribuiSalas(exame);
                    exame = NULL;
                }
                break;
            case 2:
                if (exames == NULL)
                    printf("Nao ha exames! Abortando...");
                else {
                    imprimeExames(exames);
                    printf("Numero do exame: ");
                    num = p_scan_int();
                    exame = pesquisaNumExame(exames, num);
                    while (exame == NULL) {
                        printf("Nao existe exame com esse numero! Insira de novo: ");
                        num = p_scan_int();
                        exame = pesquisaNumExame(exames, num);
                    }
                    imprimeSalas(exame->exame);
                    printf("Nome da sala a remover: ");
                    fflush(stdin);
                    gets(str);
                    fflush(stdin);
                    procuraSala(exame->exame.salas, str, &ant, &act);
                    while (act == NULL) {
                        printf("Essa sala nao esta atribuida a este exame, insira de novo: ");
                        gets(str);
                        fflush(stdin);
                        procuraSala(exame->exame.salas, str, &ant, &act);
                    }
                    exame->exame.salas = eliminaSala(exame->exame.salas, str);
                    exame = NULL;
                }
                break;
            case 3:
                if (exames == NULL)
                    printf("Nao ha exames! Abortando...");
                else {
                    imprimeExames(exames);
                    printf("Numero do exame: ");
                    num = p_scan_int();
                    exame = pesquisaNumExame(exames, num);
                    while (exame == NULL) {
                        printf("Nao existe exame com esse numero! Insira de novo: ");
                        num = p_scan_int();
                        exame = pesquisaNumExame(exames, num);
                    }
                    imprimeSalas(exame->exame);
                    exame = NULL;
                }
                break;
            case 4:
                imprimeExames(exames);
                verificaSalasSuficientes(exames);
                break;
            case 5:
                return;
            default:
                break;

        }
    }
}

void menuInscricoes(Lista_Exames exames, Lista_Alunos alunos) {
    int opcao;
    Lista_Exames exame;
    while (1) {
        printf("Gestao de inscricoes \n Por favor insira a opcao desejada:\n");
        printf("1 - Adicionar aluno a exame\n");
        printf("2 - Remover aluno de exame\n");
        printf("3 - Voltar\n");
        opcao = p_scan_int();
        while (opcao < 1 || opcao > 3) {
            printf("Por favor, insira o numero da operacao desejada (de 1 a 3):");
            opcao = p_scan_int();
        }
        switch (opcao) {
            case 1:
                inscreveAluno(exames, alunos);
                break;
            case 2:
                removeInscricao(exames);
                break;
            case 3:
                return;
            default:
                break;
        }
    }
}

void menuExames(Lista_Alunos alunos, Lista_Exames *exames, Lista_Disciplinas *disciplinas) {
    int opcao = 0, num;
    Lista_Exames exame;
    while (1) {
        printf("Gestao de exames \n Insira o numero da opcao desejada:\n");
        printf("1 - Criar exame\n");
        printf("2 - Modificar exame\n");
        printf("3 - Configurar salas\n");
        printf("4 - Eliminar exame\n");
        printf("5 - Eliminar exames realizados\n");
        printf("6 - Listar exames\n");
        printf("7 - Gerir inscricoes de alunos\n");
        printf("8 - Listar alunos inscritos em exame\n");
        printf("9 - Voltar\n");
        opcao = p_scan_int();
        while (opcao < 1 || opcao > 9) {
            printf("Por favor, insira o numero da operacao desejada (de 1 a 9):");
            opcao = p_scan_int();
        }
        switch (opcao) {
            case 1:
                *exames = criaExame(*exames, disciplinas);
                break;
            case 2:
                imprimeExames(*exames);
                *exames = modificaExame(*exames, disciplinas);
                break;
            case 3:
                menuSalas(*exames);
                break;
            case 4:
                if (*exames == NULL)
                    printf("Nao ha exames para eliminar! Abortando...");
                else {
                    imprimeExames(*exames);
                    printf("Numero do exame a eliminar: ");
                    num = p_scan_int();
                    exame = pesquisaNumExame(*exames, num);
                    while (exame == NULL) {
                        printf("Nao existe exame com esse numero! Insira de novo: ");
                        num = p_scan_int();
                        exame = pesquisaNumExame(*exames, num);
                    }
                    *exames = eliminaExame(*exames, exame);
                }
                break;
            case 5:
                *exames = eliminaExamesAntigos(*exames);
                break;
            case 6:
                imprimeExames(*exames);
                break;
            case 7:
                menuInscricoes(*exames, alunos);
                break;
            case 8:
                imprimeExames(*exames);
                if (*exames == NULL) {
                    printf("Nao ha exames na base de dados! Abortando...\n");
                    break;
                }
                printf("Insira o numero do exame que pretende ver:\n");
                num = p_scan_int();
                exame = pesquisaNumExame(*exames, num);
                while (exame == NULL) {
                    printf("Nao existe exame com esse numero! Insira de novo: ");
                    num = p_scan_int();
                    exame = pesquisaNumExame(*exames, num);
                }
                imprimeAlunosInscritos(exame->exame);
                break;
            case 9:
                return;
            default:
                break;
        }
    }
}

void menuPrincipal(Lista_Alunos *alunos, Lista_Exames *exames, Lista_Disciplinas *disciplinas) {
    int opcao;
    do {
        printf("Bem vindo ao gestor de exames do DEI. \n Por favor insira a opcao desejada:\n");
        printf("1 - Gerir alunos\n");
        printf("2 - gerir disciplinas\n");
        printf("3 - Gerir exames\n");
        printf("4 - Sair\n");
        opcao = p_scan_int();
        while (opcao < 1 || opcao > 4) {
            printf("Por favor, insira o numero da operacao desejada (de 1 a 4):");
            opcao = p_scan_int();
        }
        switch (opcao) {
            case 1:
                menuAlunos(alunos);
                break;
            case 2:
                menuDisciplinas(disciplinas, exames);
                break;
            case 3:
                menuExames(*alunos, exames, disciplinas);
                break;
            case 4:
                return;
            default:
                break;
        }
    } while (1);
}