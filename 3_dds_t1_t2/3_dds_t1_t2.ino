/**
 * @file      3_dds_t1_t2.ino
 * @author    Sourav Jena, Yi Chen
 * @brief     main file for DDS Scheduler running Task-1 and Task-2 of Lab-3
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
