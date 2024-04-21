
#ifndef CPU_CONFIG_H
#define CPU_CONFIG_H

#include "commons.h"

typedef struct CPU_CONFIG
{
    char *IP_MEMORIA;
    int32_t PUERTO_MEMORIA;
    int32_t PUERTO_ESCUCHA_DISPATCH;
    int32_t PUERTO_ESCUCHA_INTERRUPT;
    int32_t CANTIDAD_ENTRADAS_TLB;
    char *ALGORITMO_TLB;
} CPU_CONFIG;

extern CPU_CONFIG CPUConfig;

void cargar_configuracion_cpu(Config *config);

#endif
