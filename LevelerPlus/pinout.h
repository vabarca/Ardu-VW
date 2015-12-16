//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file pinout.h
 *  @date   November, 2015
 *  @brief Teensy pinout assignment
 *
 *  This code is based on the LINX example firmware for use with
 *  the PJRC Teensy 3.1 with the serial interface enabled.
 *
 *  For more information see:           www.labviewmakerhub.com/linx
 *  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef PINOUT_H_
#define PINOUT_H_

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//---[ Pinout assignment: ]----------------------------------------------------

/**
 * Button0 pin assignment
 */
const uint8_t BUTTON_PIN0         (8);

/**
 * Button1 pin assignment
 */
const uint8_t BUTTON_PIN1         (7);

/**
 * LED pins assignment
 */
const uint8_t LED_PIN             (13);

/**
 * I2C0
 */
const uint8_t I2C_SCL0            (A5);
const uint8_t I2C_SDA0            (A4);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif /* PINOUT_H_ */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

