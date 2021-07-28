/*
XTAL = 16MHz → Txtal _clock = 1/16 μs
increments 1x16/n should be within 65536
so we need take n as 16 , so prescaler= 1:16
Counter increments needed = 1000x1000 / 16 = 62500 increments
Initial counter value = 65535+1 - 62500 =3036

*/
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define BLINK_DELAY_MS 1000


void delay_timer1(){
  //setup initial value
  TCNT1 = 3036;           

//setup normal mode and 1:256 pre scaler
  TCCR1A = 0x00;      
  TCCR1B = 0x04;     

//overflow control interrupt enable
  TIMSK1 |= 0x01;
  //global interrupts enable
  sei();  
}

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
  //toggle the portB
	PORTB = PORTB^(1 << 5);	
  TCCR1A = 0x00; //clear timer setting
  TCCR1B = 0x00;
  delay_timer1();
}




int main (void){

  //set output pins
  DDRB = DDRB | 0b00101111;

  delay_timer1();
    int z;
  while(1){
      
		for(z=1;z<=8;z*=2){
			PORTB=z;
			_delay_ms(BLINK_DELAY_MS);
      PORTB=PORTB&~(z);
			
		}
		for(z=4;z>=2;z/=2){
			PORTB=z;
			_delay_ms(BLINK_DELAY_MS);
      PORTB=PORTB&~(z);
		}
  }

               
}