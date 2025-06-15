#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1REN = 0x01<<3; // enable pull up/down on 1.3 (this is the s2 switch leg)

	P1OUT = 0x01<<3; // pull up res
	P1IN = 0x00;
	P1DIR = 0x01<<3;

	return 0;
}
