#include <xc.h>

void interrupt_config(void) {
    //Página 109 del DS

    IPEN=1; // Enable priority levels on interrupts
    PEIE=1;

    GIE=1;  // Global Interrupt Enable

    RC1IE=1;    //Interrupciones por USARTs
    RC2IE=1;

    TMR0IP=0; // Low priority interrupt
    TMR0IE=0; // Deshabilita la interrupción de TMR0

    IPR1=0;
}

void interrupt isr(void) {
    /*
     *  Interrupción por USART
     */
    if (RC2IF && RC2IE) {
        if (RCSTA2&0x02 || RCSTA2&0x04) {
            RCSTA2 &= 0xEF;
            RCSTA2 |= 0x10;
        }
        else {
            //rxbuffer[rx_idx++]=RCREG2;
            //rxbuffer[rx_idx]='\0';
        }
    }
}

void interrupt low_priority lpisr(void) {
    /*
     *  Interrupción por TIMER0
     */
    if(TMR0IF && TMR0IE) {
        //Código aquí
        TMR0IF = 0;
    }
}

