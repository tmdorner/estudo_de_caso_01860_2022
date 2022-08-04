#include <stdio.h>
#include <pthread.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Local includes. */
#include "console.h"
#include "adc.h"
#include "task_process.h"
#include "fifo.h"
#include "fifo_proc.h"

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_SEND_TASK_PRIORITY       ( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue.  The times are converted from
 * milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define mainTASK_SEND_FREQUENCY_MS         pdMS_TO_TICKS( 200UL )
#define mainTIMER_SEND_FREQUENCY_MS        pdMS_TO_TICKS( 2000UL )

/* The number of items the queue can hold at once. */
#define mainQUEUE_LENGTH                   ( 2 )

/* The values sent to the queue receive task from the queue send task and the
 * queue send software timer respectively. */
#define mainVALUE_SENT_FROM_TASK           ( 100UL )
#define mainVALUE_SENT_FROM_TIMER          ( 200UL )

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueReceiveTask( void * pvParameters );
//static void prvQueueSendTask( void * pvParameters );

static void tarefa1 (void * pvParameters);
static void tarefa2 (void * pvParameters);
static void tarefa3 (void * pvParameters);
static void tarefa4 (void * pvParameters);

/*
 * The callback function executed when the software timer expires.
 */
static void prvQueueSendTimerCallback( TimerHandle_t xTimerHandle );

/*-----------------------------------------------------------*/

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

/* A software timer that is started from the tick hook. */
static TimerHandle_t xTimer = NULL;

/*-----------------------------------------------------------*/

// Buffer do ADC
uint16_t buffer_adc[16];
fifo_t adc_buffer_fifo;
proc_fifo_t buffer_filt;



void main_test( void )
{
        /* Start the two tasks as described in the comments at the top of this
         * file. */

    //adc_buffer_fifo.size = 16;
    //adc_buffer_fifo.last_index = 15;
    
    adc_buffer_fifo = create_fifo(16);
    buffer_filt = proc_create_fifo(64);

    xTaskCreate ( tarefa1, "ADC Read", configMINIMAL_STACK_SIZE, &adc_buffer_fifo, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL);
    xTaskCreate ( tarefa2, "Filtragram", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL);
    xTaskCreate ( tarefa3, "Exibir", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL);
    xTaskCreate ( tarefa4, "ConsumoProcessos", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL);


        // xTaskCreate( prvQueueReceiveTask,             /* The function that implements the task. */
        //              "Rx",                            /* The text name assigned to the task - for debug only as it is not used by the kernel. */
        //              configMINIMAL_STACK_SIZE,        /* The size of the stack to allocate to the task. */
        //              NULL,                            /* The parameter passed to the task - not used in this simple case. */
        //              mainQUEUE_RECEIVE_TASK_PRIORITY, /* The priority assigned to the task. */
        //              NULL );                          /* The task handle is not required, so NULL is passed. */

        //xTaskCreate( prvQueueSendTask, "TX", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_SEND_TASK_PRIORITY, NULL );

        /* Create the software timer, but don't start it yet. */
        // xTimer = xTimerCreate( "Timer",                     /* The text name assigned to the software timer - for debug only as it is not used by the kernel. */
        //                        xTimerPeriod,                /* The period of the software timer in ticks. */
        //                        pdTRUE,                      /* xAutoReload is set to pdTRUE. */
        //                        NULL,                        /* The timer's ID is not used. */
        //                        prvQueueSendTimerCallback ); /* The function executed when the timer expires. */


    vTaskStartScheduler();
    

    /* If all is well, the scheduler will now be running, and the following
     * line will never be reached.  If the following line does execute, then
     * there was insufficient FreeRTOS heap memory available for the idle and/or
     * timer tasks	to be created.  See the memory management section on the
     * FreeRTOS web site for more details. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

void tarefa1 (void * pvParameters) {
    printf("ola %d\n", pvParameters);
    const TickType_t delay = 1000/portTICK_PERIOD_MS;
    while (1)
    {
        int value = adc_func(buffer_adc);
        //printf("\nvalue %d \n", value);
        add_value(&adc_buffer_fifo, value);
        //printf("buff last index %d \n", get_last(pvParameters));
        /*for (int i = 0; i < 16; i++) {
            printf("%d ", buffer_adc[i]);
        }*/

        vTaskDelay(delay);
    }
}

void tarefa2 (void * pvParameters) {
    const TickType_t delay = 500/portTICK_PERIOD_MS;
    uint16_t last_known = 15;
    while (1)
    {
        //printf("tarefa 2");
        last_known = task_process(&adc_buffer_fifo, last_known, &buffer_filt);
        vTaskDelay(delay);
    }
}

void tarefa3 (void * pvParameters) {
    const TickType_t delay = 1000/portTICK_PERIOD_MS;
    char read_data[10];
    //int compare;
    //gets(read_data);
    //compare = strcmp(read_data, "obter");
    //printf("compare %d\n", compare);
    while (1)
    {
        for (int i = 0; i < 64; i++) {
            printf ("%f ", proc_get_item(&buffer_filt, i));
        }
        printf("\n%d\n\n", proc_get_last_index(&buffer_filt));
        vTaskDelay(delay);
    }
}

void tarefa4 (void * pvParameters) {
    const TickType_t delay = 3000/portTICK_PERIOD_MS;
    const char stat_buff[1024] = {'\0'};
    while (1)
    {
        //printf("hey\n");
        vTaskGetRunTimeStats(&stat_buff);
        printf("%s\n", stat_buff);
        vTaskDelay(delay);
    }
}