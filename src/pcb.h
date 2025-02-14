#pragma once

#define PCB_MEM_SIZE 100

typedef struct cpu_state cpu_state_t;
typedef struct memory memory_t;
typedef struct file file_t;
typedef struct pcb pcb_t;

enum PCB_STATES {
    READY,
    BLOCKED,
    RUNNING
};

int first_available_index(void *arr[], int size);
pcb_t* pcb_get_last_child(const pcb_t *parent);

cpu_state_t *cpu_state_create();
memory_t *memory_create();

pcb_t *pcb_create(pcb_t *parent, cpu_state_t *state0, memory_t *mem0);
void pcb_free(pcb_t *pcb);
void pcb_set_state(pcb_t *pcb, int state);
int pcb_get_state(pcb_t *pcb);
void pcb_set_next(pcb_t *pcb, pcb_t *next);
pcb_t* pcb_get_next(pcb_t *pcb);
void pcb_run(const pcb_t *pcb);
