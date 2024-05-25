#include "../include/main.h"

int main(int argc, char* argv[]) {
    iniciar_logger_cpu();

    char* config_path = argv[1];

    if(iniciar_config_cpu(config_path) == FAILURE)
        return EXIT_FAILURE;

    iniciar_servidor_cpu(argv[0]);

    int respuesta_conexion = conectar_con_memoria();
    if(respuesta_conexion != SUCCESS)
    {       
        terminar_ejecucion();
        return EXIT_FAILURE;
        // liberar_conexion_con_servidor(conexionMemoria);
        //free(mensaje); //Luego de inicializar el char* corresponde usar free para liberar la memoria utilizada
    }
  
    conectar_con_kernel();
    terminar_ejecucion();
    
    return EXIT_SUCCESS;
}
