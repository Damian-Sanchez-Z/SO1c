#include "../include/utils.h"

void iniciar_logger_interfaz()
{
    logger = log_create(ARCHIVO_LOGGER, "INTERFAZ", 1, LOG_LEVEL_INFO);
    log_info(logger, "[INTERFAZ]: Logger creado correctamente");
}

int iniciar_config_interfaz(char* path)
{
    config = config_create(path);
    if(config == NULL)
    {
        log_error(logger,"[KERNEL]: ERROR AL INICIAR CONFIG INICIAL DE INTERFAZ");
        return FAILURE;
    }
    config_io.TIPO_INTERFAZ = config_get_string_value(config, "TIPO_INTERFAZ");
    config_io.TIEMPO_UNIDAD_TRABAJO = config_get_int_value(config, "TIEMPO_UNIDAD_TRABAJO");
    config_io.IP_KERNEL = config_get_string_value(config, "IP_KERNEL");
    config_io.PUERTO_KERNEL = config_get_int_value(config, "PUERTO_KERNEL");
    config_io.IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
    config_io.PUERTO_MEMORIA = config_get_int_value(config, "PUERTO_MEMORIA");
    config_io.PATH_BASE_DIALFS = config_get_string_value(config, "PATH_BASE_DIALFS");
    config_io.BLOCK_SIZE = config_get_int_value(config, "BLOCK_SIZE");
    config_io.BLOCK_COUNT = config_get_int_value(config, "BLOCK_COUNT");
    config_io.RETRASO_COMPACTACION = config_get_int_value(config, "RETRASO_COMPACTACION");

    log_info(logger, "[INTERFAZ]: Archivo Config creado y rellenado correctamente");
    return SUCCESS;
}

int iniciar_cliente_interfaz(char* ipServidor, char* puertoServidor)
{
    log_info(logger, "[INTERFAZ]: Iniciando conexion ...");
    int socket_interfaz = crear_conexion_con_servidor(ipServidor, puertoServidor);

    if (socket_interfaz < 0)
    {
        log_error(logger, "[INTERFAZ]: Error intentando iniciar conexion.");
        return FAILURE;
    }

    log_info(logger, "[INTERFAZ]: Conexion al servidor exitosa.");
    return socket_interfaz;
}