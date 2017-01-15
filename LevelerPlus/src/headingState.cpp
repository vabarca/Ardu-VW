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
  PROGMEM const char *windrose[] = {"N",  "N-NE", "NE", "NE-E", "E",  "E-SE",
                                    "SE", "S-SE", "S",  "S-SO", "SO", "SO-O",
                                    "O",  "NO-O", "NO", "N-NO"};

  const uint8_t ui8CircleCentre(95);

  uint8_t xN((uint8_t)(30 * sin(/*M_PI_D -*/ _pStateMachine->_fHeading)));
  uint8_t yN((uint8_t)(30 * cos(/*M_PI_D -*/ _pStateMachine->_fHeading)));

  //_pStateMachine->_u8g.drawLine(
  //    xN + ui8CircleCentre, -yN + SSD1306_LCDHEIGHT_MED, -xN +
  //    ui8CircleCentre,
  //    yN + SSD1306_LCDHEIGHT_MED);
  _pStateMachine->_u8g.drawCircle(ui8CircleCentre, SSD1306_LCDHEIGHT_MED, 28);
  _pStateMachine->_u8g.drawDisc(xN + ui8CircleCentre,
                                -yN + SSD1306_LCDHEIGHT_MED, 4);
  _pStateMachine->_setDrawNumberLines(1);
  _pStateMachine->_u8g.setPrintPos(
      0, (u8g_int_t)_pStateMachine->_getDrawRowPos(0));
  _pStateMachine->_u8g.print(
      windrose[(int)(_pStateMachine->_fHeading * RAD_2_DEG / 22.5)]);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
