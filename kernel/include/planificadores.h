

#ifndef KERNEL_PLANIFICADORES_H
#define KERNEL_PLANIFICADORES_H

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
#include "utils.h"

#endif //KERNEL_PLANIFICADORES_H

PCB* enviarACPU(PCB* pcb);
void fifo();
void roundRobin();
void ejecutarPlanificacion();
PCB* CrearPcb();