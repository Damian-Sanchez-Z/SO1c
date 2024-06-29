#ifndef MEMORIA_MAIN_H
#define MEMORIA_MAIN_H
#include<stdio.h>
#include<stdlib.h>
#include"string.h"
#include <commons/log.h>
#include <commons/string.h>
#include <commons/config.h>
#include<readline/readline.h>

#include "../include/logger.h"
#include "../include/config.h"

t_log* logger;

void *atender_cliente(void *args);
#endif