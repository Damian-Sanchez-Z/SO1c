
#include "../include/protocolo.h"

PAQUETE *crear_paquete(CODIGO_OPERACION codigoOperacion)
{
    PAQUETE *paquete = malloc(sizeof(PAQUETE));

    paquete->codigo_operacion = codigoOperacion;
    inicializar_buffer(paquete);

    return paquete;
}

void eliminar_paquete(PAQUETE *paquete)
{
    if (paquete != NULL)
    {
        if (paquete->buffer != NULL)
        {
            free(paquete->buffer->stream);
            free(paquete->buffer);
        }
        free(paquete);
    }
}

void inicializar_buffer(PAQUETE *paquete)
{
    paquete->buffer = malloc(sizeof(BUFFER));
    paquete->buffer->size = 0;
    paquete->buffer->stream = NULL;
}

void agregar_a_paquete(PAQUETE *paquete, void *valor, int tamanio)
{
    paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + tamanio + sizeof(int));

    memcpy(paquete->buffer->stream + paquete->buffer->size, &tamanio, sizeof(int));
    memcpy(paquete->buffer->stream + paquete->buffer->size + sizeof(int), valor, tamanio);

    paquete->buffer->size += tamanio + sizeof(int);
}

void *serializar_paquete(PAQUETE *paquete, int bytes)
{
    void *magic = malloc(bytes);
    int desplazamiento = 0;

    memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
    desplazamiento += sizeof(int);
    memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
    desplazamiento += sizeof(int);
    memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);

    return magic;
}

PCB *deserializar_pcb(BUFFER *buffer)
{
    PCB *pcb = malloc(sizeof(PCB));
    //Falta implementar

    return pcb;
}

BUFFER* recibir_buffer(int socket) {
	BUFFER* buffer = malloc(sizeof(BUFFER));

	recv(socket, &(buffer->size), sizeof(int), 0);
	buffer->stream = malloc(buffer->size);
	recv(socket, buffer->stream, buffer->size, 0);

	return buffer;
}