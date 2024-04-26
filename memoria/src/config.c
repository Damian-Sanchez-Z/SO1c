#include "main.h"

t_config* iniciar_config_memoria(config_path)
{
	t_config* nuevo_config = config_create(config_path);

	if(nuevo_config == NULL){
		perror("Error al crear config");
		exit(EXIT_FAILURE);
	}

	return nuevo_config;
}