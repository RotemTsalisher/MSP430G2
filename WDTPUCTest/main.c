#include <msp430.h> 
#include <stdio.h>

#define BLINK_ 20000
#define TRUE   1

/**
 * main.c
 */
int main(void)
{
	volatile int j,i = 0;
	
	P1OUT = 0x00;
	P1DIR = 0xFF;

	if(IFG1&WDTIFG)
	{
	    WDTCTL = WDTPW | WDTHOLD;

	    P1OUT |= ((IFG1&WDTIFG)<<7);
	    IFG1 &= (~WDTIFG);
	    for(j = 0; j<BLINK_; j++);
	}

	for(i =1 ; i<5; i++)
	{
	    P1OUT ^= (0x01<<6);
	    for(j = 0; j<BLINK_; j++);
	}


	//program
	while(TRUE)
	{
	    P1OUT ^= 0x01;
	    for(i = 0; i<BLINK_; i++);
	}

	return 0;
}
