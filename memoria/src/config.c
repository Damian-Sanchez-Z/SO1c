#include "../include/config.h"

void iniciar_config_memoria(char* config_path)
{
	config_raw = config_create(config_path);

	if(config_raw == NULL){
		perror("[MEMORIA]: ERROR AL INICIAR CONFIG INICIAL");
		exit(EXIT_FAILURE);
	}

	//config_raw es el t_config y config es el struct

	config.puerto = config_get_int_value(config_raw, "PUERTO_ESCUCHA");
	config.tamanio_memoria = config_get_int_value(config_raw, "TAM_MEMORIA");
	config.tamanio_pagina = config_get_int_value(config_raw, "TAM_PAGINA");
	config.path_instrucciones = config_get_string_value(config_raw, "PATH_INSTRUCCIONES");
	config.retardo_memoria = config_get_int_value(config_raw, "RETARDO_MEMORIA");

	log_info(logger, "[MEMORIA]: Archivo Config creado y rellenado correctamente");
}

int iniciar_servidor_memoria()
{
    log_info(logger, "[MEMORIA]: Iniciando Servidor");
    socket_memoria = iniciar_servidor(ip, string_itoa(config.puerto));

    if (socket_memoria < 0)
    {
        log_error(logger, "[MEMORIA]: Error intentando iniciar Servidor.");
        return FAILURE;
    }

    log_info(logger, "[MEMORIA]: Servidor iniciados correctamente.");
    return SUCCESS;
}