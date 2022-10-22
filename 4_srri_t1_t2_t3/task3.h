/**
 * @file      task3.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Function prototypes, macros and global variables for Task3
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef TASK3_H
#define TASK3_H

#include <avr/io.h>            // Standard AVR IO Library
#include "os.h"
#include "Arduino.h"

#define OUTPUT 1
#define INPUT  0

#define HIGH   1
#define LOW    0

#define BIT_SET(PORT, BIT)          (PORT |= (1 << BIT))      // Macro function for setting one bit
#define BIT_CLR(PORT, BIT)          (PORT &= ~(1 << BIT))     // Macro function for clearing one bit

/**
 * @brief Make the given GPIO pin LOW
 * 
 * @param pin_num Pin number as on Arduino Board
 */
void pin_write_0(int pin_num);


/**
 * @brief Make the given GPIO pin HIGH
 * 
 * @param pin_num Pin number as on Arduino Board
 */
void pin_write_1(int pin_num);


/**
 * @brief Make the given GPIO pin OUTPUT
 * 
 * @param pin_num Pin number as on Arduino Board
 */
void pin_write_mode_0(int pin_num);


/**
 * @brief Make the given GPIO pin INPUT
 * 
 * @param pin_num Pin number as on Arduino Board
 */
void pin_write_mode_1(int pin_num);


/**
 * @brief Make the given GPIO pin either HIGH or LOW
 * 
 * @param pin_num Pin number as on Arduino Board
 * @param data HIGH or LOW
 */
void pin_write(int pin_num, int data);


/**
 * @brief Make the given GPIO pin either OUTPUT or INPUT
 * 
 * @param pin_num Pin number as on Arduino Board
 * @param data OUTPUT or INPUT
 */
void pin_mode(int pin_num, int data);


/**
 * @brief Increments the global variable counter value by 1.
 * 
 */
void seven_seg_counter_increment();


/**
 * @brief Counts number of digits in the global variable counter.
 * 
 * @return int Number of digits in the value.
 */
int seven_seg_num_digits();


/**
 * @brief Splits the counter value into individual digits and stores in the global array.
 * 
 */
void seven_seg_update_digits_arr();


/**
 * @brief Turn offs the LEDs of the selected 7-segment display.
 * 
 */
void seven_seg_clear_leds();


/**
 * @brief Displays the number passed to the function on the selected
 * 7-segment display.
 * 
 * @param curr_digit Number to be displayed on the 7-segment.
 */
void seven_seg_display_num(int curr_digit);


/**
 * @brief Selects one of the 7-segment on a 4-digit 7-segment display.
 * 
 * @param x The place of the 7-segment to be selected.
 */
void seven_seg_pick_digit(int x);


/**
 * @brief Unselects one of the 7-segment on a 4-digit 7-segment display.
 * 
 * @param x The place of the 7-segment to be un-selected.
 */
void seven_seg_unpick_digit(int x);


/**
 * @brief Displays a given digit at a given place on a 4-digit 7-segment display.
 * 
 * @param place The place at which we want the digit to be displayed.
 * @param curr_digit The digit to be displayed at the given place.
 */
void seven_seg_display(int place, int curr_digit);


/**
 * @brief Initialized the 4-digit 7-segment display for Task-3.
 * 
 */
void init_task3();


/**
 * @brief Task-3. Makes the 4-digit 7-segment display count up by 1 unit every 100 ms. 
 * 
 */
void task3(void);

#endif
