#include <stdio.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Local includes. dans posix_gcc */
#include "console.h"

/* Priorities at which the tasks are created. */
#define T1_priority					  ( tskIDLE_PRIORITY + 5 ) 
#define T2_priority					  ( tskIDLE_PRIORITY + 4 )
#define T3_priority					  ( tskIDLE_PRIORITY + 3 )
#define T4_priority					  ( tskIDLE_PRIORITY + 2 )
#define T5_priority					  ( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue.  The times are converted from
 * milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define mainTASK_SEND_FREQUENCY_MS         pdMS_TO_TICKS( 200UL )
#define mainTIMER_SEND_FREQUENCY_MS        pdMS_TO_TICKS( 2000UL )
						
/* The values sent to the queue receive task from the queue send task and the
 * queue send software timer respectively. */
#define mainVALUE_SENT_FROM_TASK           ( 100UL )
#define mainVALUE_SENT_FROM_TIMER          ( 200UL )
/*
 * The tasks as described in the comments at the top of this file.
 */

static void T1(void * pvParameters);
static void T2(void * pvParameters);
static void T3(void * pvParameters);
static void T4(void * pvParameters);
//static void T5(void * pvParameters);

/* A software timer that is started from the tick hook. */
//static TimerHandle_t xTimer = NULL;
void ipsa_sched(void)
{
xTaskCreate( T1, "Rx", configMINIMAL_STACK_SIZE, NULL, T1_priority, NULL );                          
xTaskCreate( T2, "TX", configMINIMAL_STACK_SIZE, NULL, T2_priority, NULL );
xTaskCreate( T3, "FX", configMINIMAL_STACK_SIZE, NULL, T3_priority, NULL );
xTaskCreate( T4, "ZX", configMINIMAL_STACK_SIZE, NULL, T4_priority, NULL );
//xTaskCreate( T5, "GX", configMINIMAL_STACK_SIZE, NULL, T4_priority, NULL );

/* Create the software timer, but don't start it yet. */
//xTimer = xTimerCreate( "Timer",xTimerPeriod,pdTRUE,NULL ); 

/*if( xTimer != NULL )
{
	xTimerStart( xTimer, 0 );
};*/

/* Start the tasks and timer running. */
vTaskStartScheduler();


/* If all is well, the scheduler will now be running, and the following
 * line will never be reached.  If the following line does execute, then
 * there was insufficient FreeRTOS heap memory available for the idle and/or
 * timer tasks	to be created.  See the memory management section on the
 * FreeRTOS web site for more details. */
for( ; ; )
{
}
};



static void T1(void * pvParameters){
	TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTASK_SEND_FREQUENCY_MS;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;
	xNextWakeTime = xTaskGetTickCount();
	for( ; ; )
    {
	console_print("Working \n"); //Print "Working"
	vTaskDelayUntil( &xNextWakeTime, xBlockTime );
	}
};

static void T2(void * pvParameters){
	TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTASK_SEND_FREQUENCY_MS;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;
	xNextWakeTime = xTaskGetTickCount();
	for( ; ; )
    {
	int Fahrenheit=130; //Variable for temperature in fahrenheit, Randomly selected fixed value
	float Celsius; //Variable for temperature in celsius
	Celsius=(Fahrenheit-32)/1.8; //Conversion formula from fahrenheit to celsius temperature
	console_print("%f \n",Celsius); //Print temperature in celsius, we use %f because we display float
	vTaskDelayUntil( &xNextWakeTime, xBlockTime );
	}
	
};

static void T3(void * pvParameters){
	TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTASK_SEND_FREQUENCY_MS;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;
	xNextWakeTime = xTaskGetTickCount();
	for( ; ; )
    {
	long int a=20355432453,b=25432543; //Two long int big numbers chosen randomly
	long int r; //Variable for the result
	r=a*b; //Multiply the two numbers
	console_print("%ld \n",r); //Print the result, we use %ld because we display long integers
	vTaskDelayUntil( &xNextWakeTime, xBlockTime );
	}
};



static void T4(void * pvParameters){
	TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTASK_SEND_FREQUENCY_MS;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;
	xNextWakeTime = xTaskGetTickCount();
	//( void ) pvParameters;
	for( ; ; )
    {
	int array[50]; //Create an empty array of size 50
    
    //Fill in the table with numbers from 1 to 50
    for (int i=0; i<50; i++){
        array[i]=i+1;
    }

	int lowest = 1; //Lowest value in the list
	int highest = 50; //Highest value in the list
	int nb = 6; //Number to find chosen randomly
	int middle = (lowest+highest)/2; //If the result is a float, it will be rounded down. Here, if M=51/2=25.5 then M=25
	
	while(array[middle]!=nb){ //As long as the number searched for is not equal to the middle number of the list
		if(array[middle]>nb){ //If the middle number is bigger than the searched number
			highest = middle; //Then the middle number becomes the highest in the list
			middle = (lowest+highest)/2; //And we recalculate the middle. If the result is a float, it will be rounded down.
		}
		else if(array[middle]<nb){ //If the middle number is smaller than the searched number
			lowest = middle; //Then the middle number becomes the lowest in the list
			middle = (lowest+highest)/2; //And we recalculate the middle. If the result is a float, it will be rounded down.
		}
		else{
			console_print("%d is not in the list \n",nb); //Otherwise, the number you are looking for is not in the list. We use %d because we display integers
		}
	}
	console_print("%d is in the list, in position %d \n",nb , middle); //Print the searched number and its position. We use %d because we display integers
	vTaskDelayUntil( &xNextWakeTime, xBlockTime );
	}
};


/* 
static void T5(void * pvParameters) {
    TickType_t nextWakeTime;
    int reset = 0; //Reset variable set to zero
    
    while (1) {
        printf("%d\n", reset); //Print reset

        if (kbhit()) { //If a key is pressed
            char c = getch(); //Read the key pressed

            if (c == '1' || c == '&') { //If a key is 1 or & (same key)
                reset = 1;
                printf("%d\n", reset);
            }
        }

        reset = 0; //Reset the reset rariable
        sleep(200); //Wait 200 ms
    }
}
*/
