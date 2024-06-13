#include "../include/utils.h"

void iniciar_logger_interfaz(){
    logger = log_create(ARCHIVO_LOGGER, nombre, 1, LOG_LEVEL_INFO);
    log_info(logger, "[%s]: Logger creado correctamente.", nombre);
}

int iniciar_config_interfaz(char* path){
    t_config* config = config_create(path);
    if(config == NULL)
    {
        log_error(logger,"[%s]: Error al iniciar la configuracion", nombre);
        return FAILURE;
    }
    configuracion.TIPO_INTERFAZ = config_get_string_value(config, "TIPO_INTERFAZ");
    configuracion.IP_KERNEL = config_get_string_value(config, "IP_KERNEL");
    configuracion.PUERTO_KERNEL = config_get_int_value(config, "PUERTO_KERNEL");

   tipo_interfaz = enum_interfaz(configuracion.TIPO_INTERFAZ);

    switch (tipo_interfaz)
    {
    case GENERICA:
        configuracion.TIEMPO_UNIDAD_TRABAJO = config_get_int_value(config, "TIEMPO_UNIDAD_TRABAJO");
        break;
    case STDIN:
        configuracion.IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
        configuracion.PUERTO_MEMORIA = config_get_int_value(config, "PUERTO_MEMORIA");
        break;
    case STDOUT:
        configuracion.TIEMPO_UNIDAD_TRABAJO = config_get_int_value(config, "TIEMPO_UNIDAD_TRABAJO");
        configuracion.IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
        configuracion.PUERTO_MEMORIA = config_get_int_value(config, "PUERTO_MEMORIA");
        break;
    default:
        configuracion.TIEMPO_UNIDAD_TRABAJO = config_get_int_value(config, "TIEMPO_UNIDAD_TRABAJO");
        configuracion.IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
        configuracion.PUERTO_MEMORIA = config_get_int_value(config, "PUERTO_MEMORIA");  
        configuracion.PATH_BASE_DIALFS = config_get_string_value(config, "PATH_BASE_DIALFS");
        configuracion.BLOCK_SIZE = config_get_int_value(config, "BLOCK_SIZE");
        configuracion.BLOCK_COUNT = config_get_int_value(config, "BLOCK_COUNT");
        configuracion.RETRASO_COMPACTACION = config_get_int_value(config, "RETRASO_COMPACTACION");
        break;
    }
    
    log_info(logger, "[%s]: Archivo Config creado y rellenado correctamente.", nombre);
    config_destroy(config);
    return SUCCESS;
}

int iniciar_cliente_interfaz(char* ipServidor, int puertoServidor, char* servidor)
{
    char* puerto = string_itoa(puertoServidor);
    log_info(logger, "[%s]: Iniciando conexion con %s",nombre, servidor);
    int socket_interfaz = crear_conexion_con_servidor(ipServidor, puerto);

    if (socket_interfaz < 0)
    {
        log_error(logger, "[%s]: Error de conexion con %s .", nombre, servidor);
        return FAILURE;
    }

    log_info(logger, "[%s]: Conexion con %s exitosa.", nombre, servidor);
    return socket_interfaz;
}
TIPO_INTERFAZ enum_interfaz(char* tipo){
    TIPO_INTERFAZ uno;
    if( string_equals_ignore_case(tipo,"GENERICA"))
        uno = GENERICA;
    if( string_equals_ignore_case(tipo,"STDIN"))
        uno = STDIN;
    if( string_equals_ignore_case(tipo,"STDOUT"))
        uno = STDOUT;
    if( string_equals_ignore_case(tipo,"DIALFS"))
        uno = DIALFS;
    return uno;
}