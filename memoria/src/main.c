#include "../include/main.h"

int main(int argc, char* argv[]) {

    iniciar_logger("Memoria", "configs/memoria.log");

    char* config_path = argv[1];

    iniciar_config_memoria(config_path);

    int socket_memoria = iniciar_servidor_memoria();

    //crear_hilo_operaciones(config.path_instrucciones);

     while(1){
        int *conexion = malloc(sizeof(int));
        *conexion = esperar_cliente(socket_memoria);
        if(*conexion>0){
            pthread_t unHilo;
            pthread_create(&unHilo, NULL, atender_cliente, (void*)conexion);
            pthread_detach(unHilo);
        }else{
            free(conexion);
        }
    }
    close(socket_memoria);
    return EXIT_SUCCESS;
}
void* atender_cliente(void *unCliente){
    int* cliente =  unCliente;
    int confirmacion = handshake_con_cliente(*cliente);
    free(cliente);
    close(*cliente);
    return NULL;
}