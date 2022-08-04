#include "task_process.h"

uint16_t task_process(fifo_t *adc_buff, uint16_t last_know_index, proc_fifo_t *filt_buff) {
    int16_t new_index = get_last_index(adc_buff);
    printf("index = %d %d\n", new_index, last_know_index);

    if (new_index =! last_know_index) {
        uint16_t last = get_last(adc_buff);
        new_index = get_last_index(adc_buff);
        uint16_t last1 = get_item(adc_buff, new_index-1);
        uint16_t last2 = get_item(adc_buff, new_index-2);
        uint16_t last3 = get_item(adc_buff, new_index-3);
        uint16_t last4 = get_item(adc_buff, new_index-4);

        //printf("data: %d %d %d %d %d \n", last, last1, last2, last3, last4);

        float processed = (0.2)*last + (0.2)*last1 + (0.2)*last2 + (0.2)*last3 + (0.2)*last4 ;
        proc_add_value(filt_buff, processed);

        
    }
    return new_index;
}