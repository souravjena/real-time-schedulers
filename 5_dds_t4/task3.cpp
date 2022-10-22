/**
 * @file      task3.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Task3 driver code
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "task3.h"

static int g_seven_seg_counter = 0;
static int g_seven_seg_digits_arr[4] = {-1, -1, -1, -1};
static int g_seven_seg_digits_pins[4] = {14, 15, 16, 17};

static const int pinA = 30;      // PC7
static const int pinB = 31;      // PC6
static const int pinC = 32;      // PC5
static const int pinD = 33;      // PC4
static const int pinE = 34;      // PC3
static const int pinF = 35;      // PC2
static const int pinG = 36;      // PC1
static const int pinH = 37;      // PC0

static const int D1 = 14;        // PJ1
static const int D2 = 15;        // PJ0
static const int D3 = 16;        // PH1
static const int D4 = 17;        // PH0

static uint32_t time_curr = 0;
static uint32_t time_old = 0;
static uint32_t time_old_small = 0;
static uint32_t global_ticks = 0;
static uint32_t notes_ticks = 0;

static const int seven_seg_digits_leds[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                          { 0,1,1,0,0,0,0 },  // = 1
                                          { 1,1,0,1,1,0,1 },  // = 2
                                          { 1,1,1,1,0,0,1 },  // = 3
                                          { 0,1,1,0,0,1,1 },  // = 4
                                          { 1,0,1,1,0,1,1 },  // = 5
                                          { 1,0,1,1,1,1,1 },  // = 6
                                          { 1,1,1,0,0,0,0 },  // = 7
                                          { 1,1,1,1,1,1,1 },  // = 8
                                          { 1,1,1,0,0,1,1 }   // = 9
                                          };



int seven_seg_digits_freq[6][3] = { {0, 0, 0}, {2, 9, 3},  // = 0
                                                           { 3, 2, 9 },  // = 1
                                                           { 2, 6, 1 },  // = 2
                                                           { 1, 3, 0 },  // = 3
                                                           { 1, 9, 6 }
                                                           };



void pin_write_0(int pin_num){

    switch(pin_num){

      case 14:
      BIT_CLR(PORTJ, PJ1);
      break;

      case 15:
      BIT_CLR(PORTJ, PJ0);
      break;
      
      case 16:
      BIT_CLR(PORTH, PH1);
      break;

      case 17:
      BIT_CLR(PORTH, PH0);
      break;




      case 30:
      BIT_CLR(PORTC, PC7);
      break;

      case 31:
      BIT_CLR(PORTC, PC6);
      break;
      
      case 32:
      BIT_CLR(PORTC, PC5);
      break;

      case 33:
      BIT_CLR(PORTC, PC4);
      break;

      case 34:
      BIT_CLR(PORTC, PC3);
      break;

      case 35:
      BIT_CLR(PORTC, PC2);
      break;
      
      case 36:
      BIT_CLR(PORTC, PC1);
      break;

      case 37:
      BIT_CLR(PORTC, PC0);
      break;

    };
  
}


void pin_write_1(int pin_num){

    switch(pin_num){

      case 14:
      BIT_SET(PORTJ, PJ1);
      break;

      case 15:
      BIT_SET(PORTJ, PJ0);
      break;
      
      case 16:
      BIT_SET(PORTH, PH1);
      break;

      case 17:
      BIT_SET(PORTH, PH0);
      break;




      case 30:
      BIT_SET(PORTC, PC7);
      break;

      case 31:
      BIT_SET(PORTC, PC6);
      break;
      
      case 32:
      BIT_SET(PORTC, PC5);
      break;

      case 33:
      BIT_SET(PORTC, PC4);
      break;

      case 34:
      BIT_SET(PORTC, PC3);
      break;

      case 35:
      BIT_SET(PORTC, PC2);
      break;
      
      case 36:
      BIT_SET(PORTC, PC1);
      break;

      case 37:
      BIT_SET(PORTC, PC0);
      break;

    };
  
}


//--------
void pin_write_mode_0(int pin_num){

    switch(pin_num){

      case 14:
      BIT_CLR(DDRJ, PJ1);
      break;

      case 15:
      BIT_CLR(DDRJ, PJ0);
      break;
      
      case 16:
      BIT_CLR(DDRH, PH1);
      break;

      case 17:
      BIT_CLR(DDRH, PH0);
      break;




      case 30:
      BIT_CLR(DDRC, PC7);
      break;

      case 31:
      BIT_CLR(DDRC, PC6);
      break;
      
      case 32:
      BIT_CLR(DDRC, PC5);
      break;

      case 33:
      BIT_CLR(DDRC, PC4);
      break;

      case 34:
      BIT_CLR(DDRC, PC3);
      break;

      case 35:
      BIT_CLR(DDRC, PC2);
      break;
      
      case 36:
      BIT_CLR(DDRC, PC1);
      break;

      case 37:
      BIT_CLR(DDRC, PC0);
      break;

    };
  
}


void pin_write_mode_1(int pin_num){

    switch(pin_num){

      case 14:
      BIT_SET(DDRJ, PJ1);
      break;

      case 15:
      BIT_SET(DDRJ, PJ0);
      break;
      
      case 16:
      BIT_SET(DDRH, PH1);
      break;

      case 17:
      BIT_SET(DDRH, PH0);
      break;




      case 30:
      BIT_SET(DDRC, PC7);
      break;

      case 31:
      BIT_SET(DDRC, PC6);
      break;
      
      case 32:
      BIT_SET(DDRC, PC5);
      break;

      case 33:
      BIT_SET(DDRC, PC4);
      break;

      case 34:
      BIT_SET(DDRC, PC3);
      break;

      case 35:
      BIT_SET(DDRC, PC2);
      break;
      
      case 36:
      BIT_SET(DDRC, PC1);
      break;

      case 37:
      BIT_SET(DDRC, PC0);
      break;

    };
  
}

//--------

void pin_write(int pin_num, int data){

    if(data == 0){
      pin_write_0(pin_num);  
    
    } else {
      pin_write_1(pin_num);   
    }
  
}


void pin_mode(int pin_num, int data){

    if(data == 0){
      pin_write_mode_0(pin_num);  
    
    } else {
      pin_write_mode_1(pin_num);   
    }
  
}


void seven_seg_counter_increment(){
  g_seven_seg_counter++;

  if(g_seven_seg_counter == 10000){
    g_seven_seg_counter = 0;
  }
}


int seven_seg_num_digits(){
  int digits = 0;
  int num = g_seven_seg_counter;
  
  if(num == 0){
    return 1;  
  }

  while (num != 0){
    num = num / 10;
    digits++;
  }
    
  return digits; 
}


void seven_seg_update_digits_arr(){
  
  int num = g_seven_seg_counter;
  int i = 0;

  while(num != 0){

      int extracted_digit = num % 10;
      g_seven_seg_digits_arr[i] = extracted_digit;
      i++;

      num = num/10;
  }

  for(int j = i; j < 4; j++){
    g_seven_seg_digits_arr[j] = -1;
  }

}


void seven_seg_clear_leds(){
  
  pin_write(pinA, 0);     
  pin_write(pinB, 0);     
  pin_write(pinC, 0);     
  pin_write(pinD, 0);     
  pin_write(pinE, 0);     
  pin_write(pinF, 0);     
  pin_write(pinG, 0);
}


void seven_seg_display_num(int curr_digit){

    if(curr_digit == -1){
      seven_seg_clear_leds();
      return;
    }

    pin_write(pinA, seven_seg_digits_leds[curr_digit][0]);     
    pin_write(pinB, seven_seg_digits_leds[curr_digit][1]);     
    pin_write(pinC, seven_seg_digits_leds[curr_digit][2]);     
    pin_write(pinD, seven_seg_digits_leds[curr_digit][3]);     
    pin_write(pinE, seven_seg_digits_leds[curr_digit][4]);     
    pin_write(pinF, seven_seg_digits_leds[curr_digit][5]);     
    pin_write(pinG, seven_seg_digits_leds[curr_digit][6]); 
  
}

void seven_seg_pick_digit(int x){
  
  switch(x)
  {
    case 0: 
      pin_write(D1, LOW); 
      break;
    case 1: 
      pin_write(D2, LOW); 
      break;
    case 2: 
      pin_write(D3, LOW);
      break;
    default: 
      pin_write(D4, LOW); 
      break;
  }
}


void seven_seg_unpick_digit(int x){

  switch(x)
  {
    case 0: 
      pin_write(D1, HIGH); 
      break;
    case 1: 
      pin_write(D2, HIGH); 
      break;
    case 2: 
      pin_write(D3, HIGH);
      break;
    default: 
      pin_write(D4, HIGH); 
      break;
  }
}


void seven_seg_display(int place, int curr_digit){
    
    seven_seg_display_num(curr_digit);
    seven_seg_pick_digit(place);
    /*
    delay(1);
    */
    
    if((os_ticks - time_old_small) >= 100){
     time_old_small = os_ticks;
    }
    
    
    seven_seg_unpick_digit(place);
    
}



