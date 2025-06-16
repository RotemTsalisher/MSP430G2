#include <msp430.h> 

#define FALSE 0
#define TRUE  !FALSE

#define ISLOW(VECTOR, BIT)   (!(VECTOR & (0x01<<BIT)))
#define TOGGLE(VECTOR, BIT)  (VECTOR ^= (0x01<<BIT))

/**
 * main.c
 */
int main(void)
{
    int i;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1OUT = 0x01<<3;
	P1REN = 0x01<<3;
	P1DIR = 0x01;
	P1IE  = 0x01<<3;
	
	while(TRUE)
	{
	    while(ISLOW(P1IN,3))
	    {
	        TOGGLE(P1OUT,0);
	        for(i = 0; i<10000; i++);
	    }
	    P1OUT &= ~0x01;
	}
	return 0;
}
