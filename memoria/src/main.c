#include "../include/main.h"

int main(int argc, char* argv[]) {

    logger = iniciar_logger_memoria();

    char* config_path = argv[1];

    iniciar_config_memoria(config_path);

    iniciar_servidor_memoria();

    // obtener_operacion(config.path_instrucciones);

    return EXIT_SUCCESS;

}

int codigo_de_operacion(char* path){

    int codop;
    FILE* archivo;
    archivo = fopen(path, "r");
    fread(codop, 1, archivo);
    if(fread(codop, 1, archivo) == 0){
        printf("No se pudo leer el archivo");
    }
    return codop;

}


// TENGO QUE DEFINIR UNA CANTIDAD DE BYTES PARA EL OPERANDO POR OPERACION

char* operando_de_operacion(char* path){


    int cantidad_bytes_operacion;


    char* operando = malloc(sizeof(char));
    FILE* archivo;
    archivo = fopen(path, "r");
    fread(operando, cantidad_bytes_operacion, archivo);
    if(fread(operando, cantidad_bytes_operacion, archivo) == 0){
        printf("No se pudo obtener el operando");
    }
    return operando;    
    free(operando);

}

OPERACION* obtener_operacion(char* path){

    OPERACION* operacion = malloc(sizeof(OPERACION));
    int codop;
    char* operando;
    codop = codigo_de_operacion(path);
    operando = operando_de_operacion(path);
    operacion.codigo_de_operacion = codop;
    operacion.operando_de_operacion = operando;
    return operacion;
    free(operacion);

}