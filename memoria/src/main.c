#include "../include/main.h"

int main(int argc, char* argv[]) {

    logger = iniciar_logger_memoria();

    char* config_path = argv[1];

    iniciar_config_memoria(config_path);

    iniciar_servidor_memoria();

    // obtener_operacion(config.path_instrucciones);

    // crear_hilo_operaciones();

    return EXIT_SUCCESS;

}

void abrir_archivo_y_enviar_instrucciones(char* path){

    long tamanio_archivo;

    char* contenido_archivo;

    FILE* archivo_instrucciones;

    archivo_instrucciones = fopen(path, "r");

    if(archivo_instrucciones == NULL){

        printf("No se pudo abrir el archivo");

        return;

    }

    fseek(archivo_instrucciones, 0, SEEK_END);                          // busco el final del archivo para saber cual es el tamanio

    tamanio_archivo = ftell(archivo_instrucciones);

    rewind(archivo_instrucciones);                               //vuelvo a apuntar al principio del archivo

    contenido_archivo = (char *) malloc(tamanio_archivo + 1);      // casteo a char* y reservo memoria

    if(contenido_archivo == NULL){

        printf("No se pudo reservar memoria");

        return;
    }

    fread(contenido_archivo, 1, tamanio_archivo, archivo_instrucciones);

    contenido_archivo[tamanio_archivo + 1] = '\0';        //asigno caracter de fin de string

    cargar_y_enviar_instrucciones(contenido_archivo, (tamanio_archivo + 1));

    free(contenido_archivo);

    fclose(archivo_instrucciones);

}

void cargar_y_enviar_instrucciones(char* vector_instrucciones, long posicion_caracter_fin){

    char* codop;

    char* operando;

    OPERACION* operacion;

    operacion = (OPERACION*) malloc(sizeof(OPERACION));

    vector_instrucciones = malloc(posicion_caracter_fin * sizeof(char));

    codop = (char*) malloc(sizeof(char) * 20);

    operando = (char*) malloc(sizeof(char) * 50);

    int contador_operando = 0;

    int contador_codop = 0;

    t_paquete paquete;

    for(int i=0; i < posicion_caracter_fin; i++){

        if(vector_instrucciones[i] == ' '){

            i++;

            do{
                (asignar_a_operando(operacion, operando, contador_operando));

                i++;

                contador_operando ++;

            } while(vector_instrucciones[i] != '\n');


        }

        if(vector_instrucciones[i] == '\n'){

            //wait(llegue pedido);

            //crear_paquete();

            //enviar_paquete(); 

            //signal(puedo enviar);


            i++;

            contador_codop = 0;

            contador_operando = 0;

        }

        asignar_a_codop(operacion, codop, contador_codop);

        contador_codop ++;        

    }

    free(codop);

    free(operando);

    free(vector_instrucciones);
}

void asignar_a_codop(OPERACION* operacion, char codop, int contador){

    operacion->codigo_de_operacion[contador] = codop;

}

void asignar_a_operando(OPERACION* operacion, char operando, int contador){

    operacion->operando_de_operacion[contador] = operando;

}


void crear_hilo_operaciones(char* path){

    pthread_t hilo_obtener_operaciones;

    pthread_create(hilo_obtener_operaciones, NULL, abrir_archivo_y_enviar_instrucciones, path);

    pthread_detach(hilo_obtener_operaciones);

}

