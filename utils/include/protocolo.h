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

typedef enum
{
    GENERICA,
    STDIN,
    STDOUT,
    DIALFS,

} TIPO_INTERFAZ;

typedef enum
{
    DESCONEXION = -1,
    MENSAJE,
    PAQUETE_CPU, // TODO: CHEQUEAR NOMBRE REDEFINIDOS ?
    OP_PCB,
    INSTRUCCION,
    INSTRUCCIONES,
    CREAR_PROCESO,
    FINALIZAR_PROCESO,
    SEG_FAULT,
    RECEPCION_OK,
    PROCESO_FINALIZADO,
    CREAR_SEGMENTO,
    BORRAR_SEGMENTO,
    CONSOLIDAR,
    SOLICITAR_COMPACTACION,
    COMPACTACION_TERMINADA,
    FALTA_MEMORIA,
    FINALIZO_TRUNCADO,
    FINALIZO_LECTURA,
    FINALIZO_ESCRITURA,
    READ,
    WRITE,
    RESPUESTA_FILE_SYSTEM

} CODIGO_OPERACION;

typedef struct
{
    int32_t PC;
    int8_t AX;
    int8_t BX;
    int8_t CX;
    int8_t DX;
    int32_t EAX;
    int32_t EBX;
    int32_t ECX;

} Registers;

typedef struct
{
    int32_t pid;
    int32_t programCounter;
    int32_t quantum;
    Registers registers;
    t_list instructions;

} PCB;

typedef struct
{
    CODIGO_OPERACION codigo_operacion;
    BUFFER *buffer;
} PAQUETE;

typedef struct
{
    int size;
    void *stream;
} BUFFER;

PAQUETE *crear_paquete(CODIGO_OPERACION codigoOperacion);
void eliminar_paquete(PAQUETE *paquete);
void inicializar_buffer(PAQUETE *paquete);
void agregar_a_paquete(PAQUETE *paquete, void *valor, int tamanio);
void *serializar_paquete(PAQUETE *paquete, int bytes);


#endif