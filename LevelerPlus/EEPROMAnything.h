//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  vw.ino
 *  @date  November, 2015
 *  @brief Main application
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef _EEPROM_ANYTHING_H
#define _EEPROM_ANYTHING_H

//-----------------------------------------------------------------------------
//---[ Includes: ]-------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>

//-----------------------------------------------------------------------------
//---[ Methods ]---------------------------------------------------------------

/**
 *
 * @param ee Eeprom memory address
 * @param target Structure to store data
 * @return Number of written bytes
 */
template <class T> int EEPROM_writeAnything(int ee, const T& target)
{
    const byte* p = (const byte*)(const void*)&target;
    unsigned int i;
    for (i = 0; i < sizeof(target); i++)
        EEPROM.write(ee++, *p++);
    return i;
}

//-----------------------------------------------------------------------------

/**
 *
 * @param ee Eeprom memory address
 * @param target Structure to be read
 * @return Number of read bytes
 */
template <class T> int EEPROM_readAnything(int ee, T& target)
{
    byte* p = (byte*)(void*)&target;
    unsigned int i;
    for (i = 0; i < sizeof(target); i++)
        *p++ = EEPROM.read(ee++);
    return i;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif //_EEPROM_ANYTHING_H

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
