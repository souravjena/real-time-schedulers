/**
 * @file      2_srri_t1_t2.ino
 * @author    Sourav Jena, Yi Chen
 * @brief     main file for the SRRI Scheduler running Task-1, Task-2 and Task-3 of Lab-3
 * @version   1.0
 * @date      2022-05-28
 * 
 */


#include "os.h"
#include "task1.h"
#include "task2.h"

void setup(){
  init_task1();
  init_task2();
 
  os_init();
}


void loop(){
  os_scheduler();
}
