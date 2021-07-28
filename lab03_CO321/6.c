/*
calculation for time 500 ms

(1/(p*16))*c=500*1000
r*c=16*500*1000
lets c=256
r=31,250
intial value=65536-31250=34,286

calculation for time 2 ms using timer0

(1/(p*16))*c=2000
r*c=16*2000
lets r=256
c=125
initial value 256-125=131
*/

#include<avr/io.h>
#include<avr/interrupt.h>
void delay50(){

}

void delay_timer1(){
    TCNT1 = 34286;  //setting the initial value as 34285

    TCCR1A = 0x00;      //normal mode
    TCCR1B = 0x04;      //1:256 pre scaler

    sei();
    //enable timer1 overflow control interrupt
    TIMSK1|=(1<<0);
}

ISR(TIMER1_OVF_vect){
    PORTB^=(1<<1);
    TCCR1A=0x00;
    TCCR1B=0x00;
    delay_timer1();
}

void delay_timer0()
{
    TCNT0 = 131;    //setting the initial value as 131

    TCCR1A = 0x00;      //normal mode
    TCCR1B = 0x04;      //1:256 pre scaler

    sei();
    //enable timer0 overflow control interrupt
    TIMSK0 |= 0x01;
}
int count = 0;
ISR(TIMER0_OVF_vect)
{
    count++;
    if (count == 25)
    {
        PORTB ^= (1 << 2);
        count = 0;
    }
    delay_timer0();
}

int main(void)
{
    //set pin 1 and pin 2 of PortB
    DDRB|=(1<<1);
    DDRB |= (1 << 2);
    delay_timer1();
    delay_timer0();
    while (1);
    
}