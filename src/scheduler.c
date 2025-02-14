#include "pcb.h"
#include "scheduler.h"

#include <stdio.h>
#include <stdlib.h>

pcb_t* scheduler_run(pcb_t** ready_list, int prio) {
    pcb_t *highest_prio = NULL;
    while(prio >= 0) {
        if(ready_list[prio] != NULL) {
            highest_prio = ready_list[prio];
            ready_list[prio] = pcb_get_next(highest_prio);
            return highest_prio;
        }
        prio--;
    }
    return highest_prio;
}
