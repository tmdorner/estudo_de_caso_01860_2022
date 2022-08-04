#include "adc.h"

uint16_t adc_data[16] = {4859, 6069, 7995, 8575, 10141, 9765, 7100, 7175, 4647, 3394, 2322, 2243, 856, 2325, 1817, 3964};
uint16_t read_number = 0;

uint16_t adc_func(uint16_t *buffer_adc) {
    //printf("adc func");
    uint16_t number = read_adc(buffer_adc);
    //printf("read: %d\n", number);
    return number;

}

uint16_t read_adc(uint16_t *buffer_adc) {
    uint16_t value = adc_data[read_number];
    buffer_adc[read_number] = value;
    read_number = read_number + 1;
    if (read_number == 16) {
        read_number = 0;
    };
    //printf("\n%d \n", value);
    return value;
}