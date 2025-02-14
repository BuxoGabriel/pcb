#pragma once

#include "pcb.h"

pcb_t* scheduler_run(pcb_t** ready_list, int prio);
