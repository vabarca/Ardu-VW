//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeRelState.cpp
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
  _pStateMachine->_u8g.setPrintPos(15,35);
  _pStateMachine->_u8g.print(_pStateMachine->_fAltitude -
    _pStateMachine->_fAltitudeRef, 1);
  _pStateMachine->_u8g.setPrintPos(60,55);
  _pStateMachine->_u8g.print("m rel");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
