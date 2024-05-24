#include"../include/main.h"

void crear_hilo_operaciones(char* path){

    pthread_t hilo_obtener_operaciones;

    pthread_create(hilo_obtener_operaciones, NULL, abrir_archivo_y_enviar_instrucciones, path);

    pthread_detach(hilo_obtener_operaciones);

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
    
    fclose(archivo_instrucciones);

    cargar_y_enviar_instrucciones(contenido_archivo, (tamanio_archivo + 1));

    free(contenido_archivo);

}

void cargar_y_enviar_instrucciones(char* vector_instrucciones, int posicion_caracter_fin){

    char* codop;

    char* operando;

    OPERACION* operacion;

    char* stream;

    stream = (char*) malloc(70 * sizeof(char*));

    operacion = (OPERACION*) malloc(sizeof(OPERACION));

    vector_instrucciones = malloc(posicion_caracter_fin * sizeof(char));

    codop = (char*) malloc(sizeof(char) * 20);

    operando = (char*) malloc(sizeof(char) * 50);

    int contador_operando = 0;

    int contador_codop = 0;

    t_paquete* paquete;

    for(int i=0; i < posicion_caracter_fin; i++){

        if(vector_instrucciones[i] == ' '){

            // i++;                               si quiero o no mandar el char espacio ' ' (con i++ tomo el siguiente caracter)

            do{
                (asignar_a_operando(operacion, operando, contador_operando));

                i++;

                contador_operando ++;

            } while(vector_instrucciones[i] != '\n');


        }

        if(vector_instrucciones[i] == '\n'){

            operando[i+1] = '\0';

            eliminar_paquete(paquete);

            paquete = crear_paquete();

            crear_stream(stream, codop, operando);
            
            agregar_a_paquete(paquete, stream, sizeof(stream));

            serializar_paquete(paquete, sizeof(paquete));

            //sem_wait(llegue pedido);

            retardo_milisegundos(config.retardo_memoria);

            //enviar_paquete(paquete, socket);     

            //sem_post(siguiente); 

            vaciar_string(stream, i);

            vaciar_string(codop, i);

            vaciar_string(operando, i);

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

    free(paquete);

    free(operacion);
}

void asignar_a_codop(OPERACION* operacion, char codop, int contador){

    operacion->codigo_de_operacion[contador] = codop;

}

void asignar_a_operando(OPERACION* operacion, char operando, int contador){

    operacion->operando_de_operacion[contador] = operando;

}

void crear_stream(char* destino, char* unString, char* otroString){

    destino = strcpy(unString, otroString);

}

void vaciar_string(char* string, int ultimo_lugar){

    for(int i=0; i< (ultimo_lugar+1); i++){

        string[i] = '\0';

    }

}


void retardo_milisegundos(int milisegundos){

    int tiempo_microsegundos;

    tiempo_microsegundos = milisegundos * 1000;

    usleep(tiempo_microsegundos);

}