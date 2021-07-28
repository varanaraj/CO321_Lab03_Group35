/*
calculate time delay for 4ms using timer0

(1/(p*16))*c=4,000
c*r =16*4000
lets r=256
c=250
intial value=256-250=6
*/
#include<avr/io.h>
#include<avr/interrupt.h>
void delay_timer0(){
    TCNT0=6;    //setting the initial value as 6

    //normal mode and 1:256 prescaler
    TCCR0A=0x00;
    TCCR0B=0x04;
    // Enable global interrupts
    sei();
    //enable timer0 overflow control interrupt
    TIMSK0|=0x01;
}
int itter=0;
ISR(TIMER0_OVF_vect)
{
    itter++;
    if(itter==25){
        PORTB^=(1<<1);
        itter=0;
    }
    TCNT0=6;
}

int main(void){
    DDRB|=(1<<1);
    delay_timer0();
    while(1);
    return 0;
}