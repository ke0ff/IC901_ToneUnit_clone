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
    VDDMON    = 0xA0;
    for (i = 0; i < 20; i++);  // Wait 5us for initialization
    RSTSRC    = 0x02;
}

void PCA_Init()
{
    PCA0CN    = 0x40;
    PCA0MD    &= ~0x40;
    PCA0MD    = 0x02;
    PCA0CPM0  = 0x21;
    PCA0CPM1  = 0x42;
    PCA0CPM2  = 0x42;
    PCA0CPH1  = 0x80;
    PCA0CPH2  = 0x80;
}

void Timer_Init()
{
    TCON      = 0x40;
    TMOD      = 0x22;
    CKCON     = 0x05;
    TL0       = 0x80;
    TH0       = 0x80;
    TMR2CN    = 0x04;
    TMR2RLL   = 0x06;
    TMR2RLH   = 0xF8;
    TMR2L     = 0x06;
    TMR2H     = 0xF8;

/*    TCON      = 0x40;
    TMOD      = 0x20;
    CKCON     = 0x01;
    TMR2CN    = 0x04;
    TMR2RLL   = 0x06;
    TMR2RLH   = 0xF8;
    TMR2L     = 0x06;
    TMR2H     = 0xF8;*/
}

void SPI_Init()
{
    SPI0CFG   = 0x40;
    SPI0CN    = 0x00;
    SPI0CKR   = 0x79;
}

void Comparator_Init()
{
    int i = 0;
    CPT0CN    = 0x85;
    for (i = 0; i < 35; i++);  // Wait 10us for initialization
    CPT0CN    &= ~0x30;
    CPT0MX    = 0x75;
    CPT0MD    = 0x81;
}

void Voltage_Reference_Init()
{
    REF0CN    = 0x01;
}

void Port_IO_Init()
{
    // P0.0  -  Skipped,     Open-Drain, Analog
    // P0.1  -  CP0A (Cmp0), Push-Pull,  Digital
    // P0.2  -  CEX0  (PCA), Push-Pull,  Digital
    // P0.3  -  CEX1  (PCA), Push-Pull,  Digital
    // P0.4  -  Skipped,     Open-Drain, Digital
    // P0.5  -  Skipped,     Open-Drain, Digital
    // P0.6  -  Skipped,     Open-Drain, Digital
    // P0.7  -  CEX2  (PCA), Push-Pull,  Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Skipped,     Open-Drain, Analog
    // P1.3  -  Unassigned,  Push-Pull,  Digital
    // P1.4  -  Unassigned,  Push-Pull,  Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Push-Pull,  Digital
    // P1.7  -  Skipped,     Open-Drain, Analog

    P0MDIN    = 0xFE;
    P1MDIN    = 0x7B;
    P0MDOUT   = 0x8E;
    P1MDOUT   = 0x58;
    P0SKIP    = 0x71;
    P1SKIP    = 0x84;
    XBR0      = 0x20;
    XBR1      = 0x43;
/*
    // P0.0  -  Skipped,     Open-Drain, Analog
    // P0.1  -  CP0A (Cmp0), Push-Pull,  Digital
    // P0.2  -  CEX0  (PCA), Push-Pull,  Digital
    // P0.3  -  CEX1  (PCA), Push-Pull,  Digital
    // P0.4  -  Skipped,     Open-Drain, Digital
    // P0.5  -  Skipped,     Push-Pull,  Digital
    // P0.6  -  Skipped,     Open-Drain, Digital
    // P0.7  -  CEX2  (PCA), Push-Pull,  Digital

    // P1.0  -  Unassigned,  Push-Pull,  Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Skipped,     Open-Drain, Analog
    // P1.3  -  Unassigned,  Push-Pull,  Digital
    // P1.4  -  Unassigned,  Push-Pull,  Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Push-Pull,  Digital
    // P1.7  -  Skipped,     Open-Drain, Analog

    P0MDIN    = 0xFE;
    P1MDIN    = 0x7B;
    P0MDOUT   = 0xAE;
    P1MDOUT   = 0x59;
    P0SKIP    = 0x71;
    P1SKIP    = 0x84;
    XBR0      = 0x20;
    XBR1      = 0x43;
*/
}

void Oscillator_Init()
{
    OSCICN    = 0xC7;
}

void Interrupts_Init()
{
    EIE1      = 0x04;
    EIP1      = 0x04;
    IE        = 0x2A;
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    Reset_Sources_Init();
    PCA_Init();
    Timer_Init();
    SPI_Init();
    Comparator_Init();
    Voltage_Reference_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}
