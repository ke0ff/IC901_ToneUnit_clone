/*************************************************************************
 *********** COPYRIGHT (c) 2021 by Joseph Haas (AKA KE0FF)  *********
 *
 *  File name: f300_init.c
 *
 *  Module:    Control
 *
 *  Summary:   This is the MCU init file from ConfigWizardII
 *
 *******************************************************************/


/********************************************************************
 *  File scope declarations revision history:
 *    05-08-21 jmh:  copied from ConfigWizardII
 *******************************************************************/

/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "compiler_defs.h"
#include "c8051F520.h"

// Peripheral specific initialization functions,
// Called from the Init_Device() function
void Reset_Sources_Init()
{
    int i = 0;
    VDDMON    = 0x80;
    for (i = 0; i < 20; i++);  // Wait 5us for initialization
}

void PCA_Init()
{
    PCA0CN    = 0x40;
    PCA0MD    &= ~0x40;
    PCA0MD    = 0x08;
    PCA0CPM0  = 0x21;
    PCA0CPM1  = 0x42;
    PCA0CPM2  = 0x21;
    PCA0CPH1  = 0x80;
}

void Timer_Init()
{
    TCON      = 0x40;
    TMOD      = 0x22;
    CKCON     = 0x0C;
    TL0       = 0x80;
    TH0       = 0x80;
    TMR2RLL   = 0x2C;
    TMR2RLH   = 0xFA;
    TMR2L     = 0x2C;
    TMR2H     = 0xFA;
}

void Voltage_Reference_Init()
{
    REF0CN    = 0x11;
} 

void Port_IO_Init()
{
    // P0.0  -  Skipped,     Open-Drain, Analog
    // P0.1  -  CEX0  (PCA), Open-Drain, Digital
    // P0.2  -  CEX1  (PCA), Push-Pull,  Digital
    // P0.3  -  CEX2  (PCA), Open-Drain, Digital
    // P0.4  -  TX   (UART), Push-Pull,  Digital
    // P0.5  -  RX   (UART), Open-Drain, Digital
    // P0.6  -  Unassigned,  Open-Drain, Digital
    // P0.7  -  Skipped,     Open-Drain, Analog

    // P1.0  -  Skipped,     Open-Drain, Analog
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Push-Pull,  Digital
    // P1.3  -  Unassigned,  Push-Pull,  Digital
    // P1.4  -  Unassigned,  Push-Pull,  Digital
    // P1.5  -  Unassigned,  Push-Pull,  Digital
    // P1.6  -  Unassigned,  Push-Pull,  Digital
    // P1.7  -  Unassigned,  Push-Pull,  Digital

    P0MDIN    = 0x7E;
    P1MDIN    = 0xFE;
    P0MDOUT   = 0x14;
    P1MDOUT   = 0xFC;
    P0SKIP    = 0x81;
    P1SKIP    = 0x01;
    P0SKIP    |= 0x30;
    XBR0      = 0x01;
    XBR1      = 0x43;
}

void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x76;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    CLKSEL    = 0x01;
    OSCICN    = 0x00;
}

void Interrupts_Init()
{
    EIE1      = 0x04;
    IE        = 0x08;
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    Reset_Sources_Init();
    PCA_Init();
    Timer_Init();
    Voltage_Reference_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}
