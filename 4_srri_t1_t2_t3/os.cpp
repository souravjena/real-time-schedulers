/**
 * @file      os.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     SRRI Scheduler driver code
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "Arduino.h"
#include "os.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"


volatile uint8_t  os_sFlag = PENDING;
volatile uint32_t  os_ticks = 0;

uint8_t  os_current_task_index = 0;
void (*arr_available_tasks[NUMBER_OF_TASKS])(void *p);
uint8_t arr_task_state[NUMBER_OF_TASKS]= {READY, READY, READY, READY, NULL};

uint8_t arr_task_sleep_start_flag[NUMBER_OF_TASKS] = {0, 0, 0,  0, 0, 0,  0, 0, 0,  0};
int32_t arr_task_sleep_remaining[NUMBER_OF_TASKS] = {0, 0, 0,  0, 0, 0,  0, 0, 0,  0};


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

  arr_available_tasks[0] = task1;
  
  arr_available_tasks[1] = task2;

  arr_available_tasks[2] = task3;
  
  arr_available_tasks[3] = os_scheduler_sync;

  arr_available_tasks[4] = NULL;
  
}


void os_start_task(void (*ptr_fn)()){
    ptr_fn();
}


void os_delay(int32_t t_sleep){

  if(arr_task_sleep_start_flag[os_current_task_index] == 0){

      arr_task_sleep_start_flag[os_current_task_index] = 1;

      arr_task_state[os_current_task_index] = SLEEPING;

      arr_task_sleep_remaining[os_current_task_index] = t_sleep;
  } 
  
  return;
}


void os_scheduler_sync(void){

  if(os_sFlag == PENDING){
    while(os_sFlag == PENDING){}
    
  } else {
    for(int i = 0; i < NUMBER_OF_TASKS; i++){

      int32_t t_remaining = arr_task_sleep_remaining[i];
  
      if(t_remaining <= 0){
         arr_task_state[i] = READY; 

         arr_task_sleep_remaining[i] = 0;
         arr_task_sleep_start_flag[i] = 0;
      
      } else {
         arr_task_sleep_remaining[i] = t_remaining - 2;
      }
    
    }
    
    os_sFlag = PENDING; 
  }
  
  
}


void os_scheduler(void){

    if(arr_available_tasks[os_current_task_index] == NULL && os_current_task_index != 0) {
      os_current_task_index = 0;
    }
    
    if(arr_available_tasks[os_current_task_index] == NULL && os_current_task_index == 0){
      return;
    }
    
    if(arr_task_state[os_current_task_index] == READY){
      arr_task_state[os_current_task_index] = RUNNING;
    }
    
    
    else if(arr_task_state[os_current_task_index] == RUNNING){
      os_start_task(arr_available_tasks[os_current_task_index]);
    }

    else if(arr_task_state[os_current_task_index] == SLEEPING){
      // Do Nothing
    }
    
    os_current_task_index++;
    
    return;
}



//Timer2 Overflow Interrupt Vector
ISR(TIMER2_OVF_vect) {

  os_sFlag = DONE;
  os_ticks += 2;

  TCNT2 = 5;                // Reset Timer to 5 out of 255
  TIFR2  &= ~(1 << TOV2);   // Timer2 INT Flag Reg: Clear Timer Overflow Flag
};
