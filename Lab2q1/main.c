#include <msp430.h> 

#define LED                 0x01
#define BUTTON              0x01<<3
#define CLEAR_ALL           0x00

#define SET_BIT(VEC,BIT)    (VEC |= (0x01<<BIT))
#define CLEAR_BIT(VEC,BIT)  (VEC &= (~(0x01<<BIT)))
#define TOGGLE(VEC,BIT)     (VEC ^= (0x01<<BIT))

#define PORT1_INT_VEC       0x0FFE4

#define RISING_EDGE_EXAMPLE

void PORT1_ISR(void) __attribute__((interrupt(PORT1_VECTOR)));

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	_enable_interrupts();

	SET_BIT(P1DIR, 0);
	P1REN = CLEAR_ALL; // pull down pins
	P1OUT = CLEAR_ALL;
    SET_BIT(P1REN,3); //
    SET_BIT(P1OUT,3); // pull up pins (last 2 lines)

#ifdef FALLING_EDGE_EXAMPLE

	SET_BIT(P1IES,3); // falling edge detect

#elif defined(RISING_EDGE_EXAMPLE)

	CLEAR_BIT(P1IES,3); // rising edge detect
#endif

    P1IFG = CLEAR_ALL;
	SET_BIT(P1IE,3);

	while(1);
	return 0;
}

void PORT1_ISR(void)
{

   switch(P1IFG)
   {
   case BIT0:
       break;
   case BIT1:
       break;
   case BIT2:
       break;
   case BIT3:
       TOGGLE(P1OUT,0);
       CLEAR_BIT(P1IFG,3);
       break;
   }
   P1IFG = CLEAR_ALL;
}
