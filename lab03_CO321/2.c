/*
Q2
XTAL = 16MHz → Txtal _clock = 1/16 μs
with  timer0 we only can use upto 255 counts, so we need less number clock counts for maximum time
there fore we are taking maximum pre scale 
maximum prescale 1:1024
counter clock of timer0 with prescale = 1024 × 1/16 μs = 64μs
so max interval that we can take from timer0 =256 x 64=16384 μs =16.384ms
So we can't increase the delay to 500ms
*/

/*
highest countable time interval = 16.384ms
*/

