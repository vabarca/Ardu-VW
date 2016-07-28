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
  #ifdef USE_MAG
    _pStateMachine->setState(_pStateMachine->getHeadingState());
  #else
    _pStateMachine->setState(_pStateMachine->getAttitudeState());
  #endif
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
  _pStateMachine->_u8g.setPrintPos(10,15);
  _pStateMachine->_u8g.print(_pStateMachine->_fAltitude, 1);
  _pStateMachine->_u8g.setPrintPos(85,15);
  _pStateMachine->_u8g.print("m");

  _pStateMachine->_u8g.setPrintPos(10,35);
  _pStateMachine->_u8g.print(_pStateMachine->_fAltitude -
    _pStateMachine->_fAltitudeRef, 1);
  _pStateMachine->_u8g.setPrintPos(85,35);
  _pStateMachine->_u8g.print("m rel");

  _pStateMachine->_u8g.setPrintPos(10,55);
  _pStateMachine->_u8g.print(_pStateMachine->_fPress,1);
  _pStateMachine->_u8g.setPrintPos(85,55);
  _pStateMachine->_u8g.print("mb");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
