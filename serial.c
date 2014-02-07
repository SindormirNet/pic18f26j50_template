#include <xc.h>
#include "config.h"

//Serial port configuration
#define RS232_BAUD 9600
#define DIVIDER ((int)(_XTAL_FREQ/(16UL * RS232_BAUD) -1))

void serial_init(void) {
    //BAUDCON &= 0xF0;
    SPBRG = DIVIDER;
    RCSTA = 0x90; //SPEN + Continuous Receive Enable bit
    TXSTA = 0x24; //High baud rate + TXEN

    SPBRG2 = DIVIDER;
    RCSTA2 = 0x90; //SPEN + Continuous Receive Enable bit
    TXSTA2 = 0x24; //High baud rate + TXEN

    //Configuración puertos
    TRISC7 = 1;
    TRISC6 = 0;
    TRISB4 = 1;
    TRISB5 = 0;
}

void putch(unsigned char c){
    while(!TRMT1)    // TRMT1 is set when TSR is empty
        continue;
    TXREG = c;      // load the register
}

void putch2(unsigned char c){
    while(!TRMT2)    // TRMT2 is set when TSR is empty
        continue;
    TXREG2 = c;      // load the register
}

void serial_out(const char *str){ //was register
    while((*str)!=0)
        putch(*str++);
}

void serial_out2(const char *str){ //was register
    while((*str)!=0)
        putch2(*str++);
}

