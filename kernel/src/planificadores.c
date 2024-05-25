#include "../include/planificadores.h"

t_list new_state;
t_list ready_state;
t_list block_state;
t_list exit_state;

int64_t PID;

PCB* enviarACPU(PCB* pcb){
    PAQUETE *paquete_pcb = crear_paquete(OP_PCB);

    paquete_pcb->buffer = serializar_pcb(pcb);

    Instruccion* instruccion_enviar = list_get(&pcb->instructions, pcb->programCounter);

    enviar_paquete_a_servidor(paquete_pcb, socket_cpu);

    eliminar_paquete(paquete_pcb);

    return &pcb;
}

void fifo(){
    while(true){
        if(list_size(&ready_state) > 0){
            PCB* actualProcess = list_remove(&ready_state, 0);
            while(true){
                enviarACPU(&actualProcess);
                actualProcess->programCounter++;
                if(list_size(&actualProcess->instructions) > actualProcess->programCounter){
                    list_add(&exit_state, &actualProcess);
                    break;
                }
            }
        }
    }
}


void roundRobin(){
    uint32_t quantum = KernelConfig.QUANTUM;
    while(true){
        if(list_size(&ready_state) > 0){
            PCB* actualProcess = list_remove(&ready_state, 0);
            while(true){
                enviarACPU(&actualProcess);
                actualProcess->programCounter++;
                if(list_size(&actualProcess->instructions) > actualProcess->programCounter){
                    list_add(&exit_state, &actualProcess);
                    break;
                } else if (actualProcess->programCounter % quantum == 0){
                    list_add(&ready_state, &actualProcess);
                    break;
                }
            }
        }
    }
}


void ejecutarPlanificacion(){
    char* planificador = KernelConfig.ALGORITMO_PLANIFICACION;
    ready_state = *list_create();
    exit_state = *list_create();
    if(planificador == "FIFO"){
        fifo();
    } else if(planificador == "RR") {
        roundRobin();
    }
}

PCB* CrearPcb(){

    PCB *pcb = malloc(sizeof(PCB));
    pcb->pid= PID;
    PID++;
    pcb->programCounter = 0;
    pcb->instructions = *list_create();
    pcb->quantum = 0;
    pcb->registers.AX = 0;
    pcb->registers.BX = 0;
    pcb->registers.CX = 0;
    pcb->registers.DX = 0;
    pcb->registers.EAX = 0;
    pcb->registers.EBX = 0;
    pcb->registers.ECX = 0;
}
