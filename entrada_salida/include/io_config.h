#ifdef IO_CONFIG_H
#define IO_CONFIG_H

#include <protocolo.h>

typedef struct IO_CONFIG
{
    char *TIPO_INTERFAZ;
    char *TIEMPO_UNIDAD_TRABAJO;
    char *IP_KERNEL;
    char *PUERTO_KERNEL;
    char *IP_MEMORIA;
    char *PUERTO_MEMORIA;
    char *PATH_BASE_DIALFS;
    char *BLOCK_SIZE;
    char *BLOCK_COUNT;
    int RETRADO_COMPACTACION;
};

extern IO_CONFIG io_config;

void rellenar_configuracion_io(Config *config);


#endif