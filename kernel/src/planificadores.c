#include "../include/planificadores.h"

t_list new_state;
t_list ready_state;
t_list block_state;
t_list exit_state;

int64_t PID;

PCB* enviarACPU(PCB* pcb){
    PAQUETE * paquete_pcb = crear_paquete(OP_PCB);

    paquete_pcb->buffer = serializar_pcb(pcb);

    Instruccion* instruccion_enviar = list_get(&pcb->instructions, pcb->program_counter);

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
                actualProcess->program_counter++;
                if(list_size(&actualProcess->instructions) > actualProcess->program_counter){
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
                actualProcess->program_counter++;
                if(list_size(&actualProcess->instructions) > actualProcess->program_counter){
                    list_add(&exit_state, &actualProcess);
                    break;
                } else if (actualProcess->program_counter % quantum == 0){
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
    pcb->PID = PID;
    PID++;
    pcb->program_counter = 0;
    pcb->instructions = *list_create();
    pcb->quantum = 0;
    pcb->registros_cpu.PC = 0;
    pcb->registros_cpu.AX = 0;
    pcb->registros_cpu.BX = 0;
    pcb->registros_cpu.CX = 0;
    pcb->registros_cpu.DX = 0;
    pcb->registros_cpu.EAX = 0;
    pcb->registros_cpu.EBX = 0;
    pcb->registros_cpu.ECX = 0;
    pcb->registros_cpu.EDX = 0;
    pcb->registros_cpu->SI = 0;
    pcb->registros_cpu->DI = 0;
}
