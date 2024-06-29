#include "../include/config.h"
MEM_CONFIG config;
int socket_memoria;

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
    socket_memoria = iniciar_servidor(string_itoa(config.puerto));
    if (socket_memoria < 0)
    {
        log_error(logger, "[MEMORIA]: Error intentando iniciar Servidor.");
        return FAILURE;
    }

    return SUCCESS;
}

int conectar_con_io()
{
    while(true){

        log_info(logger, "[KERNEL] Esperando nueva interfaz IO...");

        int socket_interfaz = esperar_cliente(socket_memoria);
        log_info(logger, "[CPU]: Conexión con IO [%i] establecida.", socket_interfaz);

        //TODO: HILOS
    }
}

