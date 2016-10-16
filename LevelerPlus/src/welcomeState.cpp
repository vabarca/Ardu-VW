//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  welcomeState.cpp
 *  @date  Octubre, 2016
 *  @brief welcome state class
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

void CWelcomeState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CWelcomeState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CWelcomeState::button0LongPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CWelcomeState::button1LongPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CWelcomeState::drawCurrentState()
{
  _pStateMachine->_setDrawNumberLines(1);
  _pStateMachine->_u8g.drawStr(35,
    (u8g_int_t)_pStateMachine->_getDrawRowPos(0),
    "GO!!");
  if(millis() - _pStateMachine->_ulTimeStamp > 3000)
    _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
