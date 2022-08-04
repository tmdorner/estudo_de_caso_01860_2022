#ifndef TASK_PROCESS_H
    #define TASK_PROCESS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdarg.h>
    #include <signal.h>
    #include <errno.h>
    #include <sys/select.h>

    #include "console.h"
    #include "FreeRTOS.h"
    #include "fifo.h"
    #include "fifo_proc.h"

    uint16_t task_process(fifo_t *adc_buff, uint16_t last_know_index, proc_fifo_t *filt_buff);

#endif