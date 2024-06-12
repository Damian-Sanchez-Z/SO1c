
#ifndef CPU_CONFIG_H
#define CPU_CONFIG_H


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

void cargar_configuracion_cpu(Config *config);

#endif
