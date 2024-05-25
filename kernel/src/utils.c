#include"../include/utils.h"

t_log* logger;
t_config* config;
int socket_kernel;


void iniciar_logger_kernel()
{
    logger = log_create(ARCHIVO_LOGGER, "Kernel", 1, LOG_LEVEL_INFO);
    log_info(logger, "[KERNEL]: Logger creado correctamente");
}

int iniciar_config_kernel(char* path)
{
    config = config_create(path);
    if(config == NULL)
    {
        log_error(logger,"[KERNEL]: ERROR AL INICIAR CONFIG INICIAL");
        return FAILURE;
    }

    KernelConfig.IP = config_get_string_value(config, "IP");
    KernelConfig.PUERTO_ESCUCHA = config_get_string_value(config, "PUERTO_ESCUCHA");
    KernelConfig.IP_CPU = config_get_string_value(config, "IP_CPU");
    KernelConfig.PUERTO_CPU = config_get_string_value(config, "PUERTO_CPU");
    KernelConfig.IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
    KernelConfig.PUERTO_MEMORIA = config_get_string_value(config, "PUERTO_MEMORIA");
    KernelConfig.IP_FILESYSTEM = config_get_string_value(config, "IP_FILESYSTEM");
    KernelConfig.PUERTO_FILESYSTEM = config_get_string_value(config, "PUERTO_FILESYSTEM");
    KernelConfig.ALGORITMO_PLANIFICACION = config_get_string_value(config, "ALGORITMO_PLANIFICACION");
    KernelConfig.ESTIMACION_INICIAL = config_get_string_value(config,"ESTIMACION_INICIAL");
    KernelConfig.HRRN_ALFA = config_get_string_value(config, "HRRN_ALFA");
    KernelConfig.GRADO_MAX_MULTIPROGRAMACION = config_get_string_value(config, "GRADO_MAX_MULTIPROGRAMACION");
    KernelConfig.RECURSOS = config_get_array_value(config, "RECURSOS");
    KernelConfig.INSTANCIAS_RECURSOS = config_get_array_value(config, "INSTANCIAS_RECURSOS");
    KernelConfig.QUANTUM = config_get_int_value(config, "QUANTUM");

    log_info(logger, "[KERNEL]: Archivo Config creado y rellenado correctamente");
    return SUCCESS;
}

int iniciar_servidor_kernel()
{
    log_info(logger, "[KERNEL]: Iniciando Servidor ...");
    socket_kernel = iniciar_servidor(KernelConfig.IP, KernelConfig.PUERTO_ESCUCHA);

    if (socket_kernel < 0)
    {
        log_error(logger, "[KERNEL]: Error intentando iniciar Servidor.");
        return FAILURE;
    }

    log_info(logger, "[KERNEL]: Servidor iniciado correctamente.");
    return SUCCESS;
}