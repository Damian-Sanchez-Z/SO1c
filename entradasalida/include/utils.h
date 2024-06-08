#ifndef INTERFAZ_UTILS_H
#define INTERFAZ_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <commons/log.h>
#include <commons/log.h>
#include <commons/string.h>
#include <commons/config.h>
#include <readline/readline.h>
#include <../../utils/include/cliente.h>
#include <../../utils/include/server.h>

#define ARCHIVO_LOGGER "../interfaz.log"
#define ARCHIVO_CONFIG "../interfaz.config"
#define SUCCESS 0
#define FAILURE -1

t_config* config;

typedef struct interfaz_config{
    char *TIPO_INTERFAZ;
    int *TIEMPO_UNIDAD_TRABAJO;
    char *IP_KERNEL;
    int *PUERTO_KERNEL;
    char *IP_MEMORIA;
    int *PUERTO_MEMORIA;
    char *PATH_BASE_DIALFS;
    int *BLOCK_SIZE;
    int *BLOCK_COUNT;
    int *RETRASO_COMPACTACION;
}interfaz_config;

void iniciar_logger_interfaz();
int iniciar_config_interfaz(char*);
int iniciar_cliente_interfaz(char* ip, char* puerto);

#endif