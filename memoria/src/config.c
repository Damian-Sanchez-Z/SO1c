#include "main.h"

void iniciar_config_memoria(config_path)
{
	config_raw = config_create(config_path);

	if(config_raw == NULL){
		perror("Error al crear config");
		exit(EXIT_FAILURE);
	}

	//config_raw es el t_config y config es el struct

	config.puerto = config_get_string_value(config_raw, "PUERTO_ESCUCHA");
	config.tamanio_memoria = config_get_string_value(config_raw, "TAM_MEMORIA");
	config.tamanio_pagina = config_get_string_value(config_raw, "TAM_PAGINA");
	config.path_instrucciones = config_get_string_value(config_raw, "PATH_INSTRUCCIONES");
	config.retardo_memoria = config_get_string_value(config_raw, "RETARDO_MEMORIA");

}