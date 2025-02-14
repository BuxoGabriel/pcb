#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>

enum PCB_STATES {
    READY,
    BLOCKED,
    RUNNING
};

typedef struct cpu_state {
    int stack_pointer;
    int r1;
    int r2;
} cpu_state_t;

cpu_state_t *cpu_state_create() {
    cpu_state_t *state0 = malloc(sizeof(cpu_state_t));
    state0->stack_pointer = 0;
    state0->r1 = 0;
    state0->r2 = 0;
    return state0;
}

typedef struct memory {
    void *address;
    int size;
} memory_t;

memory_t *memory_create() {
    void *address = malloc(PCB_MEM_SIZE);
    memory_t *mem0 = malloc(sizeof(memory_t));
    mem0->address = address;
    mem0->size = PCB_MEM_SIZE;
    return mem0;
}

// typedef struct scheduling_info {
//     int time_running;
// } scheduling_info_t;

typedef struct file {
    int file;
    file_t *next;
} file_t;

typedef struct pcb {
    cpu_state_t *cpu_state;
    int state;
    memory_t *memory;
    file_t *open_files;
    pcb_t *next;
    pcb_t *parent;
    pcb_t *child;
    pcb_t *os;
    pcb_t *ys;
} pcb_t;

pcb_t* pcb_create(pcb_t *parent, cpu_state_t *state0, memory_t *mem0) {
    pcb_t *pcb = malloc(sizeof(pcb_t));
    if(pcb == NULL) {
        fprintf(stderr, "Failed to allocate enough space for pcb\n");
        exit(1);
    }
    pcb->cpu_state = state0;
    pcb->state = READY;
    pcb->memory = mem0;
    pcb->open_files = NULL;
    pcb->next = NULL;
    pcb->parent = parent;
    pcb->child = NULL;
    pcb_t *os = pcb_get_last_child(parent);
    pcb->os = os;
    pcb->ys = NULL;
    if(os != NULL) {
        os->ys = pcb;
    }
    return pcb;
}

pcb_t* pcb_get_last_child(const pcb_t *parent) {
    if(parent == NULL) return NULL;
    pcb_t *child = parent->child;
    if(child == NULL) return NULL;
    while(child->ys != NULL) {
        child = child->ys;
    }
    return child;
}

pcb_t* pcb_get_next(pcb_t *pcb) {
    if(pcb == NULL) {
        fprintf(stderr, "Tried to get next on NULL pcb\n");
        return NULL;
    }
    return pcb->next;
}

void pcb_run(const pcb_t *pcb) {
    if(pcb == NULL) {
        fprintf(stderr, "Tried to run NULL pcb\n");
        return;
    }
    char* state;
    switch(pcb->state) {
        case READY:
        state = "ready";
        break;
        case BLOCKED:
        state = "blocked";
        break;
        case RUNNING:
        state = "running";
        break;
    }
    printf("pcb at %p is %s\n", pcb, state);
}
