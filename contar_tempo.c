#include "contar_tempo.h"

void *contar_tempo(void *arg)  {

    struct tm *dados_tempo = (struct tm*)(arg);
    pthread_t thread_verifica_cima;
    pthread_t thread_verifica_baixo;

    pthread_create(&thread_verifica_cima, NULL, verificar_tempo_cima, dados_tempo);
    pthread_create(&thread_verifica_baixo, NULL, verificar_tempo_baixo, dados_tempo);

    while(1) {
        sleep(1);
        ++(dados_tempo->tm_sec);
    }

}
