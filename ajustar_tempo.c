#include "ajustar_tempo.h"

void ajustar_tempo(struct tm *dados_tempo) {

    printf("Informe um novo horário (hh:mm:ss): ");
    scanf("%d:%d:%d", &(dados_tempo->tm_hour), &(dados_tempo->tm_min),
        &(dados_tempo->tm_sec));

    return;

}
