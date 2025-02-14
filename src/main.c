#include "pcb.h"
#include "scheduler.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIO 5

int main(void) {
    printf("Creating scheduler...\n");
    scheduler_t *scheduler = scheduler_create(MAX_PRIO);
    printf("Created scheduler\n");
    printf("Creating pcbs...\n");
    cpu_state_t *state0 = cpu_state_create();
    memory_t *mem0 = memory_create();
    pcb_t *pcb0 = pcb_create(NULL, state0, mem0);
    cpu_state_t *state1 = cpu_state_create();
    memory_t *mem1 = memory_create();
    pcb_t *pcb1 = pcb_create(NULL, state1, mem1);
    cpu_state_t *state2 = cpu_state_create();
    memory_t *mem2 = memory_create();
    pcb_t *pcb2 = pcb_create(NULL, state2, mem2);
    printf("Scheduling pcbs...\n");
    scheduler_schedule(scheduler, pcb0, 2);
    scheduler_schedule(scheduler, pcb1, 2);
    scheduler_schedule(scheduler, pcb2, 4);
    printf("Running pcbs...\n");
    while(!scheduler_run(scheduler)) {}
    printf("Ran all pcbs!\n");
    return 0;
}
