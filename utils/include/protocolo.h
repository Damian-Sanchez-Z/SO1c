#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <commons/config.h>
#include <commons/log.h>
#include <commons/temporal.h>
#include <math.h>
#include <time.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>
#include <commons/bitarray.h>
#include <commons/collections/dictionary.h>

// #include <list.h>
#include <commons/string.h>
#include "cliente.h"
#include "server.h"
#include "socket.h"

typedef t_config Config;
typedef t_list Lista;

BUFFER* recibir_buffer(int socket);
PCB* deserializar_pcb(BUFFER *buffer);

typedef struct
{
    int32_t PID;
    int32_t program_counter;       //DEBE INICIALIZARSE EN 0.
    Registro_CPU registros_cpu;     // Tipo struct REGISTROS_CPU
    int quantum;     //Unidad de tiempo utilizada por el algoritmo de planificación VRR.

} PCB;  
typedef struct 
{
    uint32_t PC;    // Progam Counter
    uint8_t AX;      
    uint8_t BX;      
    uint8_t CX;      
    uint8_t DX;     
    uint32_t EAX;    
    uint32_t EBX;    
    uint32_t ECX;    
    uint32_t EDX;    
    uint32_t *SI;    // Dirección lógica de memoria de origen desde donde se va a copiar un string.
    uint32_t *DI;    // Dirección lógica de memoria de destino desde donde se va a copiar un string.

} Registro_CPU;
typedef struct
{
    int size;
    void *stream;
} BUFFER;

#endif