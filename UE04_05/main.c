//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "driverlib/driverlib.h"

//Grand Total:                  code:1688   ro data:265  rw data:1080
void main(void)
{
    int MAX_COUNT = 230000;
    int count = 0;
    bool redIsOn = false;

    P5->DIR |= 0x40; // P5.0 as output (LED)
    P5->OUT &= ~0x40; // turn LED off

    /*P2->DIR |= 0x10;
    P2->OUT &= ~0x10;*/
    BITBAND_PERI(P2->DIR, 4) = 1;
    BITBAND_PERI(P2->OUT, 4) = 0;

    /*P2->DIR |= 0x40;
    P2->OUT &= ~0x40;*/
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN6);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN6);

    for (;;) {
        if (!(P5->IN & 0x02)) { // S1
            P5->OUT |= 0x40; // turn on
        } else {
            P5->OUT &= ~0x40; // turn off
        }


        if(BITBAND_PERI(P3->IN, 5) == 0){
            BITBAND_PERI(P2->OUT, 4) = !BITBAND_PERI(P2->OUT, 4);
        }

        if(count == MAX_COUNT){

            if(redIsOn){
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN6);
            }else{
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN6);
            }
            redIsOn = !redIsOn;
            count = 0;
        } else {
            count++;
        }

    }
    //WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	
}
