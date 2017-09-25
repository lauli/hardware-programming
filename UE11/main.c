//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include <driverlib/driverlib.h>

static const int KEY_EVENT = 555;
enum { STATE_OFF = 0, STATE_ON = 1, MAX_STATES = 2};
static int currentState = STATE_OFF;

void stateMachine(int event){

    if(event != KEY_EVENT) return;

    switch(currentState){
        case STATE_OFF:{
            P2->OUT |= 0x10;
            currentState = STATE_ON;
        }break;
        case STATE_ON:{
            P2->OUT &= ~0x10;
            currentState = STATE_OFF;
        }break;
        default:
            break;
    }
}

int getRawKey(){
    return P3->IN & 0x20;
}

void SysTick_Handler(void){
    //P2->OUT ^= 0x40;
    static uint8_t shiftRegister = 0;

    shiftRegister = (shiftRegister << 1) | !getRawKey();

    if(shiftRegister == 15){
        stateMachine(KEY_EVENT);
    }
}


void WDT_A_IRQHandler(void)
{
    //P5->OUT ^= 0x40;
}

void main(void)
{
    __disable_irq();

    P2->DIR |= 0x40;        //blinking LED
    P2->OUT &= ~0x40;

    P2->DIR |= 0x10;        //toogle LED
    P2->OUT &= ~0x10;

    P5->DIR |= 0x40;        //test LED
    P5->OUT &= ~0x40;       // turn LED off

    CS->KEY = CS_KEY_VAL;
    CS->CTL0 = CS_CTL0_DCORSEL_0;
    CS->KEY = 0;

    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; //enable SysTick
    SysTick->LOAD = 10000-1;  //load value
    SysTick->VAL = 0xe0; //clear (dummy write)
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //enable interrupt for SysTick

    //setup Watchdog
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_SSEL__SMCLK | WDT_A_CTL_TMSEL | WDT_A_CTL_CNTCL | WDT_A_CTL_IS_3;
    Interrupt_enableInterrupt(INT_WDT_A);


    __enable_irq();

    for(;;){};
	
}
