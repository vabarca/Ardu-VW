//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeState.cpp
 *  @date  Octubre, 2016
 *  @brief Altitude state class
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

void CAltitudeState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeRelState());
}

//-----------------------------------------------------------------------------

void CAltitudeState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getResetState());
}

//-----------------------------------------------------------------------------

void CAltitudeState::button0LongPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeStateCfg());
}

//-----------------------------------------------------------------------------

void CAltitudeState::button1LongPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeStateCfg());
}

//-----------------------------------------------------------------------------

void CAltitudeState::drawCurrentState()
{
  _pStateMachine->_u8g.setPrintPos(15,35);
  _pStateMachine->_u8g.print(_pStateMachine->_fAltitude, 1);
  _pStateMachine->_u8g.setPrintPos(85,35);
  _pStateMachine->_u8g.print("m");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
