#include "../include/utils.h"

int socket_cpu_dispatch;
int socket_cpu_interrupt;
int socket_cpu;
int socket_memoria;
int socket_kernel;

Config config;


int iniciar_servidor_cpu()
{
    log_info(logger, "[CPU]: Iniciando Servidores De Dispatch e Interrupt...");
    socket_cpu_dispatch = iniciar_servidor(string_itoa(CPUConfig.PUERTO_ESCUCHA_DISPATCH));
    socket_cpu_interrupt = iniciar_servidor(string_itoa(CPUConfig.PUERTO_ESCUCHA_INTERRUPT));

    if (socket_cpu_dispatch < 0 || socket_cpu_interrupt < 0)
    {
        log_error(logger, "[CPU]: Error intentando iniciar Servidores.");
        return FAILURE;
    }

    log_info(logger, "[CPU]: Servidores iniciados correctamente.");
    return SUCCESS;
}

int conectar_con_memoria()
{
    log_info(logger, "[CPU] conectando con memoria...");
    socket_memoria = crear_conexion_con_servidor(CPUConfig.IP_MEMORIA, string_itoa(CPUConfig.PUERTO_MEMORIA));

    if (socket_memoria < 0)
    {
        log_error(logger, "[CPU]: MEMORIA NO ESTÁ DISPONIBLE, FINALIZANDO EJECUCIÓN");
        return FAILURE;
    }
    log_info(logger, "[CPU]: Conexion con Memoria: OK %d", socket_memoria);
    return SUCCESS;
}

void conectar_con_kernel()
{
    log_info(logger, "[CPU]: Esperando conexiones de KERNEL..");

    socket_kernel = esperar_cliente(socket_cpu_dispatch);
    log_info(logger, "[CPU]: Conexión dispatch de KERNEL establecida.", socket_kernel);

    socket_kernel = esperar_cliente(socket_cpu_interrupt);
    log_info(logger, "[CPU]: Conexión interrupt de KERNEL establecida.", socket_kernel);

    //pthread_create(&hilo_kernel, NULL, (void *)manejar_paquete_kernel, (void *)socket_kernel);
    //pthread_join(hilo_kernel, NULL);
}

void terminar_ejecucion()
{
    log_warning(logger, "[CPU]: Finalizando ejecucion...");
    log_destroy(logger);
    config_destroy(config);
}

void asignar_a_registro(char *valor, char *registro_instr, PCB *pcb)
{
    Registro_CPU *reg_cpu = &pcb->registros_cpu;
    //quitar_salto_de_linea(valor);

    if(!strcmp(registro_instr,"AX"))
    {
        strncpy(reg_cpu->AX, valor, 1);
        reg_cpu->AX = '\0';
    }
    else if(!strcmp(registro_instr,"BX"))
    {
        strncpy(reg_cpu->BX, valor, 1);
        reg_cpu->BX = '\0';
    }
    else if(!strcmp(registro_instr,"CX"))
    {
        strncpy(reg_cpu->CX, valor, 1);
        reg_cpu->CX = '\0';
    }
    else if(!strcmp(registro_instr,"DX"))
    {
        strncpy(reg_cpu->DX, valor, 1);
        reg_cpu->DX = '\0';
    }
    else if(!strcmp(registro_instr,"EAX"))
    {
        strncpy(reg_cpu->EAX, valor, 4);
        reg_cpu->EAX = '\0';
    }
    else if(!strcmp(registro_instr,"EBX"))
    {
        strncpy(reg_cpu->EBX, valor, 4);
        reg_cpu->EBX = '\0';
    }
    else if(!strcmp(registro_instr,"ECX"))
    {
        strncpy(reg_cpu->ECX, valor, 4);
        reg_cpu->ECX = '\0';
    }
    else if(!strcmp(registro_instr,"EDX"))
    {
        strncpy(reg_cpu->EDX, valor, 4);
        reg_cpu->EDX = '\0';
    }
    else if(!strcmp(registro_instr,"SI"))
    {
        strncpy(reg_cpu->SI, valor, 4);
        reg_cpu->SI = '\0';
    }
    else if(!strcmp(registro_instr,"DI"))
    {
        strncpy(reg_cpu->DI, valor, 4);
        reg_cpu->DI = '\0';
    } 
    else
    {
        log_error(logger, "CPU: ERROR AL ASIGNAR REGISTRO, NOMBRE DESCONOCIDO");
    }
}

