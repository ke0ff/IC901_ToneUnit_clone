/*************************************************************************
 *********** COPYRIGHT (c) 2021 by Joseph Haas (AKA KE0FF)  *********
 *
 *  File name: init.h
 *
 *  Module:    Control
 *
 *  Summary:   This is the header file for main.
 *
 *******************************************************************/


/********************************************************************
 *  File scope declarations revision history:
 *    05-08-21 jmh:  modified for ToneUnit application
 *    05-10-13 jmh:  creation date
 *
 *******************************************************************/

#include "typedef.h"

#ifndef INIT_H
#define INIT_H
#endif

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define EXTXTAL

// timer definitions.  Uses EXTXTAL #def to select between ext crystal and int osc
//  for normal mode.
// SYSCLK value in Hz
#define SYSCLKL 10000L
#ifdef EXTXTAL
#define SYSCLKF 3579545L
#else
#define SYSCLKF (12000000L) // / 8)
#endif
#define	SYSCLK	(SYSCLKF)	//24500000L
// timer2 register value
#define TMR2RLL_VAL (U8)((65536 -(SYSCLK/(12L * 1000L))) & 0xffL)
#define TMR2RLH_VAL (U8)((65536 -(SYSCLK/(12L * 1000L))) >> 8L)
#define	TMRSECHACK	2
#define TMRIPL		1
#define TMRRUN		0

// PCA timer constants
#define	PCACLK	(SYSCLK / 2)
#define	FSAMP	(PCACLK / 256L)			// For 8-bit PWM, FSAMP is PCACLK / 2^8


// DDS defines
#define N_SIN 256L						// number of effective slots in sin look-up table
#define RSHIFT 8L						// bits to downshift phase accum to align RADIX
#define RADIX 256L						// = 2^RSHIFT

// (Fsamp = 6991 Hz)	Fstep = FSAMP/(RADIX * N_SIN) = 6991/(256*256) = 0.107 Hz
// CTCSS tone table defines (as defined for the IC-901):
#define TONE_01 (U16)(670L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_02 (U16)(719L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_03 (U16)(744L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_04 (U16)(770L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_05 (U16)(797L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_06 (U16)(825L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_07 (U16)(854L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_08 (U16)(885L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_09 (U16)(915L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_10 (U16)(948L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_11 (U16)(974L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_12 (U16)(1000L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_13 (U16)(1035L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_14 (U16)(1072L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_15 (U16)(1109L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_16 (U16)(1148L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_17 (U16)(1188L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_18 (U16)(1230L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_19 (U16)(1273L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_20 (U16)(1318L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_21 (U16)(1365L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_22 (U16)(1413L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_23 (U16)(1462L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_24 (U16)(1514L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_25 (U16)(1567L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_26 (U16)(1622L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_27 (U16)(1679L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_28 (U16)(1738L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_29 (U16)(1799L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_30 (U16)(1862L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_31 (U16)(1928L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_32 (U16)(2035L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_33 (U16)(2107L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_34 (U16)(2181L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_35 (U16)(2257L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_36 (U16)(2336L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_37 (U16)(2418L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_38 (U16)(2503L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_500  (U16)( 5000L * (RADIX * N_SIN) / (10L * FSAMP))
#define TONE_1000 (U16)(10000L * (RADIX * N_SIN) / (10L * FSAMP))

#define	TONE_MASK	(0x3F)
#define	TONE_MAX	(38)
#define	TONE_MUTE	(0x80)

#define MS_PER_TIC  10
// General timer constants
#define MS25        	(25/MS_PER_TIC)
#define MS35        	(35/MS_PER_TIC)
#define MS40        	(40/MS_PER_TIC)
#define MS45        	(45/MS_PER_TIC)
#define MS50        	(50/MS_PER_TIC)
#define MS80        	(80/MS_PER_TIC)
#define MS100        	(100/MS_PER_TIC)
#define MS125       	(125/MS_PER_TIC)
#define MS250       	(250/MS_PER_TIC)
#define MS400       	(400/MS_PER_TIC)
#define MS450       	(450/MS_PER_TIC)
#define MS500       	(500/MS_PER_TIC)
#define MS750       	(750/MS_PER_TIC)
#define MS800       	(800/MS_PER_TIC)
#define MS1000      	(1000/MS_PER_TIC)
#define MS1500      	(1500/MS_PER_TIC)
#define MS1650      	(1650/MS_PER_TIC)
#define MS2000      	(2000/MS_PER_TIC)
#define MS2500      	(2500/MS_PER_TIC)
#define MS5000      	(5000/MS_PER_TIC)
#define MS10000     	(10000/MS_PER_TIC)
#define MS20000     	(20000/MS_PER_TIC)
#define MINPERHOUR		60
#define SECPERMIN		60
#define MINPER6HOUR		(6 * MINPERHOUR)
#define MINPER12HOUR	(12 * MINPERHOUR)
#define MINPER18HOUR	(18 * MINPERHOUR)
#define MINPER24HOUR	(24 * MINPERHOUR)

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

#ifndef IS_MAINC
//extern <typdef> <fn>;
#endif

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------

void Init_Device(void);

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
