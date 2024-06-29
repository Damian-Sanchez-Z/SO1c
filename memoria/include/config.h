#ifndef MEMORIA_CONFIG_H
#define MEMORIA_CONFIG_H
#include "logger.h"
#include <commons/config.h>
#include "../../utils/include/server.h"
#define ARCHIVO_CONFIG "../memoria.config"
typedef struct{
    int puerto;
    int tamanio_memoria;
    int tamanio_pagina;
    char* path_instrucciones;
    int retardo_respuesta;
}MEM_CONFIG;

void iniciar_config_memoria(char* config_path);
int iniciar_servidor_memoria();
int conectar_con_io();

extern t_log* logger;

extern int socket_memoria;

#endif //MEMORIA_CONFIG_H