//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  attitudeState.cpp
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

void CAttitudeState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getTempState());
}

//-----------------------------------------------------------------------------

void CAttitudeState::button1ShortPress()
{
  #ifdef USE_MAG
    _pStateMachine->setState(_pStateMachine->getHeadingState());
  #else
    _pStateMachine->setState(_pStateMachine->getAltitudeState());
  #endif
}

//-----------------------------------------------------------------------------

void CAttitudeState::button0LongPress()
{
  _pStateMachine->_saveCalib(_pStateMachine->_oG);
  _pStateMachine->_oGCal = _pStateMachine->_oG;
  _pStateMachine->_ulTimeStamp = millis();
  _pStateMachine->setState(_pStateMachine->getAttitudeStateCfg());
}

//-----------------------------------------------------------------------------

void CAttitudeState::button1LongPress()
{
  this->button0LongPress();
}

//-----------------------------------------------------------------------------

void CAttitudeState::drawCurrentState()
{
  static int y {SSD1306_LCDHEIGHT_MED};
  static int x {SSD1306_LCDWIDTH_MED};
  static const int SQUARE_SIZE(8);
  static const int SQUARE_SIZE_MED(SQUARE_SIZE/2);

  //_pStateMachine->_u8g.setPrintPos(0,11);
  //_pStateMachine->_u8g.print(_pStateMachine->_oGDif.roll);
  //_pStateMachine->_u8g.setPrintPos(0,22);
  //_pStateMachine->_u8g.print(_pStateMachine->_oGDif.pitch);

  _pStateMachine->_u8g.drawBox(0,SSD1306_LCDHEIGHT_MED-2,SSD1306_LCDWIDTH,SQUARE_SIZE_MED);
  _pStateMachine->_u8g.drawBox(SSD1306_LCDWIDTH_MED-2,0,SQUARE_SIZE_MED,SSD1306_LCDHEIGHT);

  y=(int)_pStateMachine->_oGDif.roll + (SSD1306_LCDHEIGHT_MED)-SQUARE_SIZE_MED;
  x=-(int)_pStateMachine->_oGDif.pitch + (SSD1306_LCDWIDTH_MED)-SQUARE_SIZE_MED;

  _pStateMachine->_u8g.drawBox(x-SQUARE_SIZE,y-SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  _pStateMachine->_u8g.drawBox(x+SQUARE_SIZE,y-SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  _pStateMachine->_u8g.drawBox(x-SQUARE_SIZE,y+SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  _pStateMachine->_u8g.drawBox(x+SQUARE_SIZE,y+SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
