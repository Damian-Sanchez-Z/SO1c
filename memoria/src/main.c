#include "../include/main.h"

int main(int argc, char* argv[]) {

    logger = iniciar_logger_memoria();

    char* config_path = argv[1];

    iniciar_config_memoria(config_path);

    socket_memoria = iniciar_servidor_memoria();
   while(1){
        //pthread_t unHilo;
        int *socket_cliente = malloc(sizeof(int));
        *socket_cliente = esperar_cliente(socket_memoria);
        if(*socket_cliente>0){
        log_info(logger,"Cliente: %i", *socket_cliente);
        free(socket_cliente);
        break; }
        //pthread_create(&unHilo, NULL, atender_cliente, socket_cliente);
        //pthread_detach(unHilo);
    }
    close(socket_memoria);
    free(logger);
    return EXIT_SUCCESS;

}
/////// atender cliente

//void *atender_cliente(void *args){
  //  printf("hilo creado para cliente");
   // int *cliente = args;
   // enviar_mensaje_a_cliente("Holis", *cliente);
   // char* mensaje;
   // recibir_mensaje(*cliente, mensaje);
//}