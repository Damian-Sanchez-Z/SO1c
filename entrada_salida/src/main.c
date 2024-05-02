#include <stdlib.h>
#include <stdio.h>
#include "../include/config.h"

int main(int argc, char* argv[]) {
    iniciar_logger_io();

    char* config_path = argv[1];

    if(iniciar_config_io(config_path) == FAILURE)
        return EXIT_FAILURE;

    iniciar_servidor_io();

    return EXIT_SUCCESS;
}
