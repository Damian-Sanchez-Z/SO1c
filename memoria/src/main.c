#include "../include/main.h"

int main(int argc, char* argv[]) {

    iniciar_logger("Memoria", "configs/memoria.log");

    char* config_path = argv[1];

    iniciar_config_memoria(config_path);

    iniciar_servidor_memoria();

    crear_hilo_operaciones(config.path_instrucciones);

    return EXIT_SUCCESS;

}