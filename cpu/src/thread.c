#include "thread.h"

  PCB * recibir_pcb(int socket_kernel){

	BUFFER* buffer = recibir_buffer(socket_kernel);

	PCB* pcb = deserializar_pcb(buffer);

  free(buffer->stream);
	free(buffer);

	return pcb;
}

