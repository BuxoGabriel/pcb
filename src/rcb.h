#pragma once

#include "types.h"

enum RCB_STATES {
    RCB_FREE,
    RCB_ALLOCATED
};

rcb_t* rcb_create();
rcb_t* rcb_get_next(rcb_t *rcb);
void rcb_set_next(rcb_t *rcb, rcb_t *next);
void rcb_request(rcb_t *rcb, pcb_t *pcb, scheduler_t *scheduler);
void rcb_release(rcb_t *rcb, scheduler_t *scheduler);
