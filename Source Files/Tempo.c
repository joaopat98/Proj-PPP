#include "Tempo.h"

int cmpData(Data d1, Data d2) {
    if (d1.ano < d2.ano)
        return -1;
    else if (d1.ano > d2.ano)
        return 1;
    if (d1.mes < d2.mes)
        return -1;
    else if (d1.mes > d2.mes)
        return 1;
    if (d1.dia < d2.dia)
        return -1;
    else if (d1.dia > d2.dia)
        return 1;
    return 0;
}

int cmpHora(Hora h1, Hora h2) {
    if (h1.horas < h2.horas)
        return -1;
    else if (h1.horas > h2.horas)
        return 1;
    if (h1.minutos < h2.minutos)
        return -1;
    else if (h1.minutos > h2.minutos)
        return 1;
    return 0;
}

Hora adicionaMinutos(Hora h, int minutos) {
    h.horas += minutos / 60;
    h.minutos += minutos % 60;
    return h;
}

int verifConflito(Hora h1, Hora h2, int dur1, int dur2) {
    Hora fim1 = adicionaMinutos(h1, dur1), fim2 = adicionaMinutos(h2, dur2);
    if (cmpHora(fim1, h2) <= 0 || cmpHora(fim2, h1) <= 0)
        return 0;
    return 1;
}

/*Data leData() {
    Data d;
    scanf("%d/%d/%d", &d.dia, &d.mes, &d.ano);
    return d;
}

Hora leHora() {
    Hora h;
    scanf("%d:%d", &h.horas, &h.minutos);
    return h;
}*/

void imprimeData(Data d) {
    printf("%d/%d/%d", d.dia, d.mes, d.ano);
}

void imprimeHora(Hora h) {
    printf("%d:%02d", h.horas, h.minutos);
}