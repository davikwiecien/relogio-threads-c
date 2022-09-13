#include "definir_alarme.h"

void *definir_alarme(void *arg) {

    char aviso_alarme[10];
    info_alarme *alarme = (info_alarme*)(arg);

    strftime(aviso_alarme, (size_t)10, "%H:%M:%S", alarme->dados_tempo_a);
    while(1) {

        if((alarme->dados_tempo_a->tm_hour == alarme->dados_tempo_h->tm_hour) &&
            (alarme->dados_tempo_a->tm_min == alarme->dados_tempo_h->tm_min) &&
            (alarme->dados_tempo_a->tm_sec == alarme->dados_tempo_h->tm_sec)) {

            printf("\n\nAlarme %s %c\nContinue escrevendo abaixo:\n\n", aviso_alarme, 7);

        }

        sleep(1);

    }

}
