/*
 * Name:
 *     Two threads depending on each other
 *
 * Description:
 *     - A FreeRTOS example application for the Silicon Labs
 *       EFM32 Giant Gecko Starter Kit (STK3700A).
 *     - There are two tasks:
 *       - The HIGH priority task suspends itself.
 *       - While the LOW priority task resumes the HIGH priority task.
 *     - The aim is to test if FreeRTOS is able to switch context between two
 *       cooperating tasks.
 *
 * Variant:
 *     - Try out this exercise also with preemption disabled!
 *
 * Created by:
 *     NASZALY Gabor <naszaly@mit.bme.hu>
 *
 * Last modified on:
 *     2017-04-06
*/

/* --------------------------------------------------------------------------
   INCLUDES
-------------------------------------------------------------------------- */

// Application specific includes
#include <stdio.h>
#include <retargetserial.h>

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"

/* --------------------------------------------------------------------------
   DEFINES
-------------------------------------------------------------------------- */

#define  mainTASK_HI_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define  mainTASK_HI_STACK_SIZE  configMINIMAL_STACK_SIZE

#define  mainTASK_LO_PRIORITY    ( tskIDLE_PRIORITY + 1 )
#define  mainTASK_LO_STACK_SIZE  configMINIMAL_STACK_SIZE

/* --------------------------------------------------------------------------
   VARIABLES
-------------------------------------------------------------------------- */

// TODO: define a variable for the handle of the HIGH priority task
// (Type to use: TaskHandle_t.)
TaskHandle_t handlerHi;


/* --------------------------------------------------------------------------
   FUNCTION DECLARATIONS
-------------------------------------------------------------------------- */

static void prvTaskHi(void *pvParam);
static void prvTaskLo(void *pvParam);

/* --------------------------------------------------------------------------
   MAIN
-------------------------------------------------------------------------- */

int main(void) {

    // Initialize starter kit
    RETARGET_SerialInit();
    RETARGET_SerialCrLf(1);

    // Initialize FreeRTOS

        // TODO: create the high priority task --> xTaskCreate()
    	xTaskCreate(prvTaskHi, "", mainTASK_HI_STACK_SIZE, NULL, mainTASK_HI_PRIORITY, &handlerHi);

        // TODO: create the low priority task --> xTaskCreate()
    	xTaskCreate(prvTaskLo, "", mainTASK_LO_STACK_SIZE, NULL, mainTASK_LO_PRIORITY, NULL);

        vTaskStartScheduler();

    // Prevent compiler warning
    return 0;
}

/* --------------------------------------------------------------------------
   FUNCTION DEFINITIONS
-------------------------------------------------------------------------- */

/*
 * TODO: implement the high priority task as an endless loop
 *     - Print out some message which says that it belongs to the high priority
 *       task
 *     - Suspend execution (use vTaskSuspend())
*/
static void prvTaskHi(void *pvParam) {
	while(1)
	{
		printf("HI\n");
		vTaskSuspend(NULL);
	}
}

/*
 * TODO: implement the low priority task as an endless loop
 *     - Print out some message which says that it belongs to the high priority
 *       task
 *     - Resume the execution of the HIGH priroity task (use vTaskResume())
*/
static void prvTaskLo(void *pvParam) {
	while(1)
	{
		printf("LO\n");
		vTaskResume(handlerHi);
	}
}
