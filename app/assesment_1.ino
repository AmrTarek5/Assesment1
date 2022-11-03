#include <avr/io.h>
#include "adc.h"
#include "uart.h"


void init();
int reading = 0;

int main(void){
  init();
  while(1)
  {
    int check = PIND & (1 <<2);  // checking the status of the button 

    if(check)  // Checking if the button is not pressed 
    {
        Uart_SendString("\n system is off \n");   // printing (system is off) on the serial monitor 
        PORTD = PORTD &~ (1<<5);                  // Lighting up the First LED 
        reading = Adc_ReadChannel(0); }           // Monitoring ADC Activities 
    else{                                         // checking if the button is pressed 
          Uart_SendString("system is on \n");     // printing (system is on) on  the serial monitor 
          PORTD = PORTD| (1<<5);                  // Turning off the First LED 
          reading = Adc_ReadChannel(0);           // Monitoring ADC Activities
      }

      char reading1[4];                          // reading the value of the ADC 
      itoa(reading, reading1, 10);               // changing the reading value into a string 
      Uart_SendString(reading1);                 // Printing the string on the serial monitor 
       Uart_SendString("\n");  
    if (reading < 300)                          // checking if the potentiometer value is less than 300 
    { 
      PORTD = PORTD| (1<<6);                    // turning on the second LED 
      Uart_SendString("\n  High light intensity  \n");      // Printing ( high ligh intensity ) on the serial monitor 
      }
    else{
      
       PORTD = PORTD &~ (1<<6);    // Turning off the second LED
        Uart_SendString("\n low light intensity  \n");    // Printing ( low light intensity ) on the serial monitor 
    }
     
  }
  return 0;
}

void init(){
  Adc_Init();
  Uart_Init();
   
  DDRD = DDRD & ~(1 << 2);      // switch (clearing bit)
  PORTD= PORTD | (1<<2);        // Activiting the pull up resisitance
  DDRD = DDRD | (1 << 5);       // LED1 ( setting  bit )
  DDRD = DDRD | (1 << 6);       // LED2 (setting  bit )
  
}
