/**
 * @file      task1.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Task1 driver code
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "task1.h"

void init_task1(){

    DDR_LED    |= (1 << LED_RED_PIN); 
    PORT_LED   &= ~(1 << LED_RED_PIN);
}

void led_red_off(){
    PORT_LED &= ~(1 << LED_RED_PIN);    // Make PL0 High
}


void led_red_on(){
    PORT_LED |= (1 << LED_RED_PIN);    // Make PL2 High
}



void task1(void){

  static uint8_t state;

  if(state == 0){
    led_red_on();
    os_delay(250);
  }
  
  else if(state == 1){
    led_red_off();
    os_delay(750);
  }

  state = !state;
  
  return;
}
