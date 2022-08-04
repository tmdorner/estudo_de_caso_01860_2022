#ifndef FIFO_H
    #define FIFO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>

#include "FreeRTOS.h"

struct fifo {
    uint16_t size;
    uint16_t last_index;
};

typedef struct fifo fifo_t;

fifo_t create_fifo(uint16_t size);
void add_value(fifo_t *buff, uint16_t value);
uint16_t get_last(fifo_t *buff);
uint16_t get_last_index(fifo_t *buff);
uint16_t get_item(fifo_t *buff, int16_t index);

#endif