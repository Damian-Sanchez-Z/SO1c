#include "../include/protocolo.h"

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
