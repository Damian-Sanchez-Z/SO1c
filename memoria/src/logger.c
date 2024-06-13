#include "../include/logger.h"

t_log* iniciar_logger_memoria()
{
	t_log* nuevo_logger = log_create(ARCHIVO_LOGGER, "MEMORIA", 1, LOG_LEVEL_INFO);

	if(nuevo_logger == NULL){
		perror("[MEMORIA]: Error al crear el logger.");
		exit(EXIT_FAILURE);
	}

	log_info(nuevo_logger, "[MEMORIA]: Logger creado correctamente");

	return nuevo_logger;
}