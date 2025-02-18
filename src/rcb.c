#include "pcb.h"
#include "rcb.h"
#include "scheduler.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct rcb {
    int state;
    pcb_t *waiting_list;
    pcb_t *waiting_list_tail;
    rcb_t *next;
} rcb_t;

rcb_t* rcb_create() {
    rcb_t *rcb = malloc(sizeof(rcb_t));
    rcb->state = RCB_FREE;
    rcb->waiting_list = NULL;
    rcb->waiting_list_tail = NULL;
    rcb->next = NULL;
    return rcb;
}

rcb_t* rcb_get_next(rcb_t *rcb) {
    return rcb->next;
}

void rcb_set_next(rcb_t *rcb, rcb_t *next) {
    rcb->next = next;
}

void rcb_push_waiting(rcb_t *rcb, pcb_t *waiting) {
    if(rcb->waiting_list == NULL) {
        rcb->waiting_list = waiting;
    } 
    pcb_set_next(rcb->waiting_list_tail, waiting);
    rcb->waiting_list_tail = waiting;
}

pcb_t* rcb_pop_waiting(rcb_t *rcb) {
    if(rcb->waiting_list == NULL) {
        return NULL;
    } 
    pcb_t *result = rcb->waiting_list;
    pcb_t *next = pcb_get_next(rcb->waiting_list);
    rcb->waiting_list = next;
    if(next == NULL) {
        rcb->waiting_list_tail = NULL;
    }
    return result;
}

void rcb_request(rcb_t *rcb, pcb_t *pcb, scheduler_t *scheduler) {
    if(rcb->state == RCB_FREE) {
        // If RCB is free allocate it to the pcb that requested it
        pcb_add_resource(pcb, rcb);
        rcb->state = RCB_ALLOCATED;
    } else {
        // If RCB is allocated set pcb to blocked, add pcb to resources waiting list, and call scheduler
        pcb_set_state(pcb, PCB_BLOCKED);
        rcb_push_waiting(rcb, pcb);
        scheduler_run(scheduler);
    }
}

void rcb_release(rcb_t *rcb, scheduler_t *scheduler) {
    // Check if any pcbs are int he waiting list
    pcb_t *waiting = rcb_pop_waiting(rcb);
    if(waiting == NULL) {
        // If no pcbs are waiting, this resource is free
        rcb->state = RCB_FREE;
    } else {
        // If a pcb was waiting for this resource give it the resource, call the scheduler
        pcb_add_resource(waiting, rcb);
        scheduler_run(scheduler);
    }
}
