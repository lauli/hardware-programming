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

void SysTick_Handler(void){
    P2->OUT ^= 0x40;
}

void main(void)
{
    __disable_irq();

    CS->KEY = CS_KEY_VAL;
    CS->CTL0 = CS_CTL0_DCORSEL_0;
    CS->KEY = 0;

    P2->DIR |= 0x40;        //blinking LED
    P2->OUT &= ~0x40;

    P2->DIR |= 0x10;        //toogle LED
    P2->OUT &= ~0x10;

    P3->IES = 0x20;
    P3->IFG = 0;
    P3->IE = 0x20;
    NVIC_EnableIRQ(PORT3_IRQn);

    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; //enable SysTick
    SysTick->LOAD = 1500000-1;  //load value
    SysTick->VAL = 0xe0; //clear (dummy write)
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //enable interrupt for SysTick

    __enable_irq();

    for(;;){};
	
}
