/*
XTAL = 16MHz → Txtal _clock = 1/16 μs
increments 2000x16/n should be within 256
so we need take n as 256 , so prescaler= 1:256
Counter increments needed = 2000x16 / 256 = 125 increments
Initial counter value = 1+255 – 125 = 131
*/
#include <avr/io.h>
void delay_timer0(){
  TCNT0=131;  //setting the initial value as 3036
  TCCR0A=0x00;  //normal mode
  TCCR0B=0x04;  //1:256 pre scaler
  
  while((TIFR0&0x01)==0);
  TCCR0A=0x00;
  TCCR0B=0x00;
  TIFR0=0x01;
}

int main(void){
  DDRB=DDRB|(1<<5);
  while(1){
  PORTB=PORTB|(1<<5);
  delay_timer0();
  PORTB=PORTB& ~(1<<5);
  delay_timer0();
  }
}
