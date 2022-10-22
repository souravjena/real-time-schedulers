/**
 * @file      6_dds_t5.ino
 * @author    Sourav Jena, Yi Chen
 * @brief     main file for DDS Scheduler running Task-5 of Lab-3
 * @version   1.0
 * @date      2022-05-28
 * 
 */


#include "os.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

void setup(){
  init_task1();
  init_task2();
  init_task3();
  
  os_init();

}


void loop(){
  os_scheduler();
}
