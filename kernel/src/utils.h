#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include<../../utils/include/cliente.h>
#include<../../utils/include/server.h>

#define ARCHIVO_LOGGER "config/kernel.log"
#define ARCHIVO_CONFIG "config/kernel.config"
#define SUCCESS 0
#define FAILURE -1

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

void iniciar_logger_kernel();
int iniciar_config_kernel(char*);
int iniciar_servidor_kernel();