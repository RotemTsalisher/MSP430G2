#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1IN  = 0x00;
	P1REN = 0x01<<3;
	P1OUT = 0x01<<3; // pull down

	P1DIR = 0x01<<3;

	while(1)
	{
	    P1OUT = (P1IN&(0x01<<3))>>3;
	}
	return 0;
}
