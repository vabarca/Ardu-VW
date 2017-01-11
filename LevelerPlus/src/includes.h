//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  includes.h
 *  @date  November, 2015
 *  @brief This is a master include file that includes the rest of
 *  header files in the project.
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef __INCLUDES_H__
#define __INCLUDES_H__

//-----------------------------------------------------------------------------
//---[ Macros: ]---------------------------------------------------------------

//#define ULTIMATE_DEBOUNCER
//#define USE_TEMP_STATE
//#define SERIAL_OUTPUT
#define USE_MAG
#define USE_BARO

//-----------------------------------------------------------------------------
//---[ Standard header files: ]------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>

//---[ External libraries: ]---------------------------------------------------
#include <I2Cdev.h>

#include <HMC5883L.h>
#include <MPU60X0.h>
#include <MS561101BA.h>
#include <U8glib.h>

//---[ Application-specific header files: ]------------------------------------
#include "ButtonHandler.h"
#include "EEPROMAnything.h"
#include "Kalman.h"
#include "data.h"
#include "pinout.h" // Pin out assignments
#include "types.h"  // Definition of data types, structures and objects

#include "altitudeRelState.h"
#include "altitudeState.h"
#include "altitudeStateCfg.h"
#include "attitudeState.h"
#include "attitudeStateCfg.h"
#include "headingState.h"
#include "pressureState.h"
#include "resetState.h"
#include "tempState.h"
#include "tempStateCfg.h"
#include "welcomeState.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif // __INCLUDES_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
