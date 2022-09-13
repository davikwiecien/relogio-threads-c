#include "arrumar_tempo_baixo.h"

void arrumar_tempo_baixo(int tempo_base, int *tempo_1, int *tempo_2) {

    *tempo_1 = -(*tempo_1);
    int div = *tempo_1 / tempo_base;
    int dif = (tempo_base * (div + 1)) - *tempo_1;
    *tempo_1 = dif;

    if(tempo_base != 24)
         *tempo_2 -= (dif == 0) ? div : div + 1;

    return;

}

