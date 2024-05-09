#include <include/main.h>
int socket_clienteDeKernel;
int socket_clienteDeMemoria;

int main(int argc, char* argv[]) {
    
    iniciar_logger_interfaz();

    char* config_path = argv[1];

    if(iniciar_config_interfaz(config_path) == 0) 
        return EXIT_FAILURE;

    log_info(logger, "[INTERFAZ]: Conexion con KERNEL:.");
    socket_clienteDeKernel = iniciar_cliente_interfaz(interfazConfig.IP_KERNEL, interfazConfig.PUERTO_KERNEL);
    log_info(logger, "[INTERFAZ]: Conexion con MEMORIA:.");
    socket_clienteDeMemoria = iniciar_cliente_interfaz(interfazConfig.IP_MEMORIA, interfazConfig.PUERTO_MEMORIA);
    return EXIT_SUCCESS;
}

