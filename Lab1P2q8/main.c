#include <msp430.h> 

#define FALSE 0
#define TRUE  !FALSE

void wait(unsigned int k);

/**
 * main.c
 */
int main(void)
{
    unsigned int i,T = 250;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1OUT = 0x00;
	P1DIR = 0x01;

	while(TRUE)
	{
	    for(i = 0; i<T; i++)
	    {
	        P1OUT &= (~0x01);
	        wait(i);
	        P1OUT |= 0x01;
	        wait(T-i);
	    }
	}
	
	return 0;
}
void wait(unsigned int k)
{
    //__delay_cycles((unsigned long)(100*k));
    int i;
    for(i = 0; i<10*k; i++);
}
