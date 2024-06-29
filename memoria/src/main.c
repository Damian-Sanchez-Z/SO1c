#include "../include/main.h"

int socket_cpu;
int socket_kernel;

void conectar_con_cpu()
{
    log_info(logger, "[MEMORIA]: Esperando conexiones de CPU...");
    socket_cpu = esperar_cliente(socket_memoria);
    log_info(logger, "[MEMORIA]: Conexión de CPU establecida.");
    //pthread_create(&hilo_cpu, NULL, (void *)escuchar_cpu, (void *)socket_cpu);
}

void conectar_con_kernel()
{
    log_info(logger, "[MEMORIA]: Esperando conexiones de Kernel...");
    socket_kernel = esperar_cliente(socket_memoria);
    log_info(logger, "[MEMORIA]: Conexión de Kernel establecida.");

    //pthread_create(&hilo_kernel, NULL, (void *)escuchar_kernel, (void *)socket_kernel);
}

int main(int argc, char* argv[]) {

    logger = iniciar_logger_memoria();

    char* config_path = argv[1];

    iniciar_config_memoria(config_path);


    if(iniciar_servidor_memoria() == SUCCESS){

        conectar_con_cpu();

        conectar_con_kernel();

        conectar_con_io();
    }

    close(socket_memoria);
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