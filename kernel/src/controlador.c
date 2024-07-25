#include "../include/controlador.h"
#include "../include/utils.h"

t_list *crear_recursos(char **recursos, char **instancias_recursos)
{
    log_info(logger, "[KERNEL]: Crear recursos");

    t_list *lista_recursos = list_create();

    int i = 0;

    while (recursos[i] != NULL)
    {

        Recurso *recurso = malloc(sizeof(Recurso));
        recurso->nombre = recursos[i];
        recurso->instancias_maximas = atoi(instancias_recursos[i]);
        recurso->instancias = 0;
        recurso->cola_block = queue_create();

        list_add(lista_recursos, recurso);
        i++;
    }

    return lista_recursos;
}

Recurso *encontrarRecurso(const char *nombre)
{
    bool comparar_recursos_nombre(Recurso * recurso)
    {
        return recurso->nombre == nombre;
    }

    Recurso *recurso = list_find(lista_recursos, (void *)comparar_recursos_nombre);
    return recurso;
}

int *manejar_wait(Proceso *proceso, char *nombre_recurso)
{
    Recurso *recurso = encontrarRecurso(nombre_recurso);
    if (recurso == NULL)
    {
        // Recurso no existe, enviar proceso a EXIT
        printf("Proceso enviado a EXIT (recurso %s no existe)\n", nombre_recurso);
        return EXIT;
    }

    if (recurso->instancias > 0)
    {
        recurso->instancias -= 1;        

        log_warning(logger, "[KERNEL]: PID: <%d> - WAIT: %s - INSTANCIAS: %d", proceso->pcb->PID, nombre_recurso, recurso->instancias);

        proceso->pcb->program_counter++;
        queue_push(cola_ready, proceso);
        imprimir_cola(*cola_ready);
    }
    else
    {

        log_warning(logger, "[KERNEL] PID: <%d> - Bloqueado por: %s", proceso->pcb->PID, nombre_recurso);

        queue_push(recurso->cola_block, proceso);
    }
}

int *manejar_signal(Proceso *proceso, char *nombre_recurso)
{
    Recurso *recurso = encontrarRecurso(nombre_recurso);
    if (recurso  == NULL)
    {
        // Recurso no existe, enviar proceso a EXIT
        printf("Proceso enviado a EXIT (recurso %s no existe)\n", nombre_recurso);
        return EXIT;
    }
    
    recurso->instancias += 1;

    int a_borrar;

    log_warning(logger, "[KERNEL]: PID: <%d> - SIGNAL: %s - INSTANCIAS: %d", proceso->pcb->PID, nombre_recurso, recurso->instancias);

    if (!queue_is_empty(recurso->cola_block))
    {
        recurso->instancias -= 1;
    
        Proceso *proceso_bloqueado = (Proceso *)queue_pop(recurso->cola_block);
    

        proceso_bloqueado->pcb->program_counter++;
        queue_push(cola_ready, proceso_bloqueado);
        imprimir_cola(*cola_ready);
    }

    queue_push(cola_ready, proceso);
    imprimir_cola(*cola_ready);
}

void imprimir_cola(t_queue cola)
{
    t_queue *copia = queue_create();
    Proceso *paraImprimir;
    int elementos = queue_size(&cola);

    char *lista_pids = string_new();
    string_append(&lista_pids, "[ ");

    for (int i = 0; i < elementos; i++)
    {
        paraImprimir = (Proceso *)queue_pop(&cola);
        string_append_with_format(&lista_pids, " %s ", string_itoa(paraImprimir->pcb->PID));
        // log_info(logger, "Proceso ID : %d ", paraImprimir->pcb->PID);
        queue_push(copia, (Proceso *)paraImprimir);
    }

    string_append(&lista_pids, " ]");

    log_warning(logger, "Cola Ready %s: %s ", KernelConfig.ALGORITMO_PLANIFICACION, lista_pids);

    queue_destroy(cola_ready); //TODO VERIFICAR
    cola_ready = copia;

    free(lista_pids);
}