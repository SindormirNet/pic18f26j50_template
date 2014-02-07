#include <xc.h>

void pin_mapping_config(void) {

    EECON2=0x55;
    EECON2=0xAA;
    IOLOCK=0;

    RPINR16=7; //RX2 al pin RP7
    RPOR8=5; //TX2 (Función 5) al pin RP8

    EECON2=0x55;
    EECON2=0xAA;
    IOLOCK=1;
}

void ad_config(void) {

    ADON = 0; //Disable A/D module
    ANCON0 = 0xFF; //AN0-AN7 as digital
    ANCON1 = 0x1F; //AN8-AN12 as digital and Band Gap Reference disabled (save power)
}

void tmr0_config(void) {
    T0PS0 = 1;  // Prescaler LSB    101==4 segundos
    T0PS1 = 0;
    T0PS2 = 1;  // Prescaler MSB
    PSA = 0;    // Usar prescaler
    T0SE = 0;   // Incremente en flanco de subida
    T0CS = 0;   // Clock source from CLKO
    T08BIT= 0;  // Configuración para 16bits

    TMR0ON= 1;  // Activa TMR0
}

void tmr0_start(void) {
    TMR0L = 0x00;
    TMR0H = 0x00;
}
