#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include <commons/log.h>
#include <commons/string.h>
#include <commons/config.h>
#include<readline/readline.h>
#include "../../utils/include/server.h"

#include "../include/logger.h"
#include "../include/config.h"

t_log* logger;
void iniciar_config(void);
t_config* config_raw;

typedef struct 
{
    int puerto;
    int tamanio_memoria;
    int tamanio_pagina;
    char* path_instrucciones;
    int retardo_memoria;
} MEM_CONFIG;

MEM_CONFIG config;