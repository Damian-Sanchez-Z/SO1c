#include "../include/main.h"

int main(int argc, char* argv[]) {
    iniciar_logger_cpu();

    char* config_path = argv[1];

    if(iniciar_config_cpu(config_path) == FAILURE)
        return EXIT_FAILURE;

    iniciar_servidor_cpu();

    return EXIT_SUCCESS;
}
