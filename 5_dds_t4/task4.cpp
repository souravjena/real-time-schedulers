/**
 * @file      task4.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Task-4 implementation
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "task4.h"

uint32_t seven_seg_time_old = 0;
uint32_t speaker_time_old = 0;

int g_seven_seg_counter = 0;
int g_seven_seg_digits_arr[4] = {-1, -1, -1, -1};
int g_seven_seg_digits_pins[4] = {14, 15, 16, 17};

void part_task2(){

  if(notes_ticks <= 5){
    seven_seg_display(2, seven_seg_digits_freq[notes_ticks][0]);
    seven_seg_display(1, seven_seg_digits_freq[notes_ticks][1]);
    seven_seg_display(0, seven_seg_digits_freq[notes_ticks][2]);
  }
  
  if((os_ticks - speaker_time_old) >= 1000){

     TIMER4_COUNT_REG = 0; 
     TIMER4_OUTPUT_COMPARE_REG = arr_notes[notes_ticks];
  
     notes_ticks++; 

     speaker_time_old = os_ticks;

     if (notes_ticks == 9){
        notes_ticks = 0; 
     }
  }

  
  
}



void task4(void){

  seven_seg_clear_everything();
  
  part_task2();

  if(notes_ticks >= 6){
    task3();
  }
  
  
}
