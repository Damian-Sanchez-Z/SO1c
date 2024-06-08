#ifndef CPU_UTILS_H
#define CPU_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "config.h"

#define ARCHIVO_LOGGER "config/cpu.log"
#define ARCHIVO_CONFIG "config/cpu.config"

#include "../../utils/include/server.h"
#include "../../utils/include/protocolo.h"
#include "../../utils/include/cliente.h"
#include "../../utils/include/logger.h"

#define SUCCESS 0
#define FAILURE 1

extern Logger *logger;
extern Config *config;
extern Hilo hilo_kernel;

extern int socket_cpu_dispatch;
extern int socket_cpu_interrupt;
extern int socket_memoria;
extern int socket_kernel;

void iniciar_logger_cpu();
int iniciar_config_cpu(char* path);
int iniciar_servidor_cpu(char* ip);
int conectar_con_memoria();
void conectar_con_kernel();
void terminar_ejecucion();

void cambiarValorProgramCounter(char *valor, PCB *pcb);
void asignar_a_registro(char *valor, char *registro_instr, PCB *pcb);
int ejecutar_instruccion(Instruccion *Instruccion, PCB *pcb);
void ejecutar_set(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb);
void ejecutar_SUM(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb);
void ejecutar_SUB(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb);
void ejecutar_jnz(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb);
void ejecutar_io_gen_sleep(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb);



#endif //CPU_UTILS_H
