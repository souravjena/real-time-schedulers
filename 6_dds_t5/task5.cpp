/**
 * @file      task5.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Task5 driver code
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "task5.h"

void init_task5(void){
  init_task1();
  init_task2();
  init_task3();  
}

void task5(void){

  /*
   * 1. T1 runs all the time
   * 2. T2 run 2x times
   * 3. T3 countdown for 3 seconds
   * 4. T2 run 1x time
   * 5. Dispaly smile for 2 seconds
   */
   static uint32_t t_smile_start;
   
   if((os_ticks > 0) && (os_ticks < 18000)){
      os_from_task_start(&os_task[0]);
      os_from_task_start(&os_task[1]);
      os_delay(18000);
   }

   else if((os_ticks > 18000) && (os_ticks < 21000)){
      os_from_task_stop(&os_task[1]);
      os_from_task_start(&os_task[2]);
      os_delay(3000); 
   }

   else if((os_ticks > 21000) && (os_ticks < 30000)){
      os_from_task_stop(&os_task[2]);
      os_from_task_start(&os_task[1]);
      os_delay(9000); 
   }

   else if((os_ticks > 30000) && (os_ticks < 30100)){
      os_from_task_stop(&os_task[1]);
      t_smile_start = os_ticks;
       
   } else {

    if(os_ticks - t_smile_start <= 2000){
      seven_seg_display_smile();
     }
     
   }
   
   
}
