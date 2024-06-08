//
// Created by utnso on 6/8/24.
//

#include"../include/main.h"

#ifndef MEMORIA_INSTRUCCIONES_H
#define MEMORIA_INSTRUCCIONES_H

#endif //MEMORIA_INSTRUCCIONES_H

void retardo_milisegundos(int milisegundos);
void vaciar_string(char* string, int ultimo_lugar);
void crear_stream(char* destino, char* unString, char* otroString);
void asignar_a_operando(OPERACION* operacion, char caracter_operando, int contador);
void asignar_a_codop(OPERACION* operacion, char caracter_codop, int contador);
void cargar_y_enviar_instrucciones(char* vector_instrucciones, int posicion_caracter_fin);
void abrir_archivo_y_enviar_instrucciones(char* path);
void crear_hilo_operaciones(char* path);