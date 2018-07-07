#include "Protecoes.h"
#include "Estruturas.h"

long p_scan_int() {
    long num;
    int s_check, test = 0;
    fflush(stdin);
    s_check = scanf("%10lu", &num);
    test = getchar();
    fflush(stdin);
    while (s_check == 0 || test != '\n') {
        printf("Insira um NUMERO: ");
        s_check = scanf("%10lu", &num);
        test = getchar();
        fflush(stdin);
    }
    return num;
}

long p_scan_numAluno(Lista_Alunos alunos) {
    long num;
    int s_check, test = 0;
    Lista_Alunos e_check;
    fflush(stdin);
    s_check = scanf("%10lu", &num);
    test = getchar();
    e_check = pesquisaNumAluno(alunos, num);
    fflush(stdin);
    while (s_check == 0 || e_check || test != '\n') {
        if (s_check == 0 || test != '\n')
            printf("Insira um NUMERO: ");   //  ESTA PROTECAO JÁ FUNCIONA :O
        else if (e_check)
            printf("Ja existe um aluno com esse numero! Insira outro: ");
        s_check = scanf("%10lu", &num);
        test = getchar();
        e_check = pesquisaNumAluno(alunos, num);
        fflush(stdin);
    }
    return num;
}

int p_scan_numExame(Lista_Exames exames) {
    int num;
    int s_check, test = 0;
    Lista_Exames e_check;
    fflush(stdin);
    s_check = scanf("%9u", &num);
    test = getchar();
    e_check = pesquisaNumExame(exames, num);
    fflush(stdin);
    while (s_check == 0 || e_check || test != '\n') {
        if (s_check == 0 || test != '\n')
            printf("Insira um NUMERO: ");   //  ESTA PROTECAO JÁ FUNCIONA :O
        else if (e_check)
            printf("Ja existe um exame com esse numero! Insira outro: ");
        s_check = scanf("%9u", &num);
        test = getchar();
        e_check = pesquisaNumExame(exames, num);
        fflush(stdin);
    }
    return num;
}

void p_scan_nome(char *str) {
    int is_num = 1;
    fflush(stdin);
    gets(str);
    fflush(stdin);
    for (int i = 0; *(str + i) && is_num; i++)
        is_num = ((*(str + i) > 'z' || *(str + i) < 'A' || (*(str + i) > 'Z' && *(str + i) < 'a')) && *(str + i) != ' ')
                 ? 0 : 1;
    while (is_num == 0) {
        printf("O nome nao pode conter simbolos. Insira de novo: ");
        gets(str);
        fflush(stdin);
        is_num = 1;
        for (int i = 0; *(str + i) && is_num; i++) {
            is_num = ((*(str + i) > 'z' || *(str + i) < 'A' || (*(str + i) > 'Z' && *(str + i) < 'a')) &&
                      *(str + i) != ' ') ? 0 : 1;
        }
    }
}

/*char p_scan_char() {
    char ch;
    int test = 0;
    fflush(stdin);
    scanf("%c", &ch);
    test = getchar();
    fflush(stdin);
    while (test != '\n') {
        printf("Insira 1 carater: ");
        sscanf("%d", &ch);
        test = getchar();
        fflush(stdin);
    }
    return ch;
}*/

char p_scan_char_cond(char *alpha) {
    char ch;
    int test = 0, check = 0;
    fflush(stdin);
    scanf("%c", &ch);
    test = getchar();
    for (int i = 0; *(alpha + i) && check == 0; i++) {
        check = (*(alpha + i) == ch);
    }
    fflush(stdin);
    while (test != '\n' || check == 0) {
        if (*(alpha + 1)) {
            int i;
            printf("Insira ");
            for (i = 0; *(alpha + i + 1); i++) {
                printf("'%c', ", *(alpha + i));
            }
            printf("ou '%c': ", *(alpha + i));
        } else
            printf("Insira '%c': ", *alpha);
        scanf("%c", &ch);
        test = getchar();
        fflush(stdin);
        for (int i = 0; *(alpha + i) && check == 0; i++) {
            check = (*(alpha + i) == ch);  //n funciona
        }
    }
    return ch;
}

Data p_leData() {
    int s_check, test = 0, format = 0;
    Data data;
    fflush(stdin);
    s_check = scanf("%2u/%2u/%4u", &data.dia, &data.mes, &data.ano);
    test = getchar();
    if (s_check == 3 && test == '\n')
        format = (data.dia > 31 || data.dia < 0 || data.mes > 12 || data.mes < 0 || data.ano < 0) ? 1 : 0;
    fflush(stdin);
    while (s_check != 3 || test != '\n' || format) {
        printf("Insira a data valida no formato 'dd/mm/aaaa': ");
        s_check = scanf("%2u/%2u/%4u", &data.dia, &data.mes, &data.ano);
        test = getchar();
        if (s_check == 3 && test == '\n')
            format = (data.dia > 31 || data.dia < 0 || data.mes > 12 || data.mes < 0 || data.ano < 0) ? 1 : 0;
        fflush(stdin);
    }
    return data;
}

Hora p_leHora() {
    int s_check, test = 0, format = 0;
    Hora hora;
    fflush(stdin);
    s_check = scanf("%2u:%2u", &hora.horas, &hora.minutos);
    test = getchar();
    if (s_check == 2 && test == '\n')
        format = (hora.horas > 23 || hora.horas < 0 || hora.minutos > 59 || hora.minutos < 0) ? 1 : 0;
    fflush(stdin);
    while (s_check != 2 || test != '\n' || format) {
        printf("Insira uma hora valida no formato 'hh:mm': ");
        s_check = scanf("%2u:%2u", &hora.horas, &hora.minutos);
        test = getchar();
        if (s_check == 2 && test == '\n')
            format = (hora.horas > 23 || hora.horas < 0 || hora.minutos > 59 || hora.minutos < 0) ? 1 : 0;
        fflush(stdin);
    }
    return hora;
}