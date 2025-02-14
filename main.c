#include "pcb.h"
#include "scheduler.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    pcb_t* ready_list[HIGHEST_PRIO + 1];
    printf("Creating pcb...\n");
    cpu_state_t *state0 = cpu_state_create();
    memory_t *mem0 = memory_create();
    ready_list[2] = pcb_create(NULL, state0, mem0);
    printf("Created pcb\n");
    printf("Scheduling pcb\n");
    pcb_t* task = scheduler_run(ready_list, HIGHEST_PRIO);
    while(task != NULL) {
        printf("Running task\n");
        pcb_run(task);
        free(task);
        task = scheduler_run(ready_list, HIGHEST_PRIO);
    }
    return 0;
}
