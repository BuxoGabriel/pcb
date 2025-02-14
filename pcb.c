#include <stdlib.h>

#define PCB_MEM_SIZE 1000

typedef struct pcb pcb_t;
typedef struct file file_t;

int first_available_index(void *arr[], int size);
pcb_t* get_last_child(const pcb_t *parent);

enum PCB_STATES {
    READY,
    BLOCKED,
    RUNNING
};

typedef struct cpu_state {
    int stack_pointer;
    int gen_1;
    int gen_2;
    int gen_3;
    int gen_4;
} cpu_state_t;

cpu_state_t cpu_state_create() {
    cpu_state_t state0 = { 0, 0, 0, 0, 0 };
    return state0;
}

typedef struct memory {
    void *address;
    int size;
} memory_t;

memory_t memory_create() {
    void *address = malloc(PCB_MEM_SIZE);
    memory_t mem0 = { address, PCB_MEM_SIZE };
    return mem0;
}

typedef struct file {
    int file;
    file_t *next;
} file_t;

typedef struct pcb {
    cpu_state_t cpu_state;
    int state;
    memory_t memory;
    file_t* open_files;
    pcb_t *next;
    pcb_t *parent;
    pcb_t *child;
    pcb_t *os;
    pcb_t *ys;
} pcb_t;

pcb_t* pcb_create(pcb_t *pcbs[], int size, pcb_t *parent, cpu_state_t state0, memory_t mem0) {
    int index = first_available_index((void **) pcbs, size);
    if(index == -1) return NULL;
    pcb_t *pcb = malloc(sizeof(pcb_t));
    pcb->cpu_state = state0;
    pcb->state = READY;
    pcb->memory = mem0;
    pcb->open_files = NULL;
    pcb->next = NULL;
    pcb->parent = parent;
    pcb->child = NULL;
    pcb_t *os = get_last_child(parent);
    os->ys = pcb;
    pcb->os = os;
    pcb->ys = NULL;
    return pcb;
}

int first_available_index(void *arr[], int size) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == NULL) {
            return i;
        }
    }
    return -1;
}

pcb_t* get_last_child(const pcb_t *parent) {
    pcb_t *child = parent->child;
    if(child == NULL) return NULL;
    while(child->ys != NULL) {
        child = child->ys;
    }
    return child;
}

int main(void) {
    pcb_t* pcbs[20];
    pcb_t* priority[5];

    cpu_state_t state0 = cpu_state_create();
    memory_t mem0 = memory_create();
    priority[4] = pcb_create(pcbs, 20, NULL, state0, mem0);

    return 0;
}
