#ifndef FIFO_PROC_H
    #define FIFO_PROC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>

#include "FreeRTOS.h"

struct proc_fifo {
    uint16_t size;
    uint16_t last_index;
};

typedef struct proc_fifo proc_fifo_t;

proc_fifo_t proc_create_fifo(uint16_t size);
void proc_add_value(proc_fifo_t *buff, uint16_t value);
float proc_get_last(proc_fifo_t *buff);
uint16_t proc_get_last_index(proc_fifo_t *buff);
float proc_get_item(proc_fifo_t *buff, int16_t index);

#endif