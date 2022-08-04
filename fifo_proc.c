#include "fifo_proc.h"

float proc_data[64] = {0};

proc_fifo_t proc_create_fifo(uint16_t size) {
    proc_fifo_t buffer;
    buffer.size = size;
    buffer.last_index = 15;

    return buffer;
}

void proc_add_value(proc_fifo_t *buff, uint16_t value) {
    int index;

    if (buff->last_index == 15) {
        index = 0;
    }
    else {
        index = (buff->last_index)+1;
    }
    buff->last_index = index;

    proc_data[index] = value;
}

uint16_t proc_get_last(proc_fifo_t *buff) {
    return proc_data[buff->last_index];
}

uint16_t proc_get_last_index(proc_fifo_t *buff) {
    return buff->last_index;
}

uint16_t proc_get_item(proc_fifo_t *buff, int16_t index) {
    if (index < 0) {
        index = buff->size - index;
    }
    
    if (index <= buff->size) {
        return proc_data[index];
    }
}