#include <msp430.h> 

#define UP_    2300  // 0.1 sec
#define DOWN_  20700 // 0.9 sec
#define FALSE  0
#define TRUE   !FALSE

/**
 * main.c
 */
int main(void)
{
    volatile long long int i = 0;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1OUT = 0x01;
	P1DIR = 0xFF;

	while(TRUE)
	{
	    for(i = 0; i<(UP_ + DOWN_); i++);
	    P1OUT ^= (0x01<<6);
	    P1OUT ^= (0x01);

	}

	return 0;
}
