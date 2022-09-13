#include "visualizar_tempo.h"

void visualizar_tempo(info_tempo *tempo) {

    strftime(tempo->str, (size_t)10, "%H:%M:%S", &(tempo->dados_tempo));
    printf("Horário: %s\n", tempo->str);

    return;

}
