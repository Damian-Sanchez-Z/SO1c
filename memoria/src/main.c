#include "main.h"

int main(int argc, char* argv[]) {

    iniciar_logger_memoria();

    char* config_path = argv[1];

    iniciar_config_memoria(config_path);

    iniciar_servidor_memoria();

    return EXIT_SUCCESS;

}
