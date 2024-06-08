#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>
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

typedef struct kernel_config
{
    char *IP;
    char *PUERTO_ESCUCHA;
    char *IP_CPU;
    char *PUERTO_CPU;
    char *IP_MEMORIA;
    char *PUERTO_MEMORIA;
    char *IP_FILESYSTEM;
    char *PUERTO_FILESYSTEM;
    char *ALGORITMO_PLANIFICACION;
    char *ESTIMACION_INICIAL;
    char *HRRN_ALFA;
    char *GRADO_MAX_MULTIPROGRAMACION;
    char **RECURSOS;
    char **INSTANCIAS_RECURSOS;
    int32_t QUANTUM;
} kernel_config;

extern kernel_config KernelConfig;
extern int socket_cpu;

int iniciar_config_kernel(char*);
int iniciar_servidor_kernel();