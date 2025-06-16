#include <msp430.h> 

#define LED                 0x01
#define BUTTON              0x01<<3
#define CLEAR_ALL           0x00
#define FALSE               0
#define TRUE                !FALSE

#define SET_BIT(VEC,BIT)    (VEC |= (0x01<<BIT))
#define CLEAR_BIT(VEC,BIT)  (VEC &= (~(0x01<<BIT)))
#define TOGGLE(VEC,BIT)     (VEC ^= (0x01<<BIT))
#define IS_LOW(VEC,BIT)     !(VEC&(0x01<<BIT))
#define IS_HIGH(VEC,BIT)    (VEC&(0x01<<BIT))

#define WAIT(T)             __attribute__((__delay_cycles(T)))

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1OUT = CLEAR_ALL;
	P1DIR = CLEAR_ALL;

	SET_BIT(P1DIR,0);
	SET_BIT(P1REN,3);
	SET_BIT(P1OUT,3);

	while(TRUE)
	{
	    // state 00
	    if(IS_LOW(P1IN,3))
	    {
	        WAIT(20000);
	        while(IS_LOW(P1IN,3));

	        while(IS_HIGH(P1IN,3))
	        {
	            //state 01
	            TOGGLE(P1OUT,0);
	            WAIT(100000);

	            if(IS_LOW(P1IN,3))
	            {
	                WAIT(20000);
	                while(IS_LOW(P1IN,3));
	                CLEAR_BIT(P1OUT,0);
	                break;
	            }
	        }

	    }
	}
	return 0;
}
