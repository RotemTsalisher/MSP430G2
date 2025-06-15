#include <msp430.h> 

/**
 * main.c
 */
int main(void)
{

    unsigned int* p_p1dir, *p_p1out,i=0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	p_p1dir = 0x022;
	p_p1out = 0x021;

	*(p_p1out) = 0x00;
	*(p_p1dir) = 0xFF;


	while(1)
	{
	    *(p_p1out) ^= 0x01;
	    for(i = 0; i<10000; i++);
	}

	return 0;
}
