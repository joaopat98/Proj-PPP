#include <stdio.h>
#include "Source Files/Menus.h"
#include "Source Files/Ficheiros.h"

int main() {
    FILE *f_exames;
    FILE *f_alunos;
    FILE *f_disciplinas;
    Lista_Exames exames = NULL;
    Lista_Alunos alunos = NULL;
    Lista_Disciplinas disciplinas = NULL;
    f_exames = fopen("Exames.txt","r");
    f_alunos = fopen("Alunos.txt","r");
    f_disciplinas = fopen("Disciplinas.txt","r");
    if (f_exames == NULL || f_alunos == NULL || f_disciplinas == NULL) {
        printf("Erro. Nao foi possivel aceder aos dados. Pressione enter para sair");
        if (getc(stdin))
            return -1;
    }
    leFicheiroDisciplinas(&disciplinas,f_disciplinas);
    leFicheiroAlunos(&alunos,f_alunos);
    leFicheiroExames(&exames,f_exames,disciplinas,alunos);
    fclose(f_disciplinas);
    fclose(f_alunos);
    fclose(f_exames);
    menuPrincipal(&alunos, &exames, &disciplinas);
    f_exames = fopen("Exames.txt","w");
    guardaFicheiroExames(exames,f_exames);
    fclose(f_exames);
    f_alunos = fopen("Alunos.txt","w");
    guardaFicheiroAlunos(alunos,f_alunos);
    fclose(f_alunos);
    f_disciplinas = fopen("Disciplinas.txt","w");
    guardaFicheiroDisciplinas(disciplinas,f_disciplinas);
    fclose(f_disciplinas);
    return 0;
}