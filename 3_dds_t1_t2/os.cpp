/**
 * @file      os.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     DDS Scheduler driver code
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "Arduino.h"
#include "os.h"
#include "task1.h"
#include "task2.h"

TCBstruct os_task[10];

volatile uint8_t  os_sFlag = PENDING;
uint8_t  os_current_task_index = 0;


void init_timer2(){

   cli();  // Turn off global interrupts

  // Setup Timer2 to fire ISR every 2ms
  TCCR2B = 0x00;                        // Cut off Clock Source to disbale Timer2 while we set it up
  TCNT2  = 5;                           // Reset Timer os_ticks to 0 out of 255
  TIFR2  &= ~(1 << TOV2);               // Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 |= (1 << TOIE2);               // Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;                        // Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B |= (1 << CS22) | (1 << CS20);  // Timer2 Control Reg B: Timer Prescaler set to 128 and Start Timer2

  sei();  // Turn on global interrupts

}

void os_init(void){
  init_timer2();

  os_task[0].ptr_func = task1;
  os_task[0].str_name = "task1";
  os_task[0].unique_id = 0;
  os_task[0].state = READY;
  os_task[0].count_restart = 0;
  os_task[0].sleep_remaining = 0;
  os_task[0].flag_start_sleep = 0;


  os_task[1].ptr_func = task2;
  os_task[1].str_name = "task2";
  os_task[1].unique_id = 0;
  os_task[1].state = READY;
  os_task[1].count_restart = 0;
  os_task[1].sleep_remaining = 0;
  os_task[1].flag_start_sleep = 0;


  os_task[2].ptr_func = os_scheduler_sync;
  os_task[2].str_name = "syncer";
  os_task[2].unique_id = 0;
  os_task[2].state = READY;
  os_task[2].count_restart = 0;
  os_task[2].sleep_remaining = 0;
  os_task[2].flag_start_sleep = 0;


  os_task[3].ptr_func = NULL;

  
}


void os_start_task(void (*ptr_fn)()){
    ptr_fn();
}


void os_delay(int32_t t_sleep){

  if(os_task[os_current_task_index].flag_start_sleep == 0){

      os_task[os_current_task_index].flag_start_sleep = 1;

      os_task[os_current_task_index].state = SLEEPING;

      os_task[os_current_task_index].sleep_remaining = t_sleep;
  } 
  
  return;
}


void os_scheduler_sync(void){

  if(os_sFlag == PENDING){
    while(os_sFlag == PENDING){}
    
  } else {
    for(int i = 0; i < NUMBER_OF_TASKS; i++){

      if(os_task[i].ptr_func == NULL){
        break;
      }

      int32_t t_remaining = os_task[i].sleep_remaining;
  
      if(t_remaining <= 0){
         os_task[i].state = READY; 

         os_task[i].sleep_remaining = 0;
         os_task[i].flag_start_sleep = 0;
      
      } else {
         os_task[i].sleep_remaining = t_remaining - 2;
      }
    
    }
    
    os_sFlag = PENDING; 
  }
  
  
}


void os_scheduler(void){

  int i = os_current_task_index;
  
  if(os_task[i].ptr_func == NULL){
    os_current_task_index = 0;
    i = 0;
  }

  if(os_task[i].state == READY){
    os_task[i].state = RUNNING;
  }

  if(os_task[i].state == RUNNING){
    os_task[i].state = RUNNING;
    os_start_task(os_task[i].ptr_func);
  }

  if(os_task[i].state == SLEEPING){
    // Do Nothing
    // Serial.println(">> SLEEPING");
  }

  os_current_task_index++;

  return;
}



//Timer2 Overflow Interrupt Vector
ISR(TIMER2_OVF_vect) {

  os_sFlag = DONE;

  TCNT2 = 5;                // Reset Timer to 5 out of 255
  TIFR2  &= ~(1 << TOV2);   // Timer2 INT Flag Reg: Clear Timer Overflow Flag
};
