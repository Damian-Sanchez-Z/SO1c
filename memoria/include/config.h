//
// Created by utnso on 5/2/24.
//

#ifndef MEMORIA_CONFIG_H
#define MEMORIA_CONFIG_H

#include "../include/main.h"

void iniciar_config_memoria(char* config_path);
int iniciar_servidor_memoria();

extern int socket_memoria;

extern const char* ip = "localhost:3000";

#endif //MEMORIA_CONFIG_H