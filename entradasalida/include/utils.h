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
#include "../../utils/include/cliente.h"
#include "../../utils/include/server.h"
#include "../../utils/include/protocolo.h"
#include "../../utils/include/logger.h"

#define ARCHIVO_LOGGER "../interfaz.log"
#define ARCHIVO_CONFIG "../interfaz.config"
#define SUCCESS 0
#define FAILURE -1
typedef enum{
    GENERICA,
    STDIN,
    STDOUT,
    DIALFS
}TIPO_INTERFAZ;
typedef struct interfaz_config{
    char *TIPO_INTERFAZ;
    int TIEMPO_UNIDAD_TRABAJO;
    char *IP_KERNEL;
    int PUERTO_KERNEL;
    char *IP_MEMORIA;
    int PUERTO_MEMORIA;
    char *PATH_BASE_DIALFS;
    int BLOCK_SIZE;
    int BLOCK_COUNT;
    int RETRASO_COMPACTACION;
}interfaz_config;

extern t_log* logger;
extern char* nombre; //uen seccionde solo lectura y en inciar cliente interfaz no tiene definida la referencia
extern interfaz_config configuracion; 
extern TIPO_INTERFAZ tipo_interfaz; 

void iniciar_logger_interfaz();
int iniciar_config_interfaz(char* path);
int iniciar_cliente_interfaz(char* ip, int puerto, char* servidor);
TIPO_INTERFAZ enum_interfaz(char* tipo);

#endif