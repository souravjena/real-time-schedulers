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

#include "Arduino.h"          // To use Arduino macros and functions
#include <stdio.h>            // For NULL
#include <avr/io.h>           // Standard AVR IO Library
#include <util/delay.h>       // Standard AVR Delay Library
#include <stdint.h>           // For standard data types
#include <avr/interrupt.h>    // Standard AVR Interrupt Library

#define NUMBER_OF_TASKS     10

#define READY     0
#define RUNNING   1
#define SLEEPING  2
#define DEAD      3

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
 * @brief Add a task to os_task array
 * 
 * @param ptr_fn    Pointer to the function of the task
 * @param unique_id Unique id that is assigned to the task
 * @param str_name  Unique name that is assigned to the task
 */
void os_add_task(void (*ptr_fn)(), uint8_t unique_id, String  str_name);


/**
 * @brief Removes task to os_task array
 * 
 * @param target_id Unique id of the task that needs to be removed
 */
void os_remove_task(uint8_t target_id);


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
 * @brief Changes the state of the calling task to DEAD
 * 
 */
void os_task_self_quit(void);


/**
 * @brief Changes the state of a given task to READY.
 * 
 * @param ptr_tcb TCB of the task whose state we want to change.
 */
void os_from_task_start(TCBstruct* ptr_tcb);


/**
 * @brief Changes the state of a given task to DEAD.
 * 
 * @param ptr_dead_tcb TCB of the task whose state we want to change.
 */
void os_from_task_stop(TCBstruct* ptr_dead_tcb);


/**
 * @brief Scheduler code.
 * Iterates over all the tasks in os_task array and runs the tasks that
 * have RUNNING as their state.
 * Changes state of a READY task to RUNNING.
 */
void os_scheduler(void);



#endif
