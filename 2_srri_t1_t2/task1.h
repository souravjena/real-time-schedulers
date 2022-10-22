/**
 * @file      task1.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Function prototypes and macros for Task1
 * @version   1.0
 * @date      2022-05-28
 * 
 */


#ifndef TASK1_H
#define TASK1_H

#include <avr/io.h>            // Standard AVR IO Library
#include "os.h"

#define DDR_LED               DDRL       // DDR of PORTL
#define PORT_LED              PORTL      // PORTL Register

#define LED_RED_PIN           PL0        // Offboard LED R Pin number  PL0


/**
 * @brief Initializes LED GPIO Pin
 * 
 */
void init_task1();


/**
 * @brief Turns ON the LED.
 * 
 */
void led_red_on();


/**
 * @brief Turn OFF the LED.
 * 
 */
void led_red_off();


/**
 * @brief Task to turn on the LED for 250 ms and off for 750 ms.
 * 
 */
void task1(void);

#endif
