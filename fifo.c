#include "fifo.h"

uint16_t adc_data_2[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

fifo_t create_fifo(uint16_t size) {
    fifo_t buffer;
    buffer.size = size;
    buffer.last_index = 15;

    return buffer;
}

void add_value(fifo_t *buff, uint16_t value) {
    int index;

    if (buff->last_index == 15) {
        index = 0;
    }
    else {
        index = (buff->last_index)+1;
    }
    buff->last_index = index;

    adc_data_2[index] = value;
}

uint16_t get_last(fifo_t *buff) {
    return adc_data_2[buff->last_index];
}

uint16_t get_last_index(fifo_t *buff) {
    return buff->last_index;
}

uint16_t get_item(fifo_t *buff, int16_t index) {
    if (index < 0) {
        index = buff->size - index;
    }
    
    if (index <= buff->size) {
        return adc_data_2[index];
    }
}