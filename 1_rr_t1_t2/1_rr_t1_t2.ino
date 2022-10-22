/**
 * @file      1_rr_t1_t2.ino
 * @author    Sourav Jena, Yi Chen
 * @brief     main file for the RR Scheduler running Task-1 and Task-2 of Lab-3
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include <avr/io.h>       // Standard AVR IO Library
#include <stdint.h>

#define DDR_LED               DDRL       // DDR of PORTL
#define PORT_LED              PORTL      // PORTL Register

#define LED_RED_PIN           PL0        // Offboard LED R Pin number  PL0

#define DELAY_MS_ON           250        // 250 ms delay
#define DELAY_MS_OFF          750        // 750 ms delay

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

uint32_t time_curr = 0;           ///< Holds current time.

uint32_t led_time_old = 0;        ///< Holds old time for the LED task.
uint32_t speaker_time_old = 0;    ///< Holds old time for the Speaker task.

uint32_t global_ticks = 0;        ///< Holds index of the current note being played.

uint32_t arr_notes[] = {HZ_293, HZ_329, HZ_261, HZ_130, HZ_196, SILENCE_1S, SILENCE_1S, SILENCE_1S, SILENCE_1S};    ///< Holds notes to be played.


/**
 * @brief Initializes LED GPIO Pin
 * 
 */
void led_init(){

  DDRL    |= (1 << LED_RED_PIN);       // Initialize the pins PIN_LED_RED of port H as output pins.
  PORTL   &= ~(1 << LED_RED_PIN);      // Keep the LED off initially
  
}


/**
 * @brief Turn OFF the LED.
 * 
 */
void led_red_off(){
    PORT_LED &= ~(1 << LED_RED_PIN);    // Make PL0 High
}


/**
 * @brief Turns ON the LED.
 * 
 */
void led_red_on(){
    PORT_LED |= (1 << LED_RED_PIN);    // Make PL2 High
}


/**
 * @brief Initializes Timer-4 to toggle the speaker pin when the timer overflows.
 * 
 */
void timer4_init(){
  
  // 1. PRTIM4 Bit = 0, To turn-on Timer-4 (not required, already done internally by Arduino)
  BIT_CLR(TIMER4_POWER_REG, PRTIM4);    

  // 2. Clock Select Bits -> CS42, CS41, CS40 -> 001 -> For 1/256 as pre-scalar
  BIT_SET(TIMER4_CONTROL_REG_B, CS42);    
  BIT_CLR(TIMER4_CONTROL_REG_B, CS41);
  BIT_CLR(TIMER4_CONTROL_REG_B, CS40);

  // 3. Waveform Generation Bits -> WGM43, WGM42, WGM41, WGM40 -> 0100 -> For CTC Mode
  BIT_CLR(TIMER4_CONTROL_REG_B, WGM43); 
  BIT_SET(TIMER4_CONTROL_REG_B, WGM42);   
  BIT_CLR(TIMER4_CONTROL_REG_A, WGM41);
  BIT_CLR(TIMER4_CONTROL_REG_A, WGM40);

  // 4. Compare Output Bits -> COM4A1, COM4A0 -> 01 -> To toggle OC4A pin on compare match
  BIT_CLR(TIMER4_CONTROL_REG_A, COM4A1);
  BIT_SET(TIMER4_CONTROL_REG_A, COM4A0);  

  // 5. TCNT4 Register = 0 -> To start the count from 0
  TIMER4_COUNT_REG = 0;                   
  
  // 6. OCR4A Register = 78 -> To overflow Timer-4 after 78 ticks. (16MHz, 1/256 prescalar, 78 ticks -> 0.00125 seconds per overflow)
  TIMER4_OUTPUT_COMPARE_REG = SILENCE_1S;

  // 7. PH3 Bit in DDRH = 1 -> To make OC4A a output pin
  BIT_SET(DDR_SPEAKER, PIN_SPEAKER);

}




/**
 * @brief Task to turn on the LED for 250 ms and off for 750 ms.
 * 
 */
void task1(){

  uint32_t curr_millis = millis();
  uint32_t t_delta = (curr_millis - led_time_old);
  
  if( t_delta < DELAY_MS_ON){
    Serial.println("ON");
    led_red_on();                // Make the offboard R LED pin High
     
  } else if ( (t_delta > DELAY_MS_ON) && (t_delta < 1000) ){
    Serial.println("OFF");
    led_red_off();                // Make the offboard R LED pin High
  
  } else {
    led_time_old = curr_millis;
    
  }

}


/**
 * @brief Play the "Close Encounter" tune then pause for 4 seconds.
 * 
 */
int task2(){

  static int count_times = 0;


  if((millis() - speaker_time_old) >= 1000){

     TIMER4_COUNT_REG = 0; 
     TIMER4_OUTPUT_COMPARE_REG = arr_notes[global_ticks];

     global_ticks++; 

     speaker_time_old = millis();

     if (global_ticks == 9){
        global_ticks = 0;
        count_times++; 
     }
  }

  return 0;
  
}





void setup() {
                  
  led_init();
  timer4_init();
  
  Serial.begin(9600);
}


void loop() {

  while(1){
    task2();
    task1();
  }
  
}
