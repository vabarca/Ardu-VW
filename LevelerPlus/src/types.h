//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  types.h
 *  @date  November, 2015
 *  @brief This file contains the definitions of special data types
 *  		used in the application.
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef _TYPES_H_
#define _TYPES_H_

//-----------------------------------------------------------------------------
//---[ Standard header files: ]------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//---[ Version defines: ]-------------------------------------------------------

/**
 * Program Major version
 */
const uint8_t MAJOR(2);
/**
 * Program Minor version
 */
const uint8_t MINOR(3);
/**
 * Program bugs fixes
 */
const uint8_t PATCH(0);

//-----------------------------------------------------------------------------
//---[ Macros: ]---------------------------------------------------------------

#ifdef SERIAL_OUTPUT
#define SERIAL_BEGIN Serial.begin(115200)
#define SERIAL_PRINTLN(a) Serial.println(a)
#define SERIAL_PRINT(a) Serial.print(a)
#else
#define SERIAL_BEGIN
#define SERIAL_PRINTLN(a)
#define SERIAL_PRINT(a)
#endif

//---[ Generic data Types: ]---------------------------------------------------

//---[ Application enumerated parameters: ]------------------------------------

enum eStateMachine {
  ESM_WELCOME = 0,
  ESM_TEMP,
  ESM_ATTITUDE,
  ESM_CALIB_ATTITUDE,
  ESM_ALTITUDE,
  ESM_HEADING,
  ESM_CALIB_ALTITUDE,
  ESM_RESET
};

//---[ Application-specific data Types: ]-------------------------------------

//---[ Global defines: ]-------------------------------------------------------

/**
 */
const float M_PI_QUAD{M_PI / 4};

/**
 */
const float M_PI_MED{M_PI / 2};

/**
 */
const float M_PI_D{2 * M_PI};

/**
 */
const float RAD_2_DEG{180.0f / M_PI};

/**
 * Altitude Filter Size
 */
const uint8_t MOVAVG_SIZE{32};

/**
 * Sea level average pressure
 */
const float SEA_LEVEL_PRESSURE{1013.25};

/**
 * Sea level average pressure
 */
const float ABSOLUTE_ZERO{273.15f};

/**
 * For calculating altitude
 */
const float TERM_A{1.0f / 5.257f};
const float TERM_B{0.0065f};
const float TERM_C{5.257f};

/**
 * EEPROM memory addresses for PITCH calibration data
 */
const uint8_t EEPROM_CAL_PITCH{0};

/**
 * EEPROM memory addresses for ROLL calibration data
 */
const uint8_t EEPROM_CAL_ROLL{EEPROM_CAL_PITCH + sizeof(double)};

/**
 * EEPROM memory addresses for YAW calibration data
 */
const uint8_t EEPROM_CAL_YAW{EEPROM_CAL_ROLL + sizeof(double)};

/**
 * EEPROM memory addresses for sea level pressure calibration data
 */
const uint8_t EEPROM_SEA_LEVEL_PRESSURE{EEPROM_CAL_YAW + sizeof(float)};

/**
 * EEPROM memory addresses for altitude calibration data
 */
const uint8_t EEPROM_REF_ALTITUDE{EEPROM_SEA_LEVEL_PRESSURE + sizeof(float)};

/**
 * EEPROM memory addresses for temp calibration data
 */
const uint8_t EEPROM_CAL_TEMP{EEPROM_REF_ALTITUDE + sizeof(float)};

/**
 * Display width
 */
const uint8_t SSD1306_LCDWIDTH{128};

/**
 * Display height
 */
const uint8_t SSD1306_LCDHEIGHT{64};

/**
 * Display width/2
 */
const uint8_t SSD1306_LCDWIDTH_MED{SSD1306_LCDWIDTH / 2};

/**
 * Display height/2
 */
const uint8_t SSD1306_LCDHEIGHT_MED{SSD1306_LCDHEIGHT / 2};

/**
 * Comment out to restrict roll to �90deg instead - please
 * read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf
 */
#define RESTRICT_PITCH

//---[ Useful Macros: ]--------------------------------------------------------

/**
 * Macro to clear a shared variable in an atomic operation (critical area)
 */
#ifndef CLEAR
#define CLEAR(x)                                                               \
  {                                                                            \
    cli();                                                                     \
    x = 0;                                                                     \
    sei();                                                                     \
  }
#endif

/**
 * Macro to clear individual bits in a SFR register
 */
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

/**
 * Macro to set individual bits in a SFR register
 */
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif // _TYPES_H_

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
