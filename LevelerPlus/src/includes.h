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
//---[ Standard header files: ]------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>

//---[ External libraries: ]---------------------------------------------------
#include <I2Cdev.h>

#include <U8glib.h>
#include <HMC58X3.h>
#include <MPU60X0.h>
#include <MS561101BA.h>

//---[ Application-specific header files: ]------------------------------------
#include "types.h"   	// Definition of data types, structures and objects
#include "pinout.h"  	// Pin out assignments
#include "ButtonHandler.h"
#include "EEPROMAnything.h"
#include "data.h"
#include "Kalman.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif // __INCLUDES_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
