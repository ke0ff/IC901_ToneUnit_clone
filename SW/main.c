/****************************************************************************************
 ****************** COPYRIGHT (c) 2021 by Joseph Haas (AKA KE0FF)  *****************
 *
 *  File name: main.c
 *
 *  Module:    Control
 *
 *  Summary:   This is the main code file for the IC-901 ToneUnit CTCSS Encoder application
 *	License and other legal stuff:
 *			   This software, comprised of all files contained in the original distribution archive,
 *				are protected by US Copyright laws.  The files may be used and modified by the person
 *				receiving them under the following terms and conditions:
 *				1) The software, or any protion thereof may not be distributed to any 3rd party by
 *					the recipient or any agent or assign of the recipient.
 *				2) The recipient assumes all risks for the use (or mis-use) of this software.
 *
 *
 *  Project scope revision history:
 *	  *** REV 1.0 ***
 *    05-08-21 jmh:  Initial debug complete.  Product released.
 *					 Added (c)/REV string.
 *					 Fixed bbSPI shift (was shifting lsb first).
 *					 Fixed extern define of tone LUT (was U8, needs to be U16).
 *					 Made P1.6 Fsamp toggle a permanent feature.
 *
 *	  *** REV 00 ***
 *    05-05-21 jmh:  Copied from HM133, rev-03
 *					 main.c: (this file) contains main() and all ISRs and application Fns
 *					 init.h: project defines and main.c prototypes
 *					 typedef.h: type aliases
 *					 f300_init.c: continas IPL init Fns
 *					 c8051F520.h: MCU register defines
 *					 compiler_defs.h: compiler-specific defines
 *					 sine_c.c: contains sine lookup array and CTCSS delF1 ordinal lookup array
 *
 ***************************************************************************************/

/****************************************************************************************
 *  File scope revision history:
 *  05-05-21 jmh:	creation date
 *
 ***************************************************************************************/

//--------------------------------------------------------------------------------------
// main.c
//
//      The following resources of the F531 are used:
//      3.579545 MHz MHz ext crystal osc
//
//      UART: n/u
//
//      Timer0: n/u
//      Timer1: DDS sample driver ISR
//      Timer2: Application timer ISR (1ms/tic) {not currently used... scheduled for demolition}
//
//      ADC: n/u
//
//      PCA: 
//			 CEX0 = bbSPI (slave) serial clock in (RET)
//			 CEX1 = DDS PWM (no int)
//			 CEX2 = bbSPI (slave) strobe input (RET)
//
//      SYSTEM NOTES:
//
//		This project produces CTCSS tones based on an SPI data input from an IC-901 radio.  It is intended
//		to replace the factory stock Tone Unit if damaged or lost.
//
//		CTCSS signals are generated using DDS code running the PCA CEX1 output in 8-bit PWM mode.  
//		Since PCA can't do a regular interrupt in 8-bit PWM mode, Timer1 is used to drive the sample
//		clock.  Thus, the DDS ISR code lives inside Timer1 and updates the PWM register.  Timer1 needs to
//		run at the same (EXACT) rate as the PCA to preserve update alignment.
//
//		The DDS is currently being driven at FSAMP = 6991 Hz to ease the filtering requirements while keeping
//		the ISR rates low.  This sets the Fstep to about 0.053Hz, which gives better than 800ppm resolution
//		at the bottom end of the the CTCSS tone array or about 212ppm at the top end.  ISR overhead is around
//		10-20% based on in-circuit measurements.
//
//--------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
// compile defines
#include "init.h"
#include "typedef.h"
#include "c8051F520.h"

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------


//#define	IS_SIM				// enable this define if using simulator
//#define	IS_DBUG				// enable this define if debugging

//  see init.h for #defines


//-----------------------------------------------------------------------------
// External Variables
//-----------------------------------------------------------------------------

extern code const U8	SINE[];
extern code const U16	tone_lookup[];

//-----------------------------------------------------------------------------
// Main Variables
//-----------------------------------------------------------------------------

// port assignments

// PCB version 1 bit defines
//sbit test_out = P1^7;			// (o) debug toggle output
sbit fsamp_out = P1^6;			// (o) debug toggle output
//sbit 		= P1^5;				// (o) 
//sbit 	    = P1^4;				// (o) 
//sbit 	    = P1^3;				// (o) 
sbit MOSI   = P1^1;				// (i) SPI data in
//			  P1^0;				// (-) XTAL X2

//			  P0^7;				// (-) XTAL X1
sbit P06		= P0^6;			// (i) n/u
//sbit UART_R	= P0^5;			// (i) uart rx
//sbit UART_T	= P0^4;			// (o) uart tx
sbit STB		= P0^3;			// (i) SPI strobe
sbit PWMDAC		= P0^2;			// (o) DDS PWMDAC output
sbit SCLK		= P0^1;			// (i) SPI clk
sbit VREF		= P0^0;			// (a) ext VREF in (NOT USED FOR GPIO IN THIS DESIGN)

