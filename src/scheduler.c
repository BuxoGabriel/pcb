#include "pcb.h"
#include "scheduler.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct scheduler {
    pcb_t** ready_list;
    pcb_t* running;
    int max_prio;
} scheduler_t;

scheduler_t* scheduler_create(int max_prio) {
    scheduler_t *scheduler = malloc(sizeof(scheduler_t));
    pcb_t** ready_list = malloc(sizeof(pcb_t*) * (max_prio + 1));
    scheduler->ready_list = ready_list;
    scheduler->max_prio = max_prio;
    scheduler->running = NULL;
    return scheduler;
}

int scheduler_schedule(scheduler_t *scheduler, pcb_t *pcb, int prio) {
    if(prio > scheduler->max_prio || prio < 0) return 1;
    pcb_t *head = scheduler->ready_list[prio];
    if(head == NULL) {
        scheduler->ready_list[prio] = pcb;
        return 0;
    }
    while(pcb_get_next(head) != NULL) {
        head = pcb_get_next(head);
    }
    pcb_set_next(head, pcb);
    return 0;
}

int scheduler_run(scheduler_t *scheduler) {
    pcb_t *highest_prio_pcb = NULL;
    int prio = scheduler->max_prio;
    while(prio >= 0) {
        pcb_t *pcb = scheduler->ready_list[prio];
        if(pcb != NULL) {
            highest_prio_pcb = pcb;
            scheduler->ready_list[prio] = pcb_get_next(highest_prio_pcb);
            break;
        }
        prio--;
    }
    if(highest_prio_pcb == NULL) return 1;
    pcb_set_state(highest_prio_pcb, PCB_RUNNING);
    pcb_run(highest_prio_pcb);
    pcb_free(highest_prio_pcb, scheduler);
    return 0;
}
