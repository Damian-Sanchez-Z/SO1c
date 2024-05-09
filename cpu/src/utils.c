#include "../include/utils.h"

int socket_cpu_dispatch;
int socket_cpu_interrupt;

Logger *logger;
Config *config;

void iniciar_logger_cpu()
{
    logger = log_create(ARCHIVO_LOGGER, "CPU", 1, LOG_LEVEL_INFO);
    log_info(logger, "[CPU]: Logger creado correctamente");
}

int iniciar_config_cpu(char* path)
{
    config = config_create(path);
    if(config == NULL)
    {
        log_error(logger,"[CPU]: ERROR AL INICIAR CONFIG INICIAL");
        return FAILURE;
    }
    cargar_configuracion_cpu(config);
    log_info(logger, "[CPU]: Archivo Config creado y rellenado correctamente");
    return SUCCESS;
}

int iniciar_servidor_cpu(char* ip)
{
    log_info(logger, "[CPU]: Iniciando Servidores De Dispatch e Interrupt...");
    socket_cpu_dispatch = iniciar_servidor(ip, CPUConfig.PUERTO_ESCUCHA_DISPATCH);
    socket_cpu_interrupt = iniciar_servidor(ip, CPUConfig.PUERTO_ESCUCHA_INTERRUPT);

    if (socket_cpu_dispatch < 0 || socket_cpu_interrupt < 0)
    {
        log_error(logger, "[CPU]: Error intentando iniciar Servidores.");
        return FAILURE;
    }

    log_info(logger, "[CPU]: Servidores iniciados correctamente.");
    return SUCCESS;
}

int conectar_con_memoria()
{
    log_info(logger, "[CPU] conectando con memoria...");
    socket_memoria = crear_conexion_con_servidor(CPUConfig.IP_MEMORIA, CPUConfig.PUERTO_MEMORIA);

    if (socket_memoria < 0)
    {
        log_error(logger, "[CPU]: MEMORIA NO ESTÁ DISPONIBLE, FINALIZANDO EJECUCIÓN");
        return FAILURE;
    }
    log_info(logger, "[CPU]: Conexion con Memoria: OK %d", socket_memoria);
    return SUCCESS;
}

void conectar_con_kernel()
{
    log_info(logger, "[CPU]: Esperando conexiones de KERNEL..");
    socket_kernel = esperar_cliente(socket_cpu);
    log_info(logger, "[CPU]: Conexión de KERNEL establecida.");

    //crear hilo
}

void terminar_ejecucion()
{
    log_warning(logger, "[CPU]: Finalizando ejecucion...");
    log_destroy(logger);
    config_destroy(config);
}

