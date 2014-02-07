#include <xc.h>
#include "config.h"
#include "peripherals.h"
#include "serial.h"
#include "interrupts.h"

//Function prototypes
void init(void);
void delay(unsigned int);

// PIC18F26J50 Configuration Bit Settings

// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset  (Enabled)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config CPUDIV = OSC1    // CPU System Clock Postscaler (No CPU system clock divide)
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = INTOSC     // Oscillator (INTOSC)
#pragma config T1DIG = OFF      // T1OSCEN Enforcement (Secondary Oscillator clock source may not be selected)
#pragma config LPT1OSC = ON     // Low-Power Timer1 Oscillator (Low-power operation)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2H
#pragma config WDTPS = 4096     // Watchdog Postscaler (1:4096)

// CONFIG3L
#pragma config DSWDTOSC = INTOSCREF// DSWDT Clock Select (DSWDT uses INTRC)
#pragma config RTCOSC = INTOSCREF// RTCC Clock Select (RTCC uses INTRC)
#pragma config DSBOREN = OFF    // Deep Sleep BOR (Disabled)
#pragma config DSWDTEN = OFF    // Deep Sleep Watchdog Timer (Disabled)
#pragma config DSWDTPS = 8192   // Deep Sleep Watchdog Postscaler (1:8,192 (8.5 seconds))

// CONFIG3H
#pragma config IOL1WAY = OFF    // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set and cleared as needed)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_63   // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 63)
#pragma config WPEND = PAGE_WPFP// Write/Erase Protect Region Select (valid when WPDIS = 0) (Page WPFP<5:0> through Configuration Words erase/write protected)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<5:0>/WPEND region ignored)


void init(void){
    int i;

    TRISB = 0x81;           //All PORTB as outputs except RB0 and RB7
    TRISC = 0b11111011;     //All PORTC as inputs

    serial_init();

    serial_out("\nIniciando programa: PIC18F26J50: Plantilla basica\n");

    pin_mapping_config();
    interrupt_config();
    tmr0_config();
    tmr0_start();
    ad_config();
}

void main(void){
    init();

    serial_out("Sindormir.net\n");

    while (1){
        RB1 = 1;
        delay(1);
        RB1 = 0;
        delay(1);
    }

}

void delay(unsigned int s) {
    int i;
    for (i=0; i<6*s; i++)
        __delay_ms(166);
}
