
#ifndef KERNEL_CONTROLADOR_H
#define KERNEL_CONTROLADOR_H

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
#include"../../utils/include/protocolo.h"


typedef struct
{
    char *nombre;
    int instancias;
    int instancias_maximas;
    t_queue *cola_block;
} Recurso;

typedef enum
{
    NEW,
    READY,
    EXEC,
    BLOCK,
    FINISHED
} ESTADO;

typedef struct
{
    PCB *pcb;
    ESTADO estado;
} Proceso;

t_list *lista_recursos;
#endif //KERNEL_CONTROLADOR_H

t_list *crear_recursos(char** recursos, char** instancias_recursos);
int *manejar_wait(Proceso *proceso, char *nombre_recurso);
int *manejar_signal(Proceso *proceso, char *nombre_recurso);