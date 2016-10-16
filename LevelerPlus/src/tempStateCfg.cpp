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

void CTempStateCfg::button0ShortPress()
{
  _pStateMachine->_fTemperatureCalib += 0.1f;
}

//-----------------------------------------------------------------------------

void CTempStateCfg::button1ShortPress()
{
  _pStateMachine->_fTemperatureCalib -= 0.1f;
}

//-----------------------------------------------------------------------------

void CTempStateCfg::button0LongPress()
{
  _pStateMachine->_saveTempCalib(_pStateMachine->_fTemperatureCalib);
  _pStateMachine->setState(_pStateMachine->getTempState());
}

//-----------------------------------------------------------------------------

void CTempStateCfg::button1LongPress()
{
  this->button0LongPress();
}

//-----------------------------------------------------------------------------

void CTempStateCfg::drawCurrentState()
{
  _pStateMachine->_setDrawNumberLines(2);
  _pStateMachine->_u8g.drawStr(110,
    (u8g_int_t)_pStateMachine->_getDrawRowPos(1),
    "*");
  CTempState::drawCurrentState();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
