#ifndef MEMORIA_MAIN_H
#define MEMORIA_MAIN_H
#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include"../../utils/include/server.h"
#include"utils.h"

#include"../include/logger.h"
#include"../include/config.h"

t_config* config_raw;

typedef struct CONFIG_MEMORIA
{
    int puerto;
    int tamanio_memoria;
    int tamanio_pagina;
    char* path_instrucciones;
    int retardo_memoria;
}MEM_CONFIG;

MEM_CONFIG config;

typedef struct OPERACION_MEMORIA{
    char* codigo_de_operacion;
    char* operando_de_operacion;
} OPERACION;
