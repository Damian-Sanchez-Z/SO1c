#include <stdlib.h>
#include <stdio.h>
#include "../include/utils.h"

t_log* logger;

int main(int argc, char** argv) {

    logger = iniciar_logger("Kernel", "kernel.log");

    log_info(logger, "A1");

    char* config_path = argv[1];

    log_info(logger, "A2");

    if(iniciar_config_kernel(config_path) == FAILURE)
        return EXIT_FAILURE;

    log_info(logger, "A3");

    iniciar_servidor_kernel();

    log_info(logger, "A4");

    return EXIT_SUCCESS;
}


