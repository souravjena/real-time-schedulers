/**
 * @file      task2.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Function prototypes, global variable and macros for Task2
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef TASK2_H
#define TASK2_H

#include <avr/io.h>            // Standard AVR IO Library
#include <stdint.h>
#include "os.h"


#define DDR_SPEAKER                 DDRH       // DDR of PORTL
#define PORT_SPEAKER                PORTH      // PORTL Register
#define PIN_SPEAKER                 PH3        // Speaker Pin (OC4A -> PH3 -> Arduino Pin 6)

#define TIMER4_POWER_REG            PRR1
#define TIMER4_CONTROL_REG_A        TCCR4A
#define TIMER4_CONTROL_REG_B        TCCR4B
#define TIMER4_COUNT_REG            TCNT4
#define TIMER4_OUTPUT_COMPARE_REG   OCR4A

#define BIT_SET(PORT, BIT)          (PORT |= (1 << BIT))      // Macro function for setting one bit
#define BIT_CLR(PORT, BIT)          (PORT &= ~(1 << BIT))     // Macro function for clearing one bit

// 293hz 329hz 261hz 130hz 196hz
#define HZ_293      107
#define HZ_329      95
#define HZ_261      119
#define HZ_130      481
#define HZ_196      319

#define HZ_400      78
#define HZ_250      125
#define HZ_800      39
#define SILENCE_1S  62500

extern uint32_t arr_notes[];       // Array to hold notes of the tune to be played.

extern uint32_t notes_ticks;       // Holds index of current node which is being played.

/**
 * @brief Initializes Timer-4 to toggle the speaker pin when the timer overflows.
 * 
 */
void init_task2(void);


/**
 * @brief Play the "Close Encounter" tune then pause for 4 seconds.
 * 
 */
void task2(void);

#endif