void seven_seg_clear_everything(){

  for(int i = 0; i < 4; i++){
    seven_seg_clear_leds();
    seven_seg_pick_digit(i);
    delay(1);
    seven_seg_unpick_digit(i);
  }
  
}


void init_task3() {                
  pin_mode(pinA, OUTPUT);     
  pin_mode(pinB, OUTPUT);     
  pin_mode(pinC, OUTPUT);     
  pin_mode(pinD, OUTPUT);     
  pin_mode(pinE, OUTPUT);     
  pin_mode(pinF, OUTPUT);     
  pin_mode(pinG, OUTPUT);   
  
  pin_mode(D1, OUTPUT);  
  pin_mode(D2, OUTPUT);  
  pin_mode(D3, OUTPUT);  
  pin_mode(D4, OUTPUT);  

  
}


void task3(void) {
  
  if((os_ticks - time_old) >= 100){
     time_old = os_ticks;

     seven_seg_update_digits_arr();
     seven_seg_counter_increment();
     
  }
     
  seven_seg_display(0, g_seven_seg_digits_arr[0]);
  seven_seg_display(1, g_seven_seg_digits_arr[1]);
  seven_seg_display(2, g_seven_seg_digits_arr[2]);
  seven_seg_display(3, g_seven_seg_digits_arr[3]);


}
