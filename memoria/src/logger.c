#include "main.h"

t_log* iniciar_logger_memoria()
{
	t_log* nuevo_logger = log_create("log.log", "Logger", 1, LOG_LEVEL_INFO);

	if(nuevo_logger == NULL){
		perror("No se hizo el logger");
		exit(EXIT_FAILURE);
	}

	return nuevo_logger;
}