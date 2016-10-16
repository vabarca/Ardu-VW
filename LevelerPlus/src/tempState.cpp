//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  tempState.cpp
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

void CTempState::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CTempState::button1ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getResetState());
}

//-----------------------------------------------------------------------------

void CTempState::button0LongPress()
{
  _pStateMachine->setState(_pStateMachine->getTempStateCfg());
}

//-----------------------------------------------------------------------------

void CTempState::button1LongPress()
{
  _pStateMachine->setState(_pStateMachine->getTempStateCfg());
}

//-----------------------------------------------------------------------------

void CTempState::drawCurrentState()
{
  //THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  //_pStateMachine->_ulTimeStamp = millis();

  _pStateMachine->_u8g.setPrintPos(40,35);
  _pStateMachine->_u8g.print(_pStateMachine->_fTemperature,1);
  _pStateMachine->_u8g.setPrintPos(90,35);
  _pStateMachine->_u8g.print("C");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
