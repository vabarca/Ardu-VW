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

  uint8_t xN((uint8_t)(30 * sin(/*M_PI_D -*/ _pStateMachine->_fHeading)));
  uint8_t yN((uint8_t)(30 * cos(/*M_PI_D -*/ _pStateMachine->_fHeading)));

  //_pStateMachine->_u8g.drawLine(
  //    xN + ui8CircleCentre, -yN + SSD1306_LCDHEIGHT_MED, -xN +
  //    ui8CircleCentre,
  //    yN + SSD1306_LCDHEIGHT_MED);
  _pStateMachine->_u8g.drawCircle(SSD1306_LCDWIDTH_MED, SSD1306_LCDHEIGHT_MED,
                                  31);
  _pStateMachine->_u8g.drawDisc(xN + SSD1306_LCDWIDTH_MED,
                                -yN + SSD1306_LCDHEIGHT_MED, 4);

  float iData{_pStateMachine->_fHeading * RAD_2_DEG};
  String strWindRose =
      (iData >= 337.5 && iData < 22.5)
          ? "N"
          : (iData >= 22.5 && iData < 67.5)
                ? "NE"
                : (iData >= 67.5 && iData < 112.5)
                      ? "E"
                      : (iData >= 112.5 && iData < 157.5)
                            ? "SE"
                            : (iData >= 157.5 && iData < 202.5)
                                  ? "S"
                                  : (iData >= 202.5 && iData < 247.5)
                                        ? "SO"
                                        : (iData >= 247.5 && iData < 292.5)
                                              ? "O"
                                              : (iData >= 292.5 &&
                                                 iData < 337.5)
                                                    ? "NO"
                                                    : "N";
  _pStateMachine->_setDrawNumberLines(1);
  _pStateMachine->_u8g.setPrintPos(
      SSD1306_LCDWIDTH_MED - 2 - ((strWindRose.length() * 12) >> 1),
      (u8g_int_t)_pStateMachine->_getDrawRowPos(0) + 4);

  _pStateMachine->_u8g.print(strWindRose.c_str());
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
