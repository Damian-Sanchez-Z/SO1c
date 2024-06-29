
#ifndef CPU_CONFIG_H
#define CPU_CONFIG_H

#include "utils.h"

typedef struct CPU_CONFIG
{
    char *IP_MEMORIA;
    int  PUERTO_MEMORIA;
    int PUERTO_ESCUCHA_DISPATCH;
    int PUERTO_ESCUCHA_INTERRUPT;
    int CANTIDAD_ENTRADAS_TLB;
    char *ALGORITMO_TLB;
} CPU_CONFIG;

extern CPU_CONFIG CPUConfig;

int iniciar_config_cpu(char* path);


#endif
