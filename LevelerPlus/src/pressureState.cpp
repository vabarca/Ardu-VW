//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  pressureState.cpp
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

void CPressureState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAttitudeState());
}

//-----------------------------------------------------------------------------

void CPressureState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeRelState());
}

//-----------------------------------------------------------------------------

void CPressureState::button0LongPress()
{
}

//-----------------------------------------------------------------------------

void CPressureState::button1LongPress()
{
}

//-----------------------------------------------------------------------------

void CPressureState::drawCurrentState()
{
  _pStateMachine->_u8g.setPrintPos(15,35);
  _pStateMachine->_u8g.print(_pStateMachine->_fPress,1);
  _pStateMachine->_u8g.setPrintPos(85,35);
  _pStateMachine->_u8g.print("mb");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
