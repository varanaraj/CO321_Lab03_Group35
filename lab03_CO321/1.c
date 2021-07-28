/*
XTAL = 16MHz → Txtal _clock = 1/16 μs
increments 2000x16/n should be within 256
so we need take n as 256 , so prescaler= 1:256
Counter increments needed = 2000x16 / 256 = 125 increments
Initial counter value = 1+255 – 125 = 131
*/
#include <avr/io.h>
void delay_timer0(){
  
  TCNT0=0x83;  //setting the initial value as 131
  //setting up Timer/Counter Control Register or Timer/counter 0
  TCCR0A=0x00;  //normal mode
  TCCR0B=0x04;  //1:256 pre scaler
  
  //wait until TheTimer/Counter Interrupt Flag Register indicate overflow
  while((TIFR0 & 0x01)==0);
  //resetting  Timer/Counter Control Register or Timer/counter 0
  TCCR0A=0x00;
  TCCR0B=0x00;
  //crearing TheTimer/Counter Interrupt Flag Register
  TIFR0=0x01;
}

int main(void){
  //set  pin for 5 with directional data registor for port b
  DDRB=DDRB|(1<<5);
  
  while(1){
  //toggle until pin 5
  PORTB=PORTB^(1<<5);
  //wait for 2ms
  delay_timer0();
  }
}
