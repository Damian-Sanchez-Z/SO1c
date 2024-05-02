#include<stdio.h>
#include<stdlib.h>
#include"log.h"
#include"string.h"
#include"config.h"
#include<readline/readline.h>

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