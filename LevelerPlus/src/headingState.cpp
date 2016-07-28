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

void CHeadingState::button0ShortPress(){}

//-----------------------------------------------------------------------------

void CHeadingState::button1ShortPress(){}

//-----------------------------------------------------------------------------

void CHeadingState::button0LongPress(){}

//-----------------------------------------------------------------------------

void CHeadingState::button1LongPress(){}

//-----------------------------------------------------------------------------

void CHeadingState::drawCurrentState()
{
  _pStateMachine->_u8g.drawCircle(64, 32, 24);

  uint8_t xN((uint8_t)(24*sin(M_PI_D - _pStateMachine->_fHeading)));
  uint8_t yN((uint8_t)(24*cos(M_PI_D - _pStateMachine->_fHeading)));
  _pStateMachine->_u8g.setFontPosCenter();
  _pStateMachine->_u8g.drawStr(xN + SSD1306_LCDWIDTH_MED,-yN+ SSD1306_LCDHEIGHT_MED,"N");
  _pStateMachine->_u8g.drawStr(-xN + SSD1306_LCDWIDTH_MED,yN+ SSD1306_LCDHEIGHT_MED,"S");
  _pStateMachine->_u8g.drawStr(-xN + SSD1306_LCDWIDTH_MED,-yN+ SSD1306_LCDHEIGHT_MED,"E");
  _pStateMachine->_u8g.drawStr(xN + SSD1306_LCDWIDTH_MED,yN+ SSD1306_LCDHEIGHT_MED,"O");
  _pStateMachine->_u8g.setFontPosBaseline();

  _pStateMachine->_u8g.setPrintPos(0,10);
  _pStateMachine->_u8g.print(_pStateMachine->_fHeading);

  SERIAL_PRINT("Orientation: ");
  SERIAL_PRINT(_pStateMachine->_fHeading * RAD_2_DEG);
  SERIAL_PRINTLN(" deg");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
