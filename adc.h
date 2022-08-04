#ifndef ADC_H
    #define ADC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>

#include "FreeRTOS.h"

uint16_t adc_func(uint16_t *buffer_adc);

uint16_t read_adc(uint16_t *buffer_adc);

#endif