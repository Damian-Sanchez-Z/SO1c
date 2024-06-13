#include "../include/main.h"
int main(int argc, char* argv[]) {
    
    nombre = argv[2];
    iniciar_logger_interfaz();

    char* config_path = argv[1];

    if(iniciar_config_interfaz(config_path) == FAILURE) 
        return EXIT_FAILURE;

    if(tipo_interfaz == GENERICA){
            conexion_con_kernel = iniciar_cliente_interfaz(configuracion.IP_KERNEL, configuracion.PUERTO_KERNEL, "KERNEL");
            //int confirmacion_kernel = handshake_con_servidor(conexion_con_kernel);
    }else{
            conexion_con_kernel = iniciar_cliente_interfaz(configuracion.IP_KERNEL, configuracion.PUERTO_KERNEL, "KERNEL");
            conexion_con_memoria = iniciar_cliente_interfaz(configuracion.IP_MEMORIA, configuracion.PUERTO_MEMORIA, "MEMORIA");
            //int confirmacion_kernel = handshake_con_servidor(conexion_con_kernel);
            //int confirmacion_memoria = handshake_con_servidor(conexion_con_memoria);
    }
    return EXIT_SUCCESS;
}

