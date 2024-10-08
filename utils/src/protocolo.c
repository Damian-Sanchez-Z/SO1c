
#include "../include/protocolo.h"

PAQUETE *crear_paquete(CODIGO_OPERACION codigoOperacion)
{
    PAQUETE *paquete = malloc(sizeof(PAQUETE));

    paquete->codigo_operacion = codigoOperacion;
    inicializar_buffer(paquete);

    return paquete;
}

void enviar_mensaje_a_servidor(char *mensaje, int socketCliente)
{
    PAQUETE *paquete = crear_paquete(MENSAJE);

    paquete->buffer->size = strlen(mensaje) + 1;
    paquete->buffer->stream = malloc(paquete->buffer->size);
    memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

    enviar_paquete_a_servidor(paquete, socketCliente);
    eliminar_paquete(paquete);
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

BUFFER* recibir_buffer(int socket) {
	BUFFER* buffer = malloc(sizeof(BUFFER));

	recv(socket, &(buffer->size), sizeof(int), 0);
	buffer->stream = malloc(buffer->size);
	recv(socket, buffer->stream, buffer->size, 0);

	return buffer;
}

PCB *deserializar_pcb(BUFFER *buffer)
{
    PCB *pcb = malloc(sizeof(PCB));
    //Falta implementar

    return pcb;
}


void enviar_paquete_a_cliente(PAQUETE *paquete, int socketCliente)
{
  enviar_paquete_a_servidor(paquete, socketCliente);
}

void enviar_paquete_a_servidor(PAQUETE *paquete, int socketCliente)
{
  int bytes = paquete->buffer->size + 2 * sizeof(int);
  void *aEnviar = serializar_paquete(paquete, bytes);

  send(socketCliente, aEnviar, bytes, 0);
  free(aEnviar);
}