
#ifndef KERNEL_UTILS_H
#define KERNEL_UTILS_H

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include"../../utils/include/cliente.h"
#include"../../utils/include/server.h"
#include"../../utils/include/logger.h"

#define ARCHIVO_LOGGER "config/kernel.log"
#define ARCHIVO_CONFIG "config/kernel.config"
#define SUCCESS 0
#define FAILURE -1
#endif //KERNEL_UTILS_H

typedef struct kernel_config
{
    char * PUERTO_ESCUCHA;
    char *IP_MEMORIA;
    char *PUERTO_MEMORIA;
    char *IP_CPU;
    char * PUERTO_CPU_DISPATCH;
    char * PUERTO_CPU_INTERRUPT;
    char *ALGORITMO_PLANIFICACION;
    int32_t QUANTUM;
    char **RECURSOS;
    char **INSTANCIAS_RECURSOS;
    char *GRADO_MULTIPROGRAMACION;
} kernel_config;

typedef enum
{
    EXIT,
    WAIT,
    SIGNAL
} Comando;

extern kernel_config KernelConfig;
extern int socket_cpu_dispatch;
extern int socket_cpu_interrupt;
extern t_log* logger;
t_queue *cola_ready;

int iniciar_config_kernel(char*);
int iniciar_servidor_kernel();
int conectar_con_memoria();
int conectar_con_cpu();
int conectar_con_io();