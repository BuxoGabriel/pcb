#pragma once

#include "types.h"

scheduler_t* scheduler_create(int max_prio);
int scheduler_schedule(scheduler_t *scheduler, pcb_t *pcb, int prio);
int scheduler_run(scheduler_t *scheduler);
