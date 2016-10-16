//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeRelState.cpp
 *  @date  Octubre, 2016
 *  @brief Altitude State class
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

void CAltitudeRelState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getPressureState());
}

//-----------------------------------------------------------------------------

void CAltitudeRelState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CAltitudeRelState::button0LongPress()
{
  _pStateMachine->_saveAltitudeRef(_pStateMachine->_fAltitude);
  _pStateMachine->_fAltitudeRef = _pStateMachine->_fAltitude;
}

//-----------------------------------------------------------------------------

void CAltitudeRelState::button1LongPress()
{
  _pStateMachine->_saveAltitudeRef(_pStateMachine->_fAltitude);
  _pStateMachine->_fAltitudeRef = _pStateMachine->_fAltitude;
}

//-----------------------------------------------------------------------------

void CAltitudeRelState::drawCurrentState()
{
  //THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  //_pStateMachine->_ulTimeStamp = millis();

  float fTemp (_pStateMachine->_fAltitude -
    _pStateMachine->_fAltitudeRef);

  _pStateMachine->_setDrawNumberLines(2);
  _pStateMachine->_u8g.setPrintPos(
    (u8g_int_t)_pStateMachine->_getFloatDrawColPos(fTemp),
    (u8g_int_t)_pStateMachine->_getDrawRowPos(0));
  _pStateMachine->_u8g.print(fTemp, 1);

  _pStateMachine->_u8g.drawStr(0,
    (u8g_int_t)_pStateMachine->_getDrawRowPos(1),
    "Alt rel(m)");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
