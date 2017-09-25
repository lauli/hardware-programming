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
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    for(;;) {
        listen_for_button_s1_press();
    }
}

