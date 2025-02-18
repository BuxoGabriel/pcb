#include <stdlib.h>

typedef struct cpu {
    int stack_pointer;
    int reg1;
    int reg2;
    int reg3;
} cpu_t;

cpu_t *cpu_create() {
    cpu_t *cpu = malloc(sizeof(cpu_t));
    cpu->stack_pointer = 0;
    cpu->reg1 = 0;
    cpu->reg2 = 0;
    cpu->reg3 = 0;
    return cpu;
}
