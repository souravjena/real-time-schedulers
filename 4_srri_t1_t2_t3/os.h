/**
 * @file      os.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Function prototypes, global variables and macros for SSRI Scheduler
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef OS_H
#define OS_H

#include <stdio.h>            // For NULL
#include <avr/io.h>           // Standard AVR IO Library
#include <util/delay.h>       // Standard AVR Delay Library
#include <stdint.h>           // For standard data types
#include <avr/interrupt.h>    // Standard AVR Interrupt Library

#define NUMBER_OF_TASKS     10

#define READY     0
#define RUNNING   1
#define SLEEPING  2

#define PENDING   0
#define DONE      1

extern volatile uint8_t  os_sFlag;      ///< Stores scheduler's Flag (DONE, PENDING)
extern volatile uint32_t  os_ticks;     ///< Holds number of ms elasped since the start of Timer-2

extern void (*arr_ready_tasks[NUMBER_OF_TASKS])(void *p);   ///< Array to hold function pointer of the tasks
extern uint8_t arr_task_state[NUMBER_OF_TASKS];             ///< Array to hold state of the tasks

extern uint8_t arr_task_sleep_start_flag[NUMBER_OF_TASKS];  ///< Array to hold sleep start flag of the tasks
extern int32_t arr_task_sleep_remaining[NUMBER_OF_TASKS];   ///< Array to hold sleep time remaining for the tasks


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
