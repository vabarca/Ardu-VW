//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  attitudeStateCfg.cpp
 *  @date  Octubre, 2016
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

void CAttitudeStateCfg::button0ShortPress()
{
  _pStateMachine->setState(_pStateMachine->getAttitudeState());
}

//-----------------------------------------------------------------------------

void CAttitudeStateCfg::button1ShortPress()
{
  this->button0ShortPress();
}

//-----------------------------------------------------------------------------

void CAttitudeStateCfg::button0LongPress()
{
  this->button0ShortPress();
}

//-----------------------------------------------------------------------------

void CAttitudeStateCfg::button1LongPress()
{
  this->button0ShortPress();
}

//-----------------------------------------------------------------------------

void CAttitudeStateCfg::drawCurrentState()
{
  _pStateMachine->_setDrawNumberLines(1);
  _pStateMachine->_u8g.drawStr(15,
    (u8g_int_t)_pStateMachine->_getDrawRowPos(0),
    "Fix it!");
  if(millis() - _pStateMachine->_ulTimeStamp > 1000)
    _pStateMachine->setState(_pStateMachine->getAttitudeState());
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
