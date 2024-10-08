#include "../include/cliente.h"


int crear_conexion_con_servidor(char *ip, char *puerto)
{
  struct addrinfo hints;
  struct addrinfo *servinfo;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(ip, puerto, &hints, &servinfo);

  int socketCliente = socket(servinfo->ai_family,
                             servinfo->ai_socktype,
                             servinfo->ai_protocol);

  bool conexion = !(connect(socketCliente, servinfo->ai_addr, servinfo->ai_addrlen));
  freeaddrinfo(servinfo);

  return conexion ? socketCliente : -1;
}

void liberar_conexion_con_servidor(int socketCliente)
{
  close(socketCliente);
}

void terminar_programa(int socket, t_config *config, t_log *logger)
{
  liberar_conexion_con_servidor(socket);
  config_destroy(config);
  log_destroy(logger);
}