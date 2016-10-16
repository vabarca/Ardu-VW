//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  resetState.cpp
 *  @date  Octubre, 2016
 *  @brief
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

void CResetState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CResetState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAttitudeState());
}

//-----------------------------------------------------------------------------

void CResetState::button0LongPress()
{
  _pStateMachine->_restoreSettings();
}

//-----------------------------------------------------------------------------

void CResetState::button1LongPress()
{
  this->button0LongPress();
}

//-----------------------------------------------------------------------------

void CResetState::drawCurrentState()
{
  //THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  //_pStateMachine->_ulTimeStamp = millis();

  _pStateMachine->_setDrawNumberLines(2);
  _pStateMachine->_u8g.drawStr(25,
    (u8g_int_t)_pStateMachine->_getDrawRowPos(0),
    "Reset");

  _pStateMachine->_u8g.drawStr(15,
    (u8g_int_t)_pStateMachine->_getDrawRowPos(1),
    "system?");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
