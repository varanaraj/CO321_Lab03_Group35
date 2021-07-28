/*
XTAL = 16MHz → Txtal _clock = 1/16 μs
increments should be within 65536 for timer1
we take prescale as 256
time period for one clock = (1/16)256=16 micro seconds
Counter increments needed for 1s = 1000x1000 / 16 = 62500 increments
Initial counter value = 65536 - 62500 =3036

*/
#include<avr/io.h>
#include<avr/interrupt.h>
#define BLINK_DELAY_MS 1000



void led(){
  //setup initial value as 3036
  TCNT1 = 0xBDC;           

 //normal mode and 1:256 pre scaler
  TCCR1A = 0x00;      
  TCCR1B = 0x04;     

  //overflow control interrupt enable
  TIMSK1 = (1 << TOIE1) ;
	
  //global interrupts enable
  sei();  
}

 //  Inturupt service routine
ISR (TIMER1_OVF_vect)   
{
  //toggle the portB
  PORTB = PORTB^(1 << 5);
  //clear timer setting
  
  TCNT1 = 0xBDC;  
}




int main (void){

  //set output pins
  DDRB = DDRB | 0b00101111;
  
  //for emitting led with 1sec delay
  led();
  
  int z;
 	while(1){
     //forward light pattern
      for(int i=0;i<=3;i++){
        PORTB= PORTB|(1<<i);
        _delay_ms(BLINK_DELAY_MS);
        PORTB= PORTB&~(1<<i);
         
      }
     //  backword light pattern          
      for(int j=2;j>0;j--){
         PORTB= PORTB|(1<<j);
        _delay_ms(BLINK_DELAY_MS);
         PORTB= PORTB&~(1<<j);
       
      }         
     }

               
}
