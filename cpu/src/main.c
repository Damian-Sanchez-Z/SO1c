#include "../include/main.h"

int main(int argc, char* argv[]) {

    char* config_path = argv[2];

    logger = iniciar_logger("CPU", "cpu.log");

    if(iniciar_config_cpu(config_path) == FAILURE)
        return EXIT_FAILURE;

    socket_cpu = iniciar_servidor_cpu();

    int respuesta_conexion = conectar_con_memoria();
    if(respuesta_conexion != SUCCESS)
    {       
        terminar_ejecucion();
        return EXIT_FAILURE;
        // liberar_conexion_con_servidor(conexionMemoria);
        //free(mensaje); //Luego de inicializar el char* corresponde usar free para liberar la memoria utilizada
    }
  
    conectar_con_kernel();

    while(1){}

    terminar_ejecucion();
    
    return EXIT_SUCCESS;
}