char *obtener_valor_registro(Registro_CPU registros_pcb, char *registro_buscado)
{
    char *valor = malloc(17); // solo lo inicializo, se tiene q pisar
    //quitar_salto_de_linea(registro_buscado);

    if (!strcmp(registro_buscado, "AX"))
    {
        strncpy(valor, registros_pcb.AX, 1);
        valor[1] = '\0';
    }
    else if (!strcmp(registro_buscado, "BX"))
    {
        strncpy(valor, registros_pcb.BX, 1);
        valor[1] = '\0';
    }
    else if (!strcmp(registro_buscado, "CX"))
    {
        strncpy(valor, registros_pcb.CX, 1);
        valor[1] = '\0';
    }
    else if (!strcmp(registro_buscado, "DX"))
    {
        strncpy(valor, registros_pcb.DX, 4);
        valor[4] = '\0';
    }
    else if (!strcmp(registro_buscado, "EAX"))
    {
        strncpy(valor, registros_pcb.EAX, 8);
        valor[8] = '\0';
    }
    else if (!strcmp(registro_buscado, "EBX"))
    {
        strncpy(valor, registros_pcb.EBX, 8);
        valor[8] = '\0';
    }
    else if (!strcmp(registro_buscado, "ECX"))
    {
        strncpy(valor, registros_pcb.ECX, 8);
        valor[8] = '\0';
    }
    else if (!strcmp(registro_buscado, "EDX"))
    {
        strncpy(valor, registros_pcb.EDX, 8);
        valor[8] = '\0';
    }
    else if (!strcmp(registro_buscado, "SI"))
    {
        strncpy(valor, registros_pcb.SI, 8);
        valor[16] = '\0';
    }
    else if (!strcmp(registro_buscado, "DI"))
    {
        strncpy(valor, registros_pcb.DI, 8);
        valor[16] = '\0';
    }
    else
    {
        log_error(logger, "CPU: ERROR AL BUSCAR REGISTRO, NOMBRE DESCONOCIDO");
        free(valor); // Liberar la memoria asignada
        return NULL;
    }
    return valor;
}

int ejecutar_instruccion(Instruccion *Instruccion, PCB *pcb) // EXECUTE //CADA INSTRUCCIÓN DEBE TENER SU log_warning(PID: <PID> - Ejecutando: <INSTRUCCION> - <PARAMETROS>)
{

    PAQUETE *paquete = crear_paquete(INSTRUCCION);

    //quitar_salto_de_linea(nombre_instru);

    if (!strcmp(Instruccion->nombreInstruccion, "SET")) //TODO
    {
        ejecutar_set(paquete, Instruccion, pcb);
        return 1;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "MOV_IN")) //Listo
    {
        //ejecutar_mov_in(paquete, Instruccion, pcb);
        return 1;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "MOV_OUT")) //Listo
    {
        //ejecutar_mov_out(paquete, Instruccion, pcb);
        return 1;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "SUM")) //TODO
    {
        ejecutar_SUM(paquete, Instruccion, pcb);
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "SUB")) //TODO
    {
        ejecutar_SUB(paquete, Instruccion, pcb);
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "JNZ")) //TODO
    {
        ejecutar_jnz(paquete, Instruccion, pcb);
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "RESIZE"))
    {
        //ejecutar_resize();
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "COPY_STRING"))
    {
        //ejecutar_copy_string();
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "IO_GEN_SLEEP")) //TODO
    {
        ejecutar_io_gen_sleep(paquete, Instruccion, pcb); 
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "IO_STDIN_READ"))
    {
        //ejecutar_io_stdin_read();
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "IO_STDOUT_WRITE"))
    {
        //ejecutar_io_stdout_write();
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "WAIT")) //Listo
    {
        //ejecutar_wait(paquete, Instruccion, pcb);
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "SIGNAL")) //Listo
    {
        //ejecutar_signal(paquete, Instruccion, pcb);
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "IO_FS_CREATE")) 
    {
        //ejecutar_io_fs_create();
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "IO_FS_DELETE")) 
    {
        //ejecutar_io_fs_delete();
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "IO_FS_TRUNCATE"))
    {
        //ejecutar_io_fs_truncate();
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "IO_FS_WRITE"))
    {
        //ejecutar_io_fs_write();
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "IO_FS_READ"))
    {
        //ejecutar_io_fs_read();
        return 0;
    }
    else if (!strcmp(Instruccion->nombreInstruccion, "EXIT"))
    {
        //ejecutar_exit(paquete, pcb);
        return 0;
    }
    else
    {
        log_error(logger, "[CPU]: Codigo de Instruccion no encontrado");
        eliminar_paquete(paquete);
        return 0;
    }
}

