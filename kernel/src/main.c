#include <stdlib.h>
#include <stdio.h>
#include "../include/utils.h"

t_log* logger;

int main(int argc, char** argv) {

    logger = iniciar_logger("Kernel", "kernel.log");

    char* config_path = argv[1];

    if(iniciar_config_kernel(config_path) == FAILURE)
        return EXIT_FAILURE;


    if (iniciar_servidor_kernel() == SUCCESS)
    {
        if (conectar_con_memoria() == FAILURE)
            return EXIT_FAILURE;

        if (conectar_con_cpu() == FAILURE)
            return EXIT_FAILURE;

        conectar_con_io();
    }

    return EXIT_SUCCESS;
}

