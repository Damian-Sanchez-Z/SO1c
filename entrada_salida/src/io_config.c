#include <io_config.h>

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