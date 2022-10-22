/**
 * @file      task4.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Task-4 function prototypes
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef TASK1_H
#define TASK1_H

#include <avr/io.h>            // Standard AVR IO Library
#include "os.h"
#include "task2.h"
#include "task3.h"

/**
 * @brief Task-4.
 * Task 4 is a new task that combines and modifies tasks 2 and 3 as follows.   
 * While no music is being output, make it so the 7-segment display indicates a countdown 
 * in 10ths of a second until the next time the theme is played.  
 * During the music, display the frequency (in decimal Hz.) of the current tone on the 7-Segment display. 
 * 
 */
void task4(void);

#endif
