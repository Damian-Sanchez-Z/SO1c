#include"../include/utils.h"

t_config* config;
int socket_kernel;
int socket_memoria;
int socket_cpu_dispatch;
int socket_cpu_interrupt;

int iniciar_config_kernel(char* path)
{
    config = config_create(path);
    if(config == NULL)
    {
        log_error(logger,"[KERNEL]: ERROR AL INICIAR CONFIG INICIAL");
        return FAILURE;
    }

    KernelConfig.PUERTO_ESCUCHA = config_get_string_value(config, "PUERTO_ESCUCHA");

    KernelConfig.IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
    KernelConfig.PUERTO_MEMORIA = config_get_string_value(config, "PUERTO_MEMORIA");

    KernelConfig.IP_CPU = config_get_string_value(config, "IP_CPU");
    KernelConfig.PUERTO_CPU_DISPATCH = config_get_string_value(config, "PUERTO_CPU_DISPATCH");
    KernelConfig.PUERTO_CPU_INTERRUPT = config_get_string_value(config, "PUERTO_CPU_INTERRUPT");

    KernelConfig.ALGORITMO_PLANIFICACION = config_get_string_value(config, "ALGORITMO_PLANIFICACION");

    KernelConfig.QUANTUM = config_get_int_value(config, "QUANTUM");

    KernelConfig.GRADO_MULTIPROGRAMACION = config_get_string_value(config, "GRADO_MULTIPROGRAMACION");
    KernelConfig.RECURSOS = config_get_array_value(config, "RECURSOS");
    KernelConfig.INSTANCIAS_RECURSOS = config_get_array_value(config, "INSTANCIAS_RECURSOS");

    log_info(logger, "[KERNEL]: Archivo Config creado y rellenado correctamente");
    return SUCCESS;
}

int iniciar_servidor_kernel()
{
    log_info(logger, "[KERNEL]: Iniciando Servidor ...");
    socket_kernel = iniciar_servidor(KernelConfig.PUERTO_ESCUCHA);

    if (socket_kernel < 0)
    {
        log_error(logger, "[KERNEL]: Error intentando iniciar Servidor.");
        return FAILURE;
    }

    log_info(logger, "[KERNEL]: Servidor iniciado correctamente.");
    return SUCCESS;
}

int conectar_con_cpu()
{
    log_info(logger, "[KERNEL] conectando con CPU...");

    socket_cpu_dispatch = crear_conexion_con_servidor(KernelConfig.IP_CPU, KernelConfig.PUERTO_CPU_DISPATCH);
    socket_cpu_interrupt = crear_conexion_con_servidor(KernelConfig.IP_CPU, KernelConfig.PUERTO_CPU_INTERRUPT);

    if (socket_cpu_dispatch < 0 && socket_cpu_interrupt < 0)
    {
        log_error(logger, "[KERNEL]: CPU NO ESTÁ DISPONIBLE, FINALIZANDO EJECUCIÓN");
        return FAILURE;
    }
    log_info(logger, "[KERNEL]: Conexion con CPU establecida");
    //enviar_mensaje_a_servidor("HOLA! SOY KERNEL╰(*°▽°*)╯", socket_cpu);
    return SUCCESS;
}

int conectar_con_memoria()
{
    log_info(logger, "[KERNEL] conectando con Memoria...");

    socket_memoria = crear_conexion_con_servidor(KernelConfig.IP_MEMORIA, KernelConfig.PUERTO_MEMORIA);

    if (socket_memoria < 0)
    {
        log_error(logger, "[KERNEL]: MEMORIA NO ESTÁ DISPONIBLE, FINALIZANDO EJECUCIÓN");
        return FAILURE;
    }
    log_info(logger, "[KERNEL]: Conexion con Memoria: OK %d", socket_memoria);
    //enviar_mensaje_a_servidor("HOLA! SOY KERNEL ╰(*°▽°*)╯", socket_memoria);
    return SUCCESS;
}

int conectar_con_io()
{
    while(true){

        log_info(logger, "[KERNEL] Esperando nueva interfaz IO...");

        int socket_interfaz = esperar_cliente(socket_kernel);
        log_info(logger, "[CPU]: Conexión con IO [%i] establecida.", socket_interfaz);

        //TODO: HILOS
    }
}