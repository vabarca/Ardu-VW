//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  heading.cpp
 *  @date  July, 2016
 *  @brief Attitude State class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#include "includes.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void CHeadingState::button0ShortPress() {
  _pStateMachine->setState(_pStateMachine->getAttitudeState());
}

//-----------------------------------------------------------------------------

void CHeadingState::button1ShortPress() {
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CHeadingState::button0LongPress() {}

//-----------------------------------------------------------------------------

void CHeadingState::button1LongPress() {}

//-----------------------------------------------------------------------------

void CHeadingState::drawCurrentState() {
  // THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  //_pStateMachine->_ulTimeStamp = millis();

  const uint8_t ui8CircleCentre(95);

  uint8_t xN((uint8_t)(31 * sin(/*M_PI_D -*/ _pStateMachine->_fHeading)));
  uint8_t yN((uint8_t)(31 * cos(/*M_PI_D -*/ _pStateMachine->_fHeading)));

  _pStateMachine->_u8g.drawLine(
      xN + ui8CircleCentre, -yN + SSD1306_LCDHEIGHT_MED, -xN + ui8CircleCentre,
      yN + SSD1306_LCDHEIGHT_MED);
  _pStateMachine->_u8g.drawCircle(ui8CircleCentre, SSD1306_LCDHEIGHT_MED, 31);
  _pStateMachine->_setDrawNumberLines(1);
  _pStateMachine->_u8g.setPrintPos(
      (u8g_int_t)_pStateMachine->_getFloatDrawColPos(_pStateMachine->_fHeading),
      (u8g_int_t)_pStateMachine->_getDrawRowPos(0));
  _pStateMachine->_u8g.print(_pStateMachine->_fHeading * RAD_2_DEG, 0);
  _pStateMachine->_u8g.print("º");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
