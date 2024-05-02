#ifndef CPU_UTILS_H
#define CPU_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "config.h"

#define ARCHIVO_LOGGER "config/cpu.log"
#define ARCHIVO_CONFIG "config/cpu.config"

#include "commons.h"
#include "../../utils/include/server.h"

#define SUCCESS 0
#define FAILURE 1

extern Logger *logger;
extern Config *config;
extern Hilo hilo_kernel;

extern int socket_cpu_dispatch;
extern int socket_cpu_interrupt;

void iniciar_logger_cpu();
int iniciar_config_cpu(char* path);
int iniciar_servidor_cpu(char* ip);

#endif //CPU_UTILS_H