//-----------------------------------------------------------------------------
// Local variables
//-----------------------------------------------------------------------------

volatile	U8		ipldds;						// dds ISR init semaphore
volatile	U16		delF1;						// phase (tone) register for tone gen

// bbSPI registers
volatile	U8		SPDR;
volatile	bit		tmute;						// tone mute semaphore


//-----------------------------------------------------------------------------
// Local Prototypes
//-----------------------------------------------------------------------------

//******************************************************************************
// main()
//  The main function inits I/O and process I/O.
//
//******************************************************************************
void main(void)
{
	code const char	rev_note[] = {"IC-901 ToneUnit Clone, V1.0. (c) May 08, 2021 by Joseph Haas, AKA ke0ff\n"};

	// start of main
	while(1){									// outer loop is for soft-restart capability
		PCA0MD = 0x00;							// disable watchdog
		EA = 0;

		// init MCU system
		Init_Device();							// init MCU
		MOSI = 1;
		P06 = 1;
		SCLK = 1;
		STB = 1;
		EA = 1;
		// init module vars
		PCA0CPM1 &= 0xfe;						// disable CCF1
		delF1 = tone_lookup[0];					// clear the DDS tone reg
		tmute = 1;								// mute the tone
		ipldds = 1;								// ipl the DDS

#ifndef	IS_SIM									// skip DDS wait if sim
		// process IPL init
		while(ipldds);							// wait for DDS to init
#endif
		
#ifdef	IS_DBUG									// allows testing of DDS on IPL
		delF1 = TONE_500;						// Turn on 500 Hz tone for testing
		tmute = 0;
#endif

			if(rev_note[0] == 'I'){
			// main loop
			while(1){								// inner-loop runs the main application
				PCON = 1;							// set idle mode (nothing else to do here)
			} // end while(1)
		} // end if
	} // end outer while()
} // end main()

//    *********************************************
//  *************** SUBROUTINES/ISRs ****************
//    *********************************************

//-----------------------------------------------------------------------------
// pca_intr
//-----------------------------------------------------------------------------
//
// Called when PCA CEX0 or CEX2 input RE events are detected:
//	CEX0 is rising edge from the IC-901 serial clock.
//		This interrupt shifts in one bit of data from the MOSI pin and places it
//		in the SPDR memory location, msb first.
//
//	CEX1 is 8bPWM (does not generate an interrupt).
//
//	CEX2 is rising edge from the IC-901 CTC signal (strobe).
//		This interrupt validates tone# and updates tone frequency.  Also updates
//		tmute status.
//-----------------------------------------------------------------------------

void pca_intr(void) interrupt 9 using 2{
	U8		temp;
	
	temp = MOSI;										// grab databit first thing (discarded if ISR call not from clock)
    if(CCF0 == 1){
		// process clock rising edge
		SPDR <<= 1;										// make room in data register
		if(temp == 1){
			SPDR |= 0x01;								// make DR match the data bit
		}
		CCF0 = 0;                       				// clr intr flag
	}
    if(CCF2 == 1){
		// process strobe rising edge
		// set tmute
		if(SPDR & TONE_MUTE) tmute = 1;					// check/update tmute bit
		else tmute = 0;
		// update delF1
		temp = SPDR & TONE_MASK;						// get tone#
		if(temp <= TONE_MAX){
			delF1 = tone_lookup[temp];					// if valid, update tone
		}else{
			delF1 = 0;									// else, tone off
		}
 		CCF2 = 0;                       				// clr intr flag
	}
	return;
}

//-----------------------------------------------------------------------------
// Timer1_ISR
//-----------------------------------------------------------------------------
//
// Called when timer 1 overflows (NORM mode):
//      drives single-tone DDS.  If tmute == 1, NOP.
//
//-----------------------------------------------------------------------------

void Timer1_ISR(void) interrupt 3 using 2
{
	// DDS vars
	U8		pac;				// temp regs
	static U16	phaccum1;		// tone 1 phacc

    TF1 = 0;                           					// Clear Timer2 interrupt flag
	fsamp_out ^= 1;
	if(ipldds){
		// process IPL init semaphore
		phaccum1 = 0;
		ipldds = 0;
	}
	if(!tmute){
		// process phase accumulator
		phaccum1 += delF1;								// add delta to advance phase
		pac = (U8)(phaccum1 >> 8);						// get integer part of phase accumulator (becomes index into sine LUT)
		PCA0CPH1 = SINE[pac];							// do sine lookup
	}	
	return;
}

//#undef IS_MAINC
//**************
// End Of File
//**************
