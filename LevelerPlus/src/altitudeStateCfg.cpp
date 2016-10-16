//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeStateCfg.cpp
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

void CAltitudeStateCfg::button0ShortPress()
{
  _pStateMachine->_fAltitudeCalib +=10.0;
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button1ShortPress()
{
  _pStateMachine->_fAltitudeCalib -=10.0;
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button0LongPress()
{
  _pStateMachine->_saveAltitudeCalib(_pStateMachine->_fAltitudeCalib);
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button1LongPress()
{
  this->button0LongPress();
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::drawCurrentState()
{
  _pStateMachine->_setDrawNumberLines(2);
  _pStateMachine->_u8g.drawStr(110,
    (u8g_int_t)_pStateMachine->_getDrawRowPos(1),
    "*");
  CAltitudeState::drawCurrentState();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
