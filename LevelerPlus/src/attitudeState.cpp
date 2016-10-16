//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  attitudeState.cpp
 *  @date  Octubre, 2016
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
  _pStateMachine->setState(_pStateMachine->getResetState());
}

//-----------------------------------------------------------------------------

void CAttitudeState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getPressureState());
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
  //THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  //_pStateMachine->_ulTimeStamp = millis();

  static int y {SSD1306_LCDHEIGHT_MED};
  static int x {SSD1306_LCDWIDTH_MED};
  static const int SQUARE_SIZE(8);
  static const int SQUARE_SIZE_MED(SQUARE_SIZE/2);
  static const int ZOOM_FACTOR(3.0f);

  _pStateMachine->_u8g.drawBox(0,SSD1306_LCDHEIGHT_MED-2,SSD1306_LCDWIDTH,SQUARE_SIZE_MED);
  _pStateMachine->_u8g.drawBox(SSD1306_LCDWIDTH_MED-2,0,SQUARE_SIZE_MED,SSD1306_LCDHEIGHT);

  y=(int)(_pStateMachine->_oGDif.roll * ZOOM_FACTOR) + (SSD1306_LCDHEIGHT_MED)-SQUARE_SIZE_MED;
  x=-(int)(_pStateMachine->_oGDif.pitch * ZOOM_FACTOR) + (SSD1306_LCDWIDTH_MED)-SQUARE_SIZE_MED;

  _pStateMachine->_u8g.drawBox(x-SQUARE_SIZE,y-SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  _pStateMachine->_u8g.drawBox(x+SQUARE_SIZE,y-SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  _pStateMachine->_u8g.drawBox(x-SQUARE_SIZE,y+SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  _pStateMachine->_u8g.drawBox(x+SQUARE_SIZE,y+SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
