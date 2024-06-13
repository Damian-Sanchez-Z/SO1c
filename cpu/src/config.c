#include "../include/config.h"

CPU_CONFIG CPUConfig;

int iniciar_config_cpu(char* path){

    t_config* config = config_create(path);
    if(config == NULL)
    {
        log_error(logger,"[KERNEL]: ERROR AL INICIAR CONFIG INICIAL");
        return FAILURE;
    }

    CPUConfig.IP_MEMORIA = config_get_string_value(config, "IP_MEMORIA");
    CPUConfig.PUERTO_MEMORIA = config_get_int_value(config, "PUERTO_MEMORIA");
    CPUConfig.PUERTO_ESCUCHA_DISPATCH = config_get_int_value(config, "PUERTO_ESCUCHA_DISPATCH");
    CPUConfig.PUERTO_ESCUCHA_INTERRUPT = config_get_int_value(config, "PUERTO_ESCUCHA_INTERRUPT");
    CPUConfig.CANTIDAD_ENTRADAS_TLB = config_get_int_value(config, "CANTIDAD_ENTRADAS_TLB");
    CPUConfig.ALGORITMO_TLB = config_get_string_value(config, "ALGORITMO_TLB");
}