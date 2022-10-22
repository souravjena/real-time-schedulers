/**
 * @file      task5.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Task5 function prototypes
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef TASK5_H
#define TASK5_H

#include <avr/io.h>            // Standard AVR IO Library
#include "os.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

/**
 * @brief Initialized the 4-digit 7-segment display for Task-3.
 * 
 */
void init_task5(void);


/**
 * @brief Task-5.
 * 1. Taks-1 runs all the time.
 * 2. Task-2 run 2x times.
 * 3. Task-3 countdown for 3 seconds.
 * 4. Task-2 run 1x time.
 * 5. Dispalys smile for 2 seconds.
 */
void task5(void);

#endif
