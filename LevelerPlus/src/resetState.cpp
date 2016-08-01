//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  resetState.cpp
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

void CResetState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getTempState());
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
  _pStateMachine->_u8g.drawStr(3,25,"Restore factory");
  _pStateMachine->_u8g.drawStr(25,45,"settings?");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
