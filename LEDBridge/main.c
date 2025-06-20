#include <msp430.h> 

#define WAIT_         200000
#define STATES_       6
#define DEBOUNCE_     50000

typedef enum
{
    INIT      = 0x05,
    STATE_ONE = 0x00,
    STATE_TWO = 0x01,
    STATE_TREE = 0x02,
    STATE_FOUR = 0x03,
    STATE_FIVE = 0x04
}state_machine;

void PORT1_ISR(void) __attribute__((interrupt(PORT1_VECTOR)));
void state_one(void);
void state_two(void);
void state_three(void);
void state_four(void);
void state_five(void);

void (*stateMachine[STATES_])(void) = {&state_one, &state_two, &state_three, &state_four, &state_five};
volatile state_machine s_ = INIT;
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	_enable_interrupts();
	
	s_ = INIT;
	P1REN = 0xCE;
	P1OUT = 0x01<<3;

	P1IFG = 0x00;
	P1IES &= ~(0x01<<3);
	P1IE = 0x01<<3;

	while(1);
	return 0;
}
void PORT1_ISR(void)
{
    __delay_cycles(DEBOUNCE_);
    P1IFG &= 0x00;
    s_++;
    stateMachine[(s_)%STATES_]();
    return;
}
void state_one(void)
{
    P1OUT |= (0x01 | 0x01<<5);
    P1DIR |= (0x01 | 0x01<<5);
}
void state_two(void)
{
    while(!(P1IFG & (0x01<<3)))
    {
        P1OUT ^= (0x01<<5);
        __delay_cycles(WAIT_);
    }
}
void state_three(void)
{
    P1OUT &= ~(0x01<<5);
    P1OUT |= 0x01<<4;
    P1DIR |= 0x01<<4;
}
void state_four(void)
{
    while(!(P1IFG & (0x01<<3)))
    {
        P1OUT ^= (0x01<<4);
        __delay_cycles(WAIT_);
    }
}
void state_five(void)
{
    P1OUT &= ~(0x01<<5 | 0x01<<4);
    while(!(P1IFG & (0x01<<3)))
    {
        P1OUT ^= (0x01<<4);
        P1OUT ^= (0x01<<5);
        __delay_cycles(WAIT_);
    }
    P1OUT &= ~(0x01<<5 | 0x01<<4);
}
void state_six(void)
{
    P1OUT &= ~(0x01<<5 | 0x01<<4 | 0x01);
}
