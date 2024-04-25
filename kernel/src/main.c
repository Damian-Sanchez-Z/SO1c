#include <stdlib.h>
#include <stdio.h>
#include <utils.h>

int main(int argc, char* argv[]) {
    
    iniciar_logger_kernel();

    char* config_path = argv[1];

    if(iniciar_config_kernel(config_path) == 0) 
        return EXIT_FAILURE;

    iniciar_servidor_kernel();

    return EXIT_SUCCESS;
}
