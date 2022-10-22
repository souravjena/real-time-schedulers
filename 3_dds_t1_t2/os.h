/**
 * @file      os.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Function prototypes, global variables and macros for DDS Scheduler
 * @version   1.0
 * @date      2022-05-28
 * 
 */


#ifndef OS_H
#define OS_H

#define F_CPU 16000000UL      // Define Crystal Frequency of eYFi-Mega Board
#include "Arduino.h"
#include <stdio.h>            // For NULL
#include <avr/io.h>           // Standard AVR IO Library
#include <util/delay.h>       // Standard AVR Delay Library
#include <stdint.h>
#include <avr/interrupt.h>    // Standard AVR Interrupt Library

#define NUMBER_OF_TASKS     10

#define READY     0
#define RUNNING   1
#define SLEEPING  2

#define PENDING   0
#define DONE      1

/**
 * @brief Task Control Block structure to store a Task's
 * information relevant to the scheduler.
 * 
 */
typedef struct TCBstruct {
    void (*ptr_func)(void *p);    // the function pointer
    uint8_t state;                // stores the state of the task
    int32_t sleep_remaining;      // stores sleep time remaining
    uint8_t flag_start_sleep;     // stores if the task has started its sleep
    
    uint8_t unique_id;            // stores unique id of the task
    String  str_name;             // stores name given to the task
    uint32_t count_restart;       // stores number of times the task has been restarted by the scheduler
    
};

extern TCBstruct os_task[10];           // TCBstruct array to hold information about max 10 ALIVE tasks.
extern TCBstruct os_dead_task[10];      // TCBstruct array to hold information about max 10 DEAD tasks.

extern volatile uint8_t  os_sFlag;      // Stores scheduler's Flag (DONE, PENDING)
extern volatile uint32_t os_ticks;      // Holds number of ms elasped since the start of Timer-2
extern volatile uint8_t  os_task_index; // Holds the index of current task running by the scheduler


/**
 * @brief Interrupt Service Routine for Timer-2.
 * 1. Fires every 2 ms.
 * 2. Changes os_sFlag from PENDING to DONE.
 * 3. Increments os_ticks. 
 * 
 */
ISR(TIMER2_OVF_vect);


/**
 * @brief Configure Timer-2 to fire ISR every 2 ms.
 * 
 */
void init_timer2(void);


/**
 * @brief Initializes Timer-2 and add Tasks for the scheduler to manage.
 * 
 */
void os_init(void);


/**
 * @brief Starts a task. Runs the task on the scheduler.
 * 
 * @param ptr_fn Function pointer pointing to the Task.
 */
void os_start_task(void (*ptr_fn)());


/**
 * @brief Non-blocking delay. Changes the state of a running task to sleeping.
 * Allows the scheduler to run other tasks when the current task is sleeping. 
 * 
 * @param delay_ms Time in ms the task needs to sleep
 */
void os_delay(int32_t delay_ms);


/**
 * @brief Puts the scheduler in the IDLE state, till 2 ms has not elasped 
 * so that tasks and synced and runs periodically. 
 * Decrements sleep time remaining for each task by 2 ms.
 * Changes the state of a SLEEPING task to READY when it sleep time remaining
 * for that task reaches 0.
 * 
 */
void os_scheduler_sync(void);


/**
 * @brief Scheduler code.
 * Iterates over all the tasks in os_task array and runs the tasks that
 * have RUNNING as their state.
 * Changes state of a READY task to RUNNING.
 */
void os_scheduler(void);

#endif
