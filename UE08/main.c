//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"


int boostEnabled = 0;
// P3 Interrupt service routine
void PORT3_IRQHandler(void){
    if(P3IV & 0x0C) { //Boot Btn pressed
        if(boostEnabled){
            CS->KEY = CS_KEY_VAL;
            CS->CTL0 = CS_CTL0_DCORSEL_0;
            CS->KEY = 0;

        } else {
            CS->KEY = CS_KEY_VAL;
            CS->CTL0 = CS_CTL0_DCORSEL_1;
            CS->KEY = 0;
        }

        boostEnabled = !boostEnabled;
        P2->OUT ^= 0x10;
    }
}


void main(void)
{
    int MAX_COUNT = 100000;
    int count = 0;
    __disable_irq();

    CS->KEY = CS_KEY_VAL;
    CS->CTL0 = CS_CTL0_DCORSEL_0;
    CS->KEY = 0;

    P2->DIR |= 0x40;        //blinking LED
    P2->OUT &= ~0x40;

    P2->DIR |= 0x10;
    P2->OUT &= ~0x10;

    /*P3->REN = 0x20;
    P3->OUT = 0x20;*/
    P3->IES = 0x20;
    P3->IFG = 0;
    P3->IE = 0x20;
    NVIC_EnableIRQ(PORT3_IRQn);
    __enable_irq();

    for(;;){
        if(count == MAX_COUNT){
            count = 0;
            P2->OUT ^= 0x40;
        }
        count++;
    }
	
}
