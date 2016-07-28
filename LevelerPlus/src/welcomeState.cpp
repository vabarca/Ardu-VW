//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  tempState.cpp
 *  @date  July, 2016
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

void CWelcomeState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getTempState());
}

//-----------------------------------------------------------------------------

void CWelcomeState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getTempState());
}

//-----------------------------------------------------------------------------

void CWelcomeState::button0LongPress()
{
  _pStateMachine->setState(_pStateMachine->getTempState());
}

//-----------------------------------------------------------------------------

void CWelcomeState::button1LongPress()
{
  _pStateMachine->setState(_pStateMachine->getTempState());
}

//-----------------------------------------------------------------------------

void CWelcomeState::drawCurrentState()
{
  _pStateMachine->_u8g.drawStr(10,35,"GO for launch!");
  if(millis() - _pStateMachine->_ulTimeStamp > 3000)
    _pStateMachine->setState(_pStateMachine->getTempState());
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
