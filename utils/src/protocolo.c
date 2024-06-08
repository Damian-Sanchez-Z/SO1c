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