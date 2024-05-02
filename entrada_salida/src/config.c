
#include "../include/config.h"

IO_CONFIG io_config;

void rellenar_configuracion_io(Config *config){
    io_config.TIPO_INTERFAZ = config_get_string_value(config, "TIPO_INTERFAZ");
    io_config.TIEMPO_UNIDAD_TRABAJO = config_get_string_value(config, "TIEMPO_UNIDAD_TRABAJO");
    io_config.IP_KERNEL = config_get_string_value(config, "IP_KERNEL");
    io_config.PUERTO_KERNEL = config_get_string_value(config, "PUERTO_KERNEL");
    io_config.IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
    io_config.PUERTO_MEMORIA = config_get_string_value(config, "PUERTO_MEMORIA");
    io_config.PATH_BASE_DIALFS = config_get_string_value(config, "PATH_BASE_DIALFS");
    io_config.BLOCK_SIZE = config_get_string_value(config, "BLOCK_SIZE");
    io_config.BLOCK_COUNT = config_get_string_value(config, "BLOCK_COUNT");
    io_config.RETRADO_COMPACTACION = config_get_string_value(config, "RETRADO_COMPACTACION");    
}

void iniciar_logger_io()
{
    logger = log_create(ARCHIVO_LOGGER, "CPU", 1, LOG_LEVEL_INFO);
    log_info(logger, "[CPU]: Logger creado correctamente");
}

int iniciar_config_io(char* path)
{
    config = config_create(path);
    if(config == NULL)
    {
        log_error(logger,"[CPU]: ERROR AL INICIAR CONFIG INICIAL");
        return FAILURE;
    }
    rellenar_configuracion_io(config);
    log_info(logger, "[CPU]: Archivo Config creado y rellenado correctamente");
    return SUCCESS;
}

int iniciar_servidor_io()
{
    /*
    log_info(logger, "[CPU]: Iniciando Servidores De Dispatch e Interrupt...");
    socket_io = iniciar_servidor(ip, io_config.);

    if (socket_io < 0)
    {
        log_error(logger, "[CPU]: Error intentando iniciar Servidores.");
        return FAILURE;
    }

    log_info(logger, "[CPU]: Servidores iniciados correctamente.");
     */
    return SUCCESS;
}