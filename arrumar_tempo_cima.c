#include "arrumar_tempo_cima.h"

void arrumar_tempo_cima(int tempo_base, int *tempo_1, int *tempo_2) {

    int div = *tempo_1 / tempo_base;
    int dif = *tempo_1 - (tempo_base * div);
    *tempo_1 = dif;

    if(tempo_base != 24)
        *tempo_2 += div;

    return;

}
