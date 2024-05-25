#include "../include/logger.h"

t_log* iniciar_logger_memoria()
{
	t_log* nuevo_logger = log_create(ARCHIVO_LOGGER, "Memoria", 1, LOG_LEVEL_INFO);

	if(nuevo_logger == NULL){
		perror("No se hizo el logger");
		exit(EXIT_FAILURE);
	}

	log_info(logger, "[MEMORIA]: Logger creado correctamente");

	return nuevo_logger;
}