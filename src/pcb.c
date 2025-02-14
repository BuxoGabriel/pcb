#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>

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

void cpu_state_free(cpu_state_t *state) {
    if(state == NULL) {
        fprintf(stderr, "Tried to free cpu_state that does not exist\n");
        return;
    }
    free(state);
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

void memory_free(memory_t *mem) {
    if(mem == NULL) {
        fprintf(stderr, "Tried to free memory that does not exist\n");
    }
    free(mem->address);
    free(mem);
}

// typedef struct scheduling_info {
//     int time_running;
// } scheduling_info_t;

typedef struct file {
    FILE *file;
    file_t *next;
} file_t;

void files_free(file_t *file) {
    if(file == NULL) return;
    fclose(file->file);
    files_free(file->next);
    free(file);
}

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

void pcb_free(pcb_t *pcb) {
    pcb_t *child = pcb->child;
    while(child != NULL) {
        pcb_t *next = child->ys;
        pcb_free(child);
        child = next;
    }
    cpu_state_free(pcb->cpu_state);
    memory_free(pcb->memory);
    files_free(pcb->open_files);
    // If this process has an older sibl
    if(pcb->os) {
        pcb->os->ys = pcb->ys;
    }
    if(pcb->parent && pcb->parent->child == pcb) {
        pcb->parent->child = pcb->ys;
    }
    free(pcb);
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

int pcb_get_state(pcb_t *pcb) {
    if(pcb == NULL) {
        fprintf(stderr, "Tried to get state on NULL pcb\n");
        return -1;
    }
    return pcb->state;
}

void pcb_set_state(pcb_t *pcb, int state) {
    pcb->state = state;
}

pcb_t* pcb_get_next(pcb_t *pcb) {
    if(pcb == NULL) {
        fprintf(stderr, "Tried to get next on NULL pcb\n");
        return NULL;
    }
    return pcb->next;
}

void pcb_set_next(pcb_t *pcb, pcb_t *next) {
    pcb->next = next;
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
