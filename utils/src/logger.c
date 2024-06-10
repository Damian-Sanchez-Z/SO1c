#include "../include/logger.h"

t_log* iniciar_logger(char *modulo, char *archivo_logger)
{
	t_log* nuevo_logger = log_create(archivo_logger, modulo, 1, LOG_LEVEL_INFO);

	if(nuevo_logger == NULL){
		perror("No se hizo el logger");
		exit(EXIT_FAILURE);
	}

	log_info(nuevo_logger, "INICIADO LOGGER");

	return nuevo_logger;
}