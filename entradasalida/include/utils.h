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

void iniciar_logger_interfaz();
int iniciar_config_interfaz(char*);
int iniciar_cliente_interfaz(char* ip, char* puerto);

#endif