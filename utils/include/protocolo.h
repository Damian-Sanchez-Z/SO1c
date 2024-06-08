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
typedef pthread_t Hilo;

extern t_log* logger;

BUFFER* recibir_buffer(int socket);
PCB* deserializar_pcb(BUFFER *buffer);
PAQUETE *crear_paquete(CODIGO_OPERACION codigoOperacion);

typedef enum
{
    // DESCONEXION = -1,
    MENSAJE,
    // PAQUETE_CPU, // TODO: CHEQUEAR NOMBRE REDEFINIDOS ?
    // OP_PCB,
    INSTRUCCION,
    PAQUETE,
    // INSTRUCCIONES,
    // CREAR_PROCESO,
    // FINALIZAR_PROCESO,
    // SEG_FAULT,
    // RECEPCION_OK,
    // PROCESO_FINALIZADO,
    // CREAR_SEGMENTO,
    // BORRAR_SEGMENTO,
    // CONSOLIDAR,
    // SOLICITAR_COMPACTACION,
    // COMPACTACION_TERMINADA,
    // FALTA_MEMORIA,
    // FINALIZO_TRUNCADO,
    // FINALIZO_LECTURA,
    // FINALIZO_ESCRITURA,
    // READ,
    // WRITE,
    
} CODIGO_OPERACION;
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
    char* nombreInstruccion;
    char* valor; // TODO: Chequear. SET AX HOLA
    char* registro; //Recibe nombr de registro, comparo y asigno al registro del PCB
    char* registro_origen;
    char* registro_destino;
    char* numeroDeInstruccion;
    IO_Interface IO_Interface;
    int32_t unidades_de_trabajo;
    //--------------//
    int32_t direccionLogica;
    int32_t direccionFisica;
    int32_t tiempo;
    char* nombreArchivo;
    int32_t posicion;
    int32_t cantBytes;
    int32_t tamanioArchivo; 
    char* recurso;
    int32_t idSegmento; //Copiar de la tabla de seg   
    int32_t nombreInstruccion_long;
    int32_t valor_long; 
    int32_t registro_long;
    int32_t recurso_long;
    int32_t nombreArchivo_long;
    int32_t tamanioSegmento;
    
} Instruccion;

typedef struct
{
    int size;
    void *stream;
} BUFFER;
typedef struct
{
    CODIGO_OPERACION codigo_operacion;
    BUFFER *buffer;
} PAQUETE;

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