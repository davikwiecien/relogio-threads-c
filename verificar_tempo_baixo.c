#include "verificar_tempo_baixo.h"

void *verificar_tempo_baixo(void *arg) {

    struct tm *dados_tempo = (struct tm*)(arg);

    while(1) {
        if(dados_tempo->tm_sec < 0)
               arrumar_tempo_baixo(60, &(dados_tempo->tm_sec), &(dados_tempo->tm_min));
        if(dados_tempo->tm_min < 0)
               arrumar_tempo_baixo(60, &(dados_tempo->tm_min), &(dados_tempo->tm_hour));
        if(dados_tempo->tm_hour < 0)
               arrumar_tempo_baixo(24, &(dados_tempo->tm_hour), NULL);
    }

}
