#include "../include/config.h"
MEM_CONFIG config;
void iniciar_config_memoria(char* config_path)
{
	t_config *config_raw = config_create(config_path);

	if(config_raw == NULL){
		log_error(logger, "Error al iniciar configuracion.");
		exit(EXIT_FAILURE);
	}

	//config_raw es el t_config y config es el struct

	config.puerto = config_get_int_value(config_raw, "PUERTO_ESCUCHA");
	config.tamanio_memoria = config_get_int_value(config_raw, "TAM_MEMORIA");
	config.tamanio_pagina = config_get_int_value(config_raw, "TAM_PAGINA");
	config.path_instrucciones = config_get_string_value(config_raw, "PATH_INSTRUCCIONES");
	config.retardo_respuesta = config_get_int_value(config_raw, "RETARDO_RESPUESTA");

	log_info(logger, "[MEMORIA]: Configuracion inicial exitosa.");
}

int iniciar_servidor_memoria()
{
    log_info(logger, "[MEMORIA]: Iniciando Servidor");
    int socket_memoria = iniciar_servidor(string_itoa(config.puerto));

    if (socket_memoria < 0)
    {
        log_error(logger, "[MEMORIA]: Error intentando iniciar Servidor.");
        return EXIT_FAILURE;
    }

    log_info(logger, "[MEMORIA]: Servidor iniciado correctamente.");
    return socket_memoria;
}

