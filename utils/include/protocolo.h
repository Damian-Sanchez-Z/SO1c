#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <commons/config.h>
#include <commons/log.h>
#include <commons/temporal.h>
#include <math.h>
#include <time.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>
#include <commons/bitarray.h>
#include <commons/collections/dictionary.h>

// #include <list.h>
#include <commons/string.h>
#include "cliente.h"
#include "server.h"
#include "socket.h"

typedef t_config Config;
typedef t_list Lista;

typedef enum
{
    GENERICA,
    STDIN,
    STDOUT,
    DIALFS,

} TIPO_INTERFAZ;

#endif