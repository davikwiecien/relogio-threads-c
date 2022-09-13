#include "verificar_tempo_cima.h"

void *verificar_tempo_cima(void *arg) {

    struct tm *dados_tempo = (struct tm*)(arg);

    while(1) {
        if(dados_tempo->tm_sec >= 60)
            arrumar_tempo_cima(60, &(dados_tempo->tm_sec), &(dados_tempo->tm_min));
        if(dados_tempo->tm_min >= 60)
            arrumar_tempo_cima(60, &(dados_tempo->tm_min), &(dados_tempo->tm_hour));
        if(dados_tempo->tm_hour >= 24)
            arrumar_tempo_cima(24, &(dados_tempo->tm_hour), NULL);
    }

}