void ejecutar_set(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb) 
{
    log_warning(logger, "CPU: PID: <%d> - Ejecutando: <SET> - <REGISTRO:%s , VALOR: %s>",
                pcb->PID,
                instruccion->registro,
                instruccion->valor);
    asignar_a_registro(instruccion->valor, instruccion->registro, pcb);
    eliminar_paquete(paquete);
}

//Suma al Registro Destino el Registro Origen y deja el resultado en el Registro Destino.

void ejecutar_SUM(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb) 
{
    log_warning(logger, "CPU: PID: <%d> - Ejecutando: <SUM> - <REGISTRO_DESTINO:%s , REGISTRO_ORIGEN: %s>",
                pcb->PID,
                instruccion->registro_destino,
                instruccion->registro_origen);

    int32_t valor_registro_origen = obtener_valor_registro(pcb->registros_cpu,instruccion->registro_origen);
    int32_t valor_registro_destino = obtener_valor_registro(pcb->registros_cpu,instruccion->registro_destino);
    int32_t resultado = valor_registro_destino + valor_registro_origen;
    
    asignar_a_registro(resultado, instruccion->registro_destino, pcb);
    eliminar_paquete(paquete);
}

//Resta al Registro Destino el Registro Origen y deja el resultado en el Registro Destino.

void ejecutar_SUB(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb) 
{
    log_warning(logger, "CPU: PID: <%d> - Ejecutando: <SUB> - <REGISTRO_DESTINO:%s , REGISTRO_ORIGEN: %s>",
                pcb->PID,
                instruccion->registro_destino,
                instruccion->registro_origen);

    char *valor_registro_origen = obtener_valor_registro(pcb->registros_cpu,instruccion->registro_origen);
    char *valor_registro_destino = obtener_valor_registro(pcb->registros_cpu,instruccion->registro_destino);
    char *resultado = valor_registro_destino - valor_registro_origen;
        
    asignar_a_registro(resultado, instruccion->registro_destino, pcb);
    eliminar_paquete(paquete);
}

//Si el valor del registro es distinto de cero, actualiza el program counter al número de instrucción pasada por parámetro.
void ejecutar_jnz(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb) 
{
    log_warning(logger, "CPU: PID: <%d> - Ejecutando: <JNZ> - <REGISTRO:%s>",
                pcb->PID,
                instruccion->registro);

    char *valor_registro = obtener_valor_registro(pcb->registros_cpu, instruccion->registro);

    if(!valor_registro == 0){
        cambiarValorProgramCounter(valor_registro, pcb);
        log_info(logger,"CAMBIANDO EL VALOR DEL PC...");
        log_info(logger, "EL VALOR DEL PC ES: <%d>",
                 pcb->program_counter);
    }

    eliminar_paquete(paquete);
}

//Esta instrucción solicita al Kernel que se envíe a una interfaz de I/O a que realice un sleep por una cantidad de unidades de trabajo.
//ESTA INSTRUCCION DEBERIA DE ATENDERLA KERNEL
void ejecutar_io_gen_sleep(PAQUETE *paquete, Instruccion *instruccion, PCB *pcb) 
{
    log_warning(logger, "CPU: PID: <%d> - Ejecutando: <IO_GEN_SLEEP> - <INTERFACE:%s , UNIDADES_DE_TRABAJO: %d>",
                pcb->PID,
                instruccion->IO_Interface.nombre,
                instruccion->unidades_de_trabajo);

    PAQUETE *paquete_kernel = crear_paquete(OP_PAQUETE);
    agregar_a_paquete(paquete_kernel, &pcb->PID, sizeof(int32_t));
    agregar_a_paquete(paquete_kernel, &pcb->program_counter, sizeof(int32_t));
    agregar_a_paquete(paquete_kernel, &pcb->registros_cpu, sizeof(Registro_CPU));
    agregar_a_paquete(paquete_kernel, &instruccion->IO_Interface.id,sizeof(int32_t));
    agregar_a_paquete(paquete_kernel, &instruccion->unidades_de_trabajo,sizeof(int32_t));

    enviar_paquete_a_cliente(paquete_kernel, socket_kernel);
    eliminar_paquete(paquete_kernel);
    eliminar_paquete(paquete);
}

//hay que probar esto, no creo que funcione
void cambiarValorProgramCounter(char *valor, PCB *pcb){
    strncpy(pcb->program_counter,valor,4);
    pcb->program_counter = '\0';
}