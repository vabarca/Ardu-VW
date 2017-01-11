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

  const uint8_t ui8CircleCentre(97);

  _pStateMachine->_u8g.drawCircle(ui8CircleCentre, 32, 31);

  uint8_t xN((uint8_t)(31 * sin(M_PI_D - _pStateMachine->_fHeading)));
  uint8_t yN((uint8_t)(31 * cos(M_PI_D - _pStateMachine->_fHeading)));
  _pStateMachine->_u8g.setFontPosCenter();
  _pStateMachine->_u8g.drawStr(xN + ui8CircleCentre,
                               -yN + SSD1306_LCDHEIGHT_MED, "N");
  /*_pStateMachine->_u8g.drawStr(-xN + SSD1306_LCDWIDTH_MED,
                               yN + SSD1306_LCDHEIGHT_MED, "S");
  _pStateMachine->_u8g.drawStr(-xN + SSD1306_LCDWIDTH_MED,
                               -yN + SSD1306_LCDHEIGHT_MED, "E");
  _pStateMachine->_u8g.drawStr(xN + SSD1306_LCDWIDTH_MED,
                               yN + SSD1306_LCDHEIGHT_MED, "O");*/
  _pStateMachine->_u8g.setFontPosBaseline();
  _pStateMachine->_u8g.setPrintPos(0, 10);
  _pStateMachine->_u8g.print((uint16_t)(_pStateMachine->_fHeading * RAD_2_DEG),
                             1);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
