#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <stdio_ext.h>
#include "ajustar_tempo.h"
#include "contar_tempo.h"
#include "definir_alarme.h"
#include "info_alarme.h"
#include "info_tempo.h"
#include "menu.h"
#include "visualizar_tempo.h"

#define CLEAR printf("\033[H\033[2J\033[3J")

int main(void) {

    time_t tempo;
    struct tm *ptr_info_tempo;
    unsigned short op;
    bool flag_cronometro = false, flag_alarme = false;
    pthread_t thread_horario, thread_cronometro, thread_alarme;

    info_tempo *h = malloc(sizeof *h);
    info_tempo *c = calloc(1, sizeof *c);
    info_tempo *a = calloc(1, sizeof *a);

    info_alarme *alarme = calloc(1, sizeof *alarme);
    alarme->dados_tempo_h = &(h->dados_tempo);
    alarme->dados_tempo_a = &(a->dados_tempo);

    time(&tempo);
    ptr_info_tempo = localtime(&tempo);
    h->dados_tempo = *ptr_info_tempo;
    strftime(c->str, (size_t)10, "%H:%M:%S", &(c->dados_tempo));
    strftime(a->str, (size_t)10, "%H:%M:%S", &(a->dados_tempo));

    pthread_create(&thread_horario, NULL, contar_tempo, &(h->dados_tempo));

    do {

        menu();
        scanf("%hu", &op);

        CLEAR;
        switch(op) {

            case 0:
                puts("Até mais!");
                return EXIT_SUCCESS;

            case 1:
                ajustar_tempo(&(h->dados_tempo));
                break;

            case 2:
                visualizar_tempo(h);
                break;

            case 3:

                if(!flag_cronometro) {
                    pthread_create(&thread_cronometro, NULL, contar_tempo, &(c->dados_tempo));
                    strftime(c->str, (size_t)10, "%H:%M:%S", &(c->dados_tempo));
                }

                printf("Cronômetro %siniciado! (em %s)\n", (flag_cronometro) ? "já " : "", c->str);
                flag_cronometro = true;

                break;

            case 4:

                if(flag_cronometro) {
                    pthread_cancel(thread_cronometro);
                    strftime(c->str, (size_t)10, "%H:%M:%S", &(c->dados_tempo));
                }

                printf("Cronômetro %sparado! (em %s)\n", (flag_cronometro) ? "" : "já ", c->str);
                flag_cronometro = false;

                break;

            case 5:

                c->dados_tempo.tm_hour = c->dados_tempo.tm_min = c->dados_tempo.tm_sec = 0;
                printf("Cronômetro zerado: 00:00:00\n");
                strftime(c->str, (size_t)10, "%H:%M:%S", &(c->dados_tempo));

                break;

            case 6:

                if(!flag_alarme) {

                    printf("Informe um alarme (hh:mm): ");
                    scanf("%d:%d", &(a->dados_tempo.tm_hour), &(a->dados_tempo.tm_min));

                    pthread_t thread_verifica_cima;
                    pthread_t thread_verifica_baixo;

                    pthread_create(&thread_verifica_cima, NULL, verificar_tempo_cima, &(a->dados_tempo));
                    pthread_create(&thread_verifica_baixo, NULL, verificar_tempo_baixo, &(a->dados_tempo));
                    pthread_cancel(thread_verifica_cima);
                    pthread_cancel(thread_verifica_baixo);

                    strftime(a->str, (size_t)10, "%H:%M", &(a->dados_tempo));
                    pthread_create(&thread_alarme, NULL, definir_alarme, alarme);

                }

                printf("Alarme %sdefinido para tocar às %s:00\n", flag_alarme ? "já " : "",
                    a->str);
                flag_alarme = true;

                break;

            case 7:

                if(flag_alarme) {
                    a->dados_tempo.tm_hour = a->dados_tempo.tm_min = a->dados_tempo.tm_sec = 0;
                    pthread_cancel(thread_alarme);
                }

                printf("Alarme %sdesativado!\n", (flag_alarme) ? "" : "já ");
                flag_alarme = false;

                break;

            default:
                puts("Inválido! Informe uma opção de 0 a 7!");

        }

        __fpurge(stdin);
        printf("\nPressione ENTER para continuar... ");
        getchar();
        __fpurge(stdin);

    } while(op != 0);

    return EXIT_SUCCESS;

}
