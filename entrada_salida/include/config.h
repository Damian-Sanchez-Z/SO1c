//
// Created by utnso on 5/2/24.
//

#ifndef ENTRADA_SALIDA_CONFIG2_H
#define ENTRADA_SALIDA_CONFIG2_H

//#include <protocolo.h>
#include <commons/log.h>
#include <commons/string.h>
#include <commons/config.h>
#include "../../utils/include/server.h"

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
} IO_CONFIG;

extern IO_CONFIG io_config;

extern const char* ip = "localhost:3000";

#define SUCCESS 0
#define FAILURE 1

#define ARCHIVO_LOGGER "config/io.log"
#define ARCHIVO_CONFIG "config/io.config"

typedef t_config Config;
typedef t_log Logger;
typedef pthread_t Hilo;

extern Logger *logger;
extern Config *config;
extern Hilo hilo_kernel;

void rellenar_configuracion_io(Config *config);

extern int socket_io;

void iniciar_logger_io();
int iniciar_config_io(char* path);
int iniciar_servidor_io();

#endif //ENTRADA_SALIDA_CONFIG2_H