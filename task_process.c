#include "task_process.h"

uint16_t task_process(fifo_t *adc_buff, uint16_t last_know_index, proc_fifo_t *filt_buff) {
    int16_t new_index = get_last_index(adc_buff);

    if (new_index =! last_know_index) {
        uint16_t last = get_last(adc_buff);
        new_index = get_last_index(adc_buff);
        int index1, index2, index3, index4;
        index1 = new_index - 1;
        if (index1 < 0) {
            index1 = 16+index1;
        }
        index2 = new_index - 2;
        if (index2 < 0) {
            index2 = 16+index2;
        }
        index3 = new_index -3;
        if (index3 < 0) {
            index3 = 16+index3;
        }
        index4 = new_index - 4;
        if (index4 < 0) {
            index4 = 16+index4;
        }
        uint16_t last1 = get_item(adc_buff, index1);
        uint16_t last2 = get_item(adc_buff, index2);
        uint16_t last3 = get_item(adc_buff, index3);
        uint16_t last4 = get_item(adc_buff, index4);

        float processed = (0.2)*last + (0.2)*last1 + (0.2)*last2 + (0.2)*last3 + (0.2)*last4 ;
        proc_add_value(filt_buff, processed);

        
    }
    return new_index;
}