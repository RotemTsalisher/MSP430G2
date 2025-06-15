#include <msp430.h> 
#include <stdio.h>

#define BLINK_ 200
#define TRUE   1

/**
 * main.c
 */
int main(void)
{
    volatile int j,i = 0;

    WDTCTL = WDTPW | WDTSSEL;
    P1OUT &= 0x01<<7;
    P1OUT ^= (0x01<<7);
    P1DIR = 0xFF;

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
