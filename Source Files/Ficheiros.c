//
// Created by guilh on 23/05/2017.
//
#include "Ficheiros.h"

void leFicheiroDisciplinas(Lista_Disciplinas *disciplinas, FILE *fich_disc){
    char *ptr = NULL;
    int in;
    char *nome;
    char *docente = (char *) malloc(TAM_STR * sizeof(char));
    nome = malloc(TAM_STR * sizeof(char));
    while (fgets(nome, TAM_STR, fich_disc) && fgets(docente, TAM_STR, fich_disc)) {
        in = 1;
        for(ptr = nome; in; ptr++){
            if(*ptr == '\n'){
                *ptr = '\0';
                in = 0;
            }
        }
        in = 1;
        for(ptr = docente; in; ptr++){
            if(*ptr == '\n'){
                *ptr = '\0';
                in = 0;
            }
        }
        Disciplina disc;
        disc.nome = malloc(TAM_STR * sizeof(char));
        disc.docente = malloc(TAM_STR * sizeof(char));
        strcpy(disc.nome, nome);
        strcpy(disc.docente, docente);
        *disciplinas = insereDisciplina(*disciplinas, disc);
    }
}

void leFicheiroAlunos(Lista_Alunos *alunos, FILE *fich_aln){
    char *str1 = malloc(TAM_STR * sizeof(char));
    char *str2 = malloc(TAM_STR * sizeof(char));
    int numero, ano;
    char regime;
    while (fscanf(fich_aln, "%[^\n]\n%[^\n]\n%d\n%d\n%c\n", str1, str2, &numero, &ano, &regime) == 5) {
        Aluno aln;
        aln.nome = malloc(TAM_STR * sizeof(char));
        aln.curso = malloc(TAM_STR * sizeof(char));
        strcpy(aln.nome, str1);
        //printf("%s\n", aln.nome);
        strcpy(aln.curso, str2);
        //printf("%s\n", aln.curso);
        aln.num = numero;
        //printf("%d\n", numero);
        aln.ano = ano;
        //printf("%d\n", ano);
        aln.regime = regime;
        //printf("%c\n", regime);
        aln.exames = NULL;
        *alunos = insereAluno(*alunos, aln);
    }
}

void leFicheiroExames(Lista_Exames *exames, FILE *fich_exm, Lista_Disciplinas disciplinas, Lista_Alunos alunos){
    Lista_Ptr_Alunos ptr_aln;
    Lista_Exames ptr_exm;
    char epoca;
    Data data;
    Hora hora;
    int num;
    int duracao;
    Lista_Salas salas = malloc(sizeof(Lista_Salas));
    Lista_Ptr_Alunos alns = malloc(sizeof(Lista_Ptr_Alunos));
    char *linha = malloc(TAM_STR * sizeof(char));
    while (fscanf(fich_exm, "%d\n%d\n%c\n%d/%d/%d\n%d:%d\n%[^\n]\n", &num, &duracao, &epoca, &data.dia, &data.mes, &data.ano, &hora.horas, &hora.minutos, linha) == 9) {
        Exame exm;
        exm.num = num;
        exm.disciplina = pesquisaDisciplinas(disciplinas, linha);
        exm.alunos = alns;
        exm.salas = salas;
        exm.epoca = epoca;
        exm.data = data;
        exm.duracao = duracao;
        exm.hora = hora;
        exm.salas = NULL;
        exm.alunos = NULL;
        while(fscanf(fich_exm, "%[^\n]\n",linha) && *linha != '/') {
            exm.salas = insereSala(exm.salas, linha);
        }
        while(fscanf(fich_exm,"%d\n", &num) == 1, num)
            exm.alunos = inserePtrAluno(exm.alunos, pesquisaNumAluno(alunos, num));
        *exames = insereExame(*exames, exm);
        ptr_exm = pesquisaNumExame(*exames, exm.num);
        for (ptr_aln = ptr_exm->exame.alunos; ptr_aln; ptr_aln = ptr_aln->next) {
            ptr_aln->aluno->aluno.exames = inserePtrExame(ptr_aln->aluno->aluno.exames, ptr_exm);
        }
    }
}

void guardaFicheiroDisciplinas(Lista_Disciplinas disciplinas, FILE *fich_disc){
    for (disciplinas;disciplinas != NULL; disciplinas = disciplinas->next) {
        fprintf(fich_disc,"%s\n",disciplinas->disciplina.nome);
        fprintf(fich_disc,"%s\n",disciplinas->disciplina.docente);
    }
}

void guardaFicheiroAlunos(Lista_Alunos alunos, FILE *fich_aln){
    for (alunos; alunos != NULL ; alunos = alunos->next) {
        fprintf(fich_aln,"%s\n",alunos->aluno.nome);
        fprintf(fich_aln,"%s\n",alunos->aluno.curso);
        fprintf(fich_aln,"%ld\n",alunos->aluno.num);
        fprintf(fich_aln,"%ld\n",alunos->aluno.ano);
        fprintf(fich_aln,"%c\n",alunos->aluno.regime);
    }
}

void guardaFicheiroExames(Lista_Exames exames, FILE *fich_exms){
    Lista_Salas ptr_s;
    Lista_Ptr_Alunos ptr_aln;
    Lista_Exames ptr_exm;
    for (ptr_exm = exames; ptr_exm; ptr_exm = ptr_exm->next) {
        fprintf(fich_exms,"%d\n",ptr_exm->exame.num);
        fprintf(fich_exms,"%d\n",ptr_exm->exame.duracao);
        fprintf(fich_exms,"%c\n",ptr_exm->exame.epoca);
        fprintf(fich_exms,"%d/%d/%d\n",ptr_exm->exame.data.dia, ptr_exm->exame.data.mes, ptr_exm->exame.data.ano);
        fprintf(fich_exms,"%d:%d\n",ptr_exm->exame.hora.horas, ptr_exm->exame.hora.minutos);
        fprintf(fich_exms,"%s\n",ptr_exm->exame.disciplina->disciplina.nome);
        ptr_s = exames->exame.salas;
        while (ptr_s) {
            fprintf(fich_exms,"%s\n",ptr_s->nome);
            ptr_s = ptr_s->next;
        }
        fprintf(fich_exms,"/\n");
        ptr_aln = exames->exame.alunos;
        while (ptr_aln) {
            fprintf(fich_exms,"%ld\n",ptr_aln->aluno->aluno.num);
            ptr_aln = ptr_aln->next;
        }
        fprintf(fich_exms, "0\n");
    }
}