//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeState.cpp
 *  @date  July, 2016
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

void CAltitudeState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAttitudeState());
}

//-----------------------------------------------------------------------------

void CAltitudeState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getTempState());
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
  _pStateMachine->_u8g.setPrintPos(20,25);
  _pStateMachine->_u8g.print(_pStateMachine->_fAltitude -
    _pStateMachine->_fAltitudeCalib, 1);
  _pStateMachine->_u8g.setPrintPos(95,25);
  _pStateMachine->_u8g.print("m");
  _pStateMachine->_u8g.setPrintPos(20,45);
  _pStateMachine->_u8g.print(_pStateMachine->_fPress,1);
  _pStateMachine->_u8g.setPrintPos(95,45);
  _pStateMachine->_u8g.print("mb");

  if(millis() - _pStateMachine->_ulTimeStamp > 60000)
    _pStateMachine->setState(_pStateMachine->getTempState());
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
